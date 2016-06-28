#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <QString>

#include "camera.h"
#include "gpio.h"
#include "dataaquisition.h"
#include "picproc.h"
#include "const_global.h"
#include "xmlreader.h"

using namespace std;


DataAquisition dataaq;
xmlReader xmlreader;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    cout << "VideoModul" << endl;
    States s = INIT;

    while(1){
        switch(s){
                case INIT:
                    qDebug() << "STATUS -> INIT";
                    gpioInit();
                    s = WAIT;
                    break;

                case ENGAGE:
                    //qDebug() << "STATUS -> ENGAGE";
                    if((xmlreader.getStatus() == true) || (getVideoOnOff() == true))
                    {
                        if(dataaq.getStatus() == true)
                        {

                        }else{
                            dataaq.start(QThread::HighestPriority);
                        }
                        s = ENGAGE;
                    }else{
                        dataaq.quit();
                        dataaq.wait(1000);
                        qDebug() << "Film wird erstellt";
                        dataaq.doVideo();
                        qDebug() << "Film FERTIG";
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
                    }else if(getOnOff() == true){
                        s = SHUTDOWN;
                    }else
                    {
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
