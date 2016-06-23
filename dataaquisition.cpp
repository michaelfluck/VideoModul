#include "dataaquisition.h"
#include "picproc.h"
#include <QDebug>




DataAquisition::DataAquisition()
{
    qDebug() << "DataAquisition GO";
    Camera cam;
}

DataAquisition::~DataAquisition()
{

}

void DataAquisition::run()
{
    qDebug() << "DataAquisition läuft..";
    sleep(1);
    cam.getPicture();
    while(cam.getStatus()==true)
    {}
}

bool DataAquisition::getStatus()
{
    return cam.getStatus();
}

void DataAquisition::doVideo()
{
    procPictures();
}
