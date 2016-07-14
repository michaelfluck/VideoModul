#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QXmlStreamWriter>
#include <QFile>

#include "gpio.h"

class FuelGauge : public QThread
{
public:
    FuelGauge();
    ~FuelGauge();
    void run();
};

#endif // FUELGAUGE_H
