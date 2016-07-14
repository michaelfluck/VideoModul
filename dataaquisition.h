#ifndef DATAAQUISITION_H
#define DATAAQUISITION_H

#include <QThread>
#include <QDebug>
#include <QElapsedTimer>

#include "gpio.h"

class DataAquisition : public QThread
{
public:
    DataAquisition();
    ~DataAquisition();
    void run();
    int angleArray[1000000];
    void setConfig(std::string fps);
    void setReset();
private:
    std::string fps;
    long unsigned int i;
        QElapsedTimer t;
};

#endif // DATAAQUISITION_H
