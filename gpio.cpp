#include "gpio.h"

void gpioInit()
{
    if(gpioInitialise() == -1)
        qDebug() << "GPIO Init Fehler";

    //Input AtTiny13A
    gpioSetMode(5, PI_INPUT);           //VideoSwitch
    gpioSetMode(6, PI_INPUT);           //Shutdown

    //Akku Anzeige
    gpioSetMode(7, PI_OUTPUT);
    gpioSetMode(12, PI_OUTPUT);
    gpioSetMode(16, PI_OUTPUT);
    gpioSetMode(20, PI_OUTPUT);
    gpioSetMode(21, PI_OUTPUT);
    gpioWrite(7,1);                     //LED1 leuchtet immer
    gpioWrite(12,1);
    gpioWrite(16,1);
    gpioWrite(20,1);
    gpioWrite(21,1);

    // i2C
    gpioSetMode(13,PI_OUTPUT);          // MMA8491_EN
    gpioWrite(13,0);                    // MMA8491_EN = 0

    // Beleuchtung
    gpioSetMode(23,PI_OUTPUT);           // LED_Enable_2
    gpioWrite(23,0);                     // Beleuchtung = 0
    gpioSetMode(25,PI_OUTPUT);          // LED_Enable_1
    gpioWrite(25,0);                    // Beleuchtung = 0

}

int getOnOff()
{
    return gpioRead(6);
}

int getVideoOnOff()
{
    return gpioRead(5);
}

void setLEDsOn()
{
    gpioWrite(23,1);
    gpioWrite(25,1);
}

void setLEDsOff()
{
    gpioWrite(23,0);
    gpioWrite(25,0);
}

void setFuelGaugeLEDs(int charge)
{
    if(charge >= 80)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,1);
        gpioWrite(21,1);
    }
    else if(charge >= 60 && charge < 80)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,1);
        gpioWrite(21,0);
    }
    else if(charge >= 40 && charge < 60)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }
    else if(charge >= 20 && charge < 40)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,0);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }
    else if(charge > 0 && charge < 20)
    {
        gpioWrite(7,1);
        gpioWrite(12,0);
        gpioWrite(16,0);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }
    else
    {
        gpioWrite(7,0);
        gpioWrite(12,0);
        gpioWrite(16,0);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }

}

//--------------------------------------------------------------------
/* Initialisiert LTC2941
    Vbat Alert   = [01]  = 2.8V
    Prescaler M  = [111] = 128
    AL/CC        = [00]  = pin AL/CC disabled
    Shutdown     = [0]   = no Shutdown
*/
void initFuelGauge()
{
    int handle = 0;

    handle = i2cOpen(1,0x64,0);

    i2cWriteByteData(handle,0x01,0x78);

    i2cClose(handle);

}
//-------------------------------------------------------------------

//--------------------------------------------------------------------
// Liest Register 0x02 und 0x03 (MSB und LSB Accumulated Charge) von LTC2941 aus
int getCharge()
{
    int handle = 0;

    int charge_MSB = 0;
    int charge_LSB = 0;
    unsigned short int charge = 0;

    double akkustand_double = 0;
    double charge_double = 0;
    int akkustand_int = 0;

    i2cSwitchCombined(1);               // WICHTIG! Enable "Repeated Start"!!

    handle = i2cOpen(1,0x64,0);

    i2cWriteByte(handle,0x02);          // MSB Data

    charge_MSB = i2cReadByteData(handle,0x02);
    charge_LSB = i2cReadByteData(handle,0x03);

    charge = charge_LSB + (charge_MSB << 8);

    i2cClose(handle);

     // Wertigkeit des LSB von Charge (in mAh)
    // siehe Datenblatt LTC2941 Seite 10
    // q_lsb = 0.425

    // Akkukapazität verbaut = 9000mAh

    // 9000 / 0.425 =  21176
    // 2^16 - 21176 = 44359 = 0xAD48

    // --> Charge = 0xFFFF --> Akkustand = 100%
    // --> Charge = 0xAD48 --> Akkustand = 0%

    charge_double = charge;
    akkustand_double = ((charge_double - 44359.0) / 21176.0) * 100;
    akkustand_int = akkustand_double;

    if(akkustand_int < 0)
    {
        akkustand_int = 0;
    }

    return akkustand_int;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Setzt Register 0x02 und 0x03 von LTC2941 auf 0xFFFF (voll aufgeladen)
void setChargeFull()
{
    int handle = 0;

    handle = i2cOpen(1,0x64,0);

    i2cWriteByteData(handle,0x02,0xFF);
    i2cWriteByteData(handle,0x03,0xFF);

    i2cClose(handle);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Setzt Register 0x02 und 0x03 von LTC2941 auf 0xAD48 (Akku leer)
void setChargeEmpty()
{
    int handle = 0;

    handle = i2cOpen(1,0x64,0);

    i2cWriteByteData(handle,0x02,0xAD);
    i2cWriteByteData(handle,0x03,0x48);

    i2cClose(handle);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
/*   Prüft Status Register 0x00 auf Vbat Alert
     Vbat Alert = 0 --> Akkuspannung unter 2.8V
   Returnstatement: [0] = Spannung OK / [1] = Spannung unter 2.8V*/
int emptyCheck()
{
    int handle = 0;
    int StatusReg = 0;

    i2cSwitchCombined(1);               // WICHTIG! Enable "Repeated Start"!!

    handle = i2cOpen(1,0x64,0);
    i2cWriteByte(handle,0x00);          // MSB Data
    StatusReg = i2cReadByteData(handle,0x00);
    i2cClose(handle);

    if((StatusReg & 0x02) != 0)
        return 1;
    else
        return 0;
}
//--------------------------------------------------------------------

