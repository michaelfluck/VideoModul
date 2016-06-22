#ifndef DATAAQUISITION_H
#define DATAAQUISITION_H

#include <QThread>
#include "camera.h"

class DataAquisition : public QThread
{
public:
    DataAquisition();
    ~DataAquisition();
    void run();
    bool getStatus();
    void doVideo();
private:
    Camera cam;
};

#endif // DATAAQUISITION_H
