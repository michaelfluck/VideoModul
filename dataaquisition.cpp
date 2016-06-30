#include "dataaquisition.h"

DataAquisition::DataAquisition()
{
    qDebug() << "DataAquisition GO";
}

DataAquisition::~DataAquisition()
{

    qDebug() << "DataAquisition STOPP";
}

void DataAquisition::run()
{
    sleep(1);
    cam.getPicture();
    qDebug() << "Bilder aufnehmen...";
}

bool DataAquisition::getStatus()
{
    return cam.getStatus();
}

void DataAquisition::doVideo()
{
    qDebug() << cam.getPictureNr();
    procPictures(cam.getPictureNr());
    cam.setPictureNrToZero();
}

void DataAquisition::setConfig(int resolution, int fps)
{
    cam.setResolution(resolution);
}
