#ifndef CONST_GLOBAL_H
#define CONST_GLOBAL_H

#include <string>
#include <QString>



const std::string pictureName               =       "images";
const std::string pictureExtension          =       ".jpg";
const std::string pictureSaveDestination    =       "/home/pi/Desktop/Testbilder/";
const QString pictureDestination             =      "/home/pi/Desktop/Testbilder/";
const std::string pictureProcDestination    =       "/home/pi/Desktop/Proc/";
const std::string videoPath                 =       "/var/www/html/video/Film.avi";

const QString configXML                     =       "/var/www/html/config/config.xml";
const QString onoffXML                      =       "/var/www/html/config/onoff.xml";

enum States {
    INIT,
    ENGAGE,
    SHUTDOWN,
    WAIT
};

#endif // CONST_GLOBAL_H
