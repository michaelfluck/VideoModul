#ifndef CONST_GLOBAL_H
#define CONST_GLOBAL_H

#include <string>

#include <QString>
#include <QDebug>

#include <opencv2/core/core.hpp>

const std::string pictureName               =       "img";
const std::string pictureExtension          =       ".jpg";
const std::string pictureSaveDestination    =       "/home/pi/Desktop/Testbilder/";
const QString pictureDestination            =       "/home/pi/Desktop/Testbilder/";
const std::string pictureProcDestination    =       "/home/pi/Desktop/Proc/";


const QString rawVideoPath                  =       "/home/pi/Videos";
const std::string rawVideo                  =       "/home/pi/Videos/rawVideo.h264";
const std::string prepVideo                 =       "/home/pi/Videos/prepVideo.mp4";
const std::string procVideo                 =       "/home/pi/Videos/procVideo.avi";
const std::string releaseVideoPath          =       "/var/www/html/video/";

const QString configXML                     =       "/var/www/html/config/config.xml";
const QString onoffXML                      =       "/var/www/html/config/onoff.xml";

const cv::Scalar textColor                  =       cv::Scalar(0,0,255);

enum States {
    INIT,
    ENGAGE,
    SHUTDOWN,
    WAIT,
    PROCESSING
};

#endif // CONST_GLOBAL_H
