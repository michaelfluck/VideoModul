#ifndef LEDPROC_H
#define LEDPROC_H

#include <QThread>
#include <QDebug>

#include "gpio.h"

class LEDProc : public QThread
{
public:
    LEDProc();
    ~LEDProc();
    void run();
};

#endif // LEDPROC_H
