#ifndef VIDEO_H
#define VIDEO_H

#include <QThread>
#include <QDir>

#include "const_global.h"

class Video : public QThread
{
public:
    Video();
    ~Video();
    void run();
    bool getStatus();
    void stopVideo();
    void setConfig(std::string fps, int resolution, std::string offsetBlende);
private:
    bool videoStatus;
    std::string fps;
    std::string befehl;
    int resolution;
    std::string offsetBlende;
};

#endif // VIDEO_H
