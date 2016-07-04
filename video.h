#ifndef VIDEO_H
#define VIDEO_H

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include "const_global.h"

class Video : public QThread
{
public:
    Video();
    ~Video();
    void run();
    bool getStatus();
    void stopVideo();
    void setConfig(std::string fps, int resolution);
private:
    bool videoStatus;
    std::string fps;
    std::string befehl;
    double speed;
    int resolution;
    QDateTime dateTime;
};

#endif // VIDEO_H
