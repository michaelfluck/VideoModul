#ifndef DATAAQUISITION_H
#define DATAAQUISITION_H

#include <QThread>
#include <QDebug>
#include "camera.h"
#include "picproc.h"


class DataAquisition : public QThread
{
public:
    DataAquisition();
    ~DataAquisition();
    void run();
    bool getStatus();
    void doVideo();
    void setConfig(int resolution, double fps);
private:
    Camera cam;
    double camSpeed;
};

#endif // DATAAQUISITION_H
