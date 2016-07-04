#include "dataaquisition.h"

DataAquisition::DataAquisition()
{
    qDebug() << "DataAquisition GO";
    camSpeed = 1.0;
}

DataAquisition::~DataAquisition()
{

    qDebug() << "DataAquisition STOPP";
}

void DataAquisition::run()
{
    sleep(camSpeed);
    cam.getPicture();
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
