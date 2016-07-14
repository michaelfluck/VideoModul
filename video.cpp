#include "video.h"

using namespace std;

Video::Video()
{
    qDebug() << "Video GO";
    videoStatus = false;
    fps = "2";
    resolution = 800;
    offsetBlende = "0";
}

Video::~Video()
{
    qDebug() << "Video STOPP";
    system("sudo pkill raspivid");
}

void Video::run()
{
    if(videoStatus == false)
    {
        videoStatus = true;
        QDir dir(rawVideoPath);
        QString dirFile;
        foreach(dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }

        if(resolution == 1024)
        {
            befehl = "raspivid -t 999999 -n -fps " + fps +" -o " + rawVideo + " -w 1024 -h 786 -awb flash -ev " + offsetBlende;
        }
        else if(resolution == 800)
        {
            befehl = "raspivid -t 999999 -n -fps " + fps +" -o " + rawVideo + " -w 800 -h 600 -awb flash -ev " + offsetBlende;
        }
        else
        {
            befehl = "raspivid -t 999999 -n -fps " + fps +" -o " + rawVideo + " -w 640 -h 480 -awb flash -ev " + offsetBlende;
        }
        system(befehl.c_str());

    }
}

bool Video::getStatus()
{
    return videoStatus;
}

void Video::stopVideo()
{
        videoStatus = false;
        system("sudo pkill raspivid");
        if(fps == "2")
        {
            befehl = "MP4Box -fps 20 -add " + rawVideo + " " + prepVideo;
        }
        else if(fps == "10")
        {
            befehl = "MP4Box -fps 20 -add " + rawVideo + " " + prepVideo;
        }
        else
        {
            befehl = "MP4Box -fps 30 -add " + rawVideo + " " + prepVideo;
        }
        system(befehl.c_str());
}

void Video::setConfig(string fps, int resolution, string offsetBlende)
{
    this->fps = fps;
    this->resolution = resolution;
    this->offsetBlende = offsetBlende;
}
