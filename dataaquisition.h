#ifndef DATAAQUISITION_H
#define DATAAQUISITION_H

#include <QThread>

class DataAquisition : public QThread
{
public:
    DataAquisition();
    void run();
};

#endif // DATAAQUISITION_H
