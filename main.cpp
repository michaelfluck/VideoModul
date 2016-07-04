#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QString>
#include <QtCore>

#include "camera.h"
#include "gpio.h"
#include "dataaquisition.h"
#include "picproc.h"
#include "const_global.h"
#include "xmlreader.h"
#include "video.h"

using namespace std;


DataAquisition dataaq;
xmlReader xmlreader;
Video video;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    cout << "VideoModul" << endl;
    States s = INIT;
    QDir dir("/home/pi/Desktop/Testbilder");
    QString dirFile;

    while(1){
        switch(s){
                case INIT:
                    qDebug() << "STATUS -> INITI";
                    gpioInit();
                    initFuelGauge();
                    setChargeFull(); //nur für Test der FuelGauge
                    s = WAIT;
                    break;

                case ENGAGE:
                    //qDebug() << "STATUS -> ENGAGE";
                    if((xmlreader.getStatus() == true) || (getVideoOnOff() == true))
                    {
                        if(video.getStatus() == true)
                        {
                        }else
                        {
                            foreach(dirFile, dir.entryList())
                            {
                                dir.remove(dirFile);
                            }
                            setLEDsOn();
                            video.setConfig(xmlreader.getFPS(), xmlreader.getResolution());
                            video.start(QThread::HighestPriority);
                        }
                        s = ENGAGE;
                    }else{
                        setLEDsOff();
                        video.stopVideo();
                        s = WAIT;
                    }
                    break;

                case SHUTDOWN:
                    qDebug() << "STATUS -> SHUTDOWN";
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
                        setFuelGaugeLEDs();
                        s = WAIT;
                    }

                    break;

                default:
                    qDebug() << "STATUS -> DEFAULT";
                    break;
        }
    }
    return app.exec();
}
