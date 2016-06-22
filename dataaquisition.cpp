#include "dataaquisition.h"
#include <QDebug>

DataAquisition::DataAquisition()
{
    qDebug() << "DataAquisition GO";
}

void DataAquisition::run()
{
    for (int i = 0; i < 10; ++i) {
        qDebug() << i;
    }
}
