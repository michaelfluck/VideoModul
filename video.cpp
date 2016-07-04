#include "video.h"

using namespace std;

Video::Video()
{
    qDebug() << "Video GO";
    videoStatus = false;
    fps = "1";
    speed = 10;
    resolution = 800;
}

Video::~Video()
{
    qDebug() << "Video STOPP";
}

void Video::run()
{
    if(videoStatus == false)
    {
        videoStatus = true;
        if(resolution == 1024)
        {
            befehl = "raspivid -t 999999 -fps " + fps +" -o " + pictureSaveDestination + "video.h264 -w 1024 -h 786";
        }
        else if(resolution == 800)
        {
            befehl = "raspivid -t 999999 -fps " + fps +" -o " + pictureSaveDestination + "video.h264 -w 800 -h 600";
        }
        else
        {
            befehl = "raspivid -t 999999 -fps " + fps +" -o " + pictureSaveDestination + "video.h264 -w 640 -h 480";
        }
        system(befehl.c_str());
    }
    else
    {
        qDebug() << "Aufnahme läuft";
    }

}

bool Video::getStatus()
{
    return videoStatus;
}

void Video::stopVideo()
{
        videoStatus = false;
        system("pkill raspivid");
        double cspeed = speed * (atof(fps.c_str()));
        dateTime = QDateTime::currentDateTime();
        ostringstream sspeed;
        sspeed << cspeed;
        befehl = "MP4Box -fps " + sspeed.str() + " -add " + pictureSaveDestination + "video.h264 /var/www/html/video/Aufnahme_" + (dateTime.toString("dd-MM-yyyy_hh:mm:ss")).toAscii().constData() + ".mp4";
        system(befehl.c_str());
}

void Video::setConfig(string fps, int resolution)
{
    this->fps = fps;
    this->resolution = resolution;
}
