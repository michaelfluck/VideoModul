#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "camera.h"
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
                    s = WAIT;
                    break;

                case ENGAGE:
                    qDebug() << "STATUS -> ENGAGE";
                    if(xmlreader.getStatus() == true)
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
                        qDebug() << "DoVideo start";
                        dataaq.doVideo();
                        s = WAIT;
                    }
                    break;

                case SHUTDOWN:
                    qDebug() << "STATUS -> SHUTDOWN";
                    break;

                case WAIT:
                    qDebug() << "STATUS -> WAIT";
                    if(xmlreader.getStatus() == true)
                    {
                        s = ENGAGE;
                    }else{
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
