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
    bool videostatus = 0;
    States s = INIT;

    dataaq.start();

    while(1){
        switch(s){
                case INIT:
                    cout << "Initialisiere" << endl;
                    s = ENGAGE;
                    break;

                case ENGAGE:
                    videostatus = xmlreader.getStatus();
                    qDebug() << videostatus;
                    if(videostatus == 1)
                    {
                        qDebug() << "Aufnahme läuft";
                        s = ENGAGE;
                    }else{
                        s = WAIT;
                    }
                    break;

                case SHUTDOWN:
                    cout << "Shutdown" << endl;
                    break;

                case WAIT:
                    //cout << "Wait" << endl;
                    s = WAIT;
                    break;

                default:
                    cout << "Default Case!" << endl;
                    break;
        }
    }
    return app.exec();
}
