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
    qDebug() << "DataAquisition STOPP";
}

void DataAquisition::run()
{
    qDebug() << "Bild aufnehmen...";
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
    qDebug() << cam.getPictureNr();
    procPictures(cam.getPictureNr());
}

void DataAquisition::setConfig(int resolution, int fps)
{
    cam.setResolution(resolution);
}
