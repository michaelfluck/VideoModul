#include "dataaquisition.h"

DataAquisition::DataAquisition()
{
    qDebug() << "DataAquisition GO";
    fps = "10";
}

DataAquisition::~DataAquisition()
{
    qDebug() << "DataAquisition STOPP";
}

void DataAquisition::run()
{
    long unsigned int i = 0;

    //Konstantendeklaration
     const int PI = 3.14159265359;

     //Variablendeklaration
     int handle = 0;
     int dataready = 0;


    while(1)
    {
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

         handle = i2cOpen(1,0x55,0);

             i2cSwitchCombined(1);               // WICHTIG! Enable "Repeated Start"!!

             gpioWrite(13,1);                    // MMA8491_EN = 1
             gpioDelay(2000);                   // Ton (minimales Delay)

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

                 //Absolutwert und Wandlung in Double
                 dataX_ABS = abs(dataX);
                 dataZ_ABS = abs(dataZ);

                 //Berechnung Tangens
                 tangens = (dataX_ABS)/(dataZ_ABS);

                 //Berechnung Winkel
                 winkel = (atan(tangens))*180 / PI;

                 //Unterscheidung Quadrant
                 if((dataZ >= 0) & (dataX >= 0))         // Rechts unten
                     winkel = winkel;
                 else if((dataZ <= 0) & (dataX >= 0))    // Rechts oben
                     winkel = 180 - winkel;
                 else if((dataZ <= 0) & (dataX <= 0))    // Links oben
                     winkel = 180 + winkel;
                 else if((dataZ >= 0) & (dataX <= 0))    // Links unten
                     winkel = 360 - winkel ;
             }

        i2cClose(handle);

        gpioWrite(13,0);                    // MMA8491_EN = 0


        if (winkel < 6 || winkel > 355)
        {
            winkel = 0;
        }

        if(fps == "2")
        {
            if(i%5 == 0)
            {
                angleArray[(i/5)] = winkel;
            }
        }
        else if(fps == "30")
        {
            angleArray[i] = winkel;
            angleArray[++i] = winkel;
            angleArray[++i] = winkel;
        }
        else
        {
            angleArray[i] = winkel;
        }
        i++;  
        msleep(100);
    }
}

void DataAquisition::setConfig(std::string fps)
{
    this->fps = fps;
}
