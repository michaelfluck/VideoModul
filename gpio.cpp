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
    gpioWrite(7,1);
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

void setFuelGauge(int fuel)
{

}
