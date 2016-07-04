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

int getAngle()
{
    //Konstantendeklaration
     const int PI = 3.14159265359;

     //Variablendeklaration
     int handle = 0;
     int dataready = 0;

     int dataX_MSB = 0;
     int dataX_LSB = 0;
     int dataY_MSB = 0;
     int dataY_LSB = 0;
     int dataZ_MSB = 0;
     int dataZ_LSB = 0;

     signed short int dataX = 0;
     signed short int dataY = 0;
     signed short int dataZ = 0;

     int winkel = 0;
     double tangens = 0;
     double dataX_ABS = 0;
     double dataZ_ABS = 0;

      //i2c

         i2cSwitchCombined(1);               // WICHTIG! Enable "Repeated Start"!!

         gpioWrite(13,1);                    // MMA8491_EN = 1
         gpioDelay(1000);                   // Ton (minimales Delay)
         handle = i2cOpen(1,0x55,0);

         i2cWriteByte(handle,0x00);
         dataready = i2cReadByte(handle);

         if((dataready & 0x08) == 0x08)      // Falls neue Daten Verfügbar
         {
             dataX_MSB = i2cReadByteData(handle,0x01);
             dataX_LSB = i2cReadByteData(handle,0x02);
             dataY_MSB = i2cReadByteData(handle,0x03);
             dataY_LSB = i2cReadByteData(handle,0x04);
             dataZ_MSB = i2cReadByteData(handle,0x05);
             dataZ_LSB = i2cReadByteData(handle,0x06);

             dataX = dataX_LSB + (dataX_MSB << 8);
             dataY = dataY_LSB + (dataY_MSB << 8);
             dataZ = dataZ_LSB + (dataZ_MSB << 8);

//             qDebug() << "X: " << dataX;
//             qDebug() << "Y: " << dataY;
//             qDebug() << "Z: " << dataZ;

             //Absolutwert und Wandlung in Double
             dataX_ABS = abs(dataX);
             dataZ_ABS = abs(dataZ);

             //Berechnung Tangens
             tangens = (dataX_ABS)/(dataZ_ABS);

             //Berechnung Winkel
             winkel = (atan(tangens))*180 / PI;
             //qDebug() << "atan: " << winkel;

             //Unterscheidung Quadrant
             if((dataZ >= 0) & (dataX >= 0))         // Rechts unten
                 winkel = winkel;
             else if((dataZ <= 0) & (dataX >= 0))    // Rechts oben
                 winkel = 180 - winkel;
             else if((dataZ <= 0) & (dataX <= 0))    // Links oben
                 winkel = 180 + winkel;
             else if((dataZ >= 0) & (dataX <= 0))    // Links unten
                 winkel = 360 - winkel ;

             //qDebug() << "Winkel: " << winkel;
             return winkel;
         }

         i2cClose(handle);

         gpioWrite(13,0);                    // MMA8491_EN = 0
         return 0;
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

void setFuelGaugeLEDs()
{
    int c = getCharge();
    if(c >= 80)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,1);
        gpioWrite(21,1);
    }
    else if(c >= 60 && c < 80)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,1);
        gpioWrite(21,0);
    }
    else if(c >= 40 && c < 60)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,1);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }
    else if(c >= 20 && c < 40)
    {
        gpioWrite(7,1);
        gpioWrite(12,1);
        gpioWrite(16,0);
        gpioWrite(20,0);
        gpioWrite(21,0);
    }
    else
    {
        gpioWrite(7,1);
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

