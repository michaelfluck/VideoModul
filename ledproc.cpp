#include "ledproc.h"

LEDProc::LEDProc()
{
    qDebug() << "LEDProc GO";
}

LEDProc::~LEDProc()
{
    qDebug() << "LEDProc STOPP";
}

void LEDProc::run()
{
    while(1)
    {
        setFuelGaugeLEDs(100);
        msleep(500);
        setFuelGaugeLEDs(0);
        msleep(500);
    }
}
