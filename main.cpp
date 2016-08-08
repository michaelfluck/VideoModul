#include <QCoreApplication>
#include <QtCore>

#include "gpio.h"
#include "dataaquisition.h"
#include "picproc.h"
#include "const_global.h"
#include "xmlreader.h"
#include "video.h"
#include "fuelgauge.h"
#include "ledproc.h"

using namespace std;

// Erstellen aller benötigten Objekte
DataAquisition dataaq;
XMLReader xmlreader;
Video video;
FuelGauge fuel;
LEDProc procled;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    States s = INIT;

    // Hauptschleife wird nie verlassen
    while(1){
        switch(s){
                case INIT:
                    gpioInit();
                    initFuelGauge();
                    fuel.start(QThread::LowPriority);
                    s = WAIT;
                    break;

                case ENGAGE:
                    // Wenn die Akkuspannung kritisch ist, wird die Aufnahme beendet
                    if(emptyCheck() == true)
                    {
                        setLEDsOff();
                        video.stopVideo();
                        dataaq.terminate();
                        s = SHUTDOWN;
                    }
                    // Prüfen ob Aufnahme gestartet wurde (Magnetisch oder per Webinterface)
                    if((xmlreader.getStatus() == true) || (getVideoOnOff() == true))
                    {
                        // Starten der Videoaufnahme
                        if(video.getStatus() == false)
                        {
                            setLEDsOn();
                            video.setConfig(xmlreader.getFPS(), xmlreader.getResolution(), xmlreader.getOffsetBlende());
                            dataaq.setConfig(xmlreader.getFPS());
                            video.start(QThread::NormalPriority);
                            dataaq.start(QThread::HighestPriority);

                        }
                        s = ENGAGE;
                    // Beenden der Aufnahme und Starten der Verarbeitung
                    }else{
                        setLEDsOff();
                        video.stopVideo();
                        dataaq.terminate();
                        procled.start(QThread::LowPriority);
                        s = PROCESSING;
                    }
                    break;
                // Verarbeitung der Video-Rohdaten
                case PROCESSING:
                    procPictures(dataaq.angleArray);
                    releaseVideo();
                    procled.terminate();
                    dataaq.setReset();
                    setFuelGaugeLEDs(getCharge());
                    s = WAIT;
                    break;
                // Abschalten des Systems mit LED-Blinksequenz
                case SHUTDOWN:
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
                // Warten auf Einsatz oder Abschalten bei kritischer Akkuspannung
                case WAIT:
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
