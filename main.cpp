#include <QCoreApplication>
#include <QtCore>

#include "camera.h"
#include "gpio.h"
#include "dataaquisition.h"
#include "picproc.h"
#include "const_global.h"
#include "xmlreader.h"
#include "video.h"
#include "fuelgauge.h"
#include "ledproc.h"

using namespace std;


DataAquisition dataaq;
xmlReader xmlreader;
Video video;
FuelGauge fuel;
LEDProc procled;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    States s = INIT;

    while(1){
        switch(s){
                case INIT:
                    qDebug() << "STATUS -> INITI";
                    gpioInit();
                    initFuelGauge();
                    fuel.start(QThread::LowPriority);
                    s = WAIT;
                    break;

                case ENGAGE:
                    //qDebug() << "STATUS -> ENGAGE";
                    if(emptyCheck() == true)
                    {
                        setLEDsOff();
                        video.stopVideo();
                        dataaq.terminate();
                        s = SHUTDOWN;
                    }

                    if((xmlreader.getStatus() == true) || (getVideoOnOff() == true))
                    {
                        if(video.getStatus() == false)
                        {
                            setLEDsOn();
                            video.setConfig(xmlreader.getFPS(), xmlreader.getResolution(), xmlreader.getOffsetBlende());
                            dataaq.setConfig(xmlreader.getFPS());
                            video.start(QThread::NormalPriority);
                            dataaq.start(QThread::HighestPriority);

                        }
                        s = ENGAGE;
                    }else{
                        setLEDsOff();
                        video.stopVideo();
                        dataaq.terminate();
                        procled.start(QThread::LowPriority);
                        s = PROCESSING;
                    }
                    break;

                case PROCESSING:
                    qDebug() << "STATUS -> PROCESSING";
                    procPictures(dataaq.angleArray);
                    releaseVideo();
                    procled.terminate();
                    dataaq.setReset();
                    setFuelGaugeLEDs(getCharge());
                    s = WAIT;
                    break;

                case SHUTDOWN:
                    qDebug() << "STATUS -> SHUTDOWN";
                    if(emptyCheck() == true)
                    {
                        setChargeEmpty();
                        for (int i = 5; i >= 0; i--) {
                            setFuelGaugeLEDs(i*20);
                            gpioDelay(500000);
                        }
                    }
                    system("sudo shutdown now");
                    break;

                case WAIT:
                    //qDebug() << "STATUS -> WAIT";
                    if((xmlreader.getStatus() == true) || (getVideoOnOff() == true))
                    {
                        s = ENGAGE;
                    }else if((getOnOff() == true) || (emptyCheck() == true)){   
                        s = SHUTDOWN;
                    }else
                    {
                        s = WAIT;
                    }
                    break;
        }
    }
    return app.exec();
}
