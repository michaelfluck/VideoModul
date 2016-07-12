#ifndef DATAAQUISITION_H
#define DATAAQUISITION_H

#include <QThread>
#include <QDebug>

#include "gpio.h"

class DataAquisition : public QThread
{
public:
    DataAquisition();
    ~DataAquisition();
    void run();
    int angleArray[1000000];
    void setConfig(std::string fps);
private:
    std::string fps;

};

#endif // DATAAQUISITION_H
