#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "camera.h"
#include "dataaquisition.h"
#include "picproc.h"
#include "const_global.h"
#include "xmlreader.h"

using namespace std;

void init()
{
    Camera cam;

}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    cout << "VideoModul" << endl;
    States s = INIT;
    DataAquisition dataaq;
    xmlReader xmlreader;


    while(1){
        switch(s){
                case INIT:
                    cout << "Initialisiere" << endl;
                    init();

                    s = WAIT;
                    break;

                case ENGAGE:

                    dataaq.start();
                    bool status;
                    status = xmlreader.getStatus();
                    cout << status << endl;
                    s = WAIT;
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
