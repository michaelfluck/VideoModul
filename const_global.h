#ifndef CONST_GLOBAL_H
#define CONST_GLOBAL_H

#include <string>


const std::string pictureName               =       "images";
const std::string pictureExtension          =       ".jpg";
const std::string pictureSaveDestination    =       "/home/pi/Desktop/Testbilder/";
const std::string pictureProcDestination    =       "/home/pi/Desktop/Proc/";

const std::string textToAdd                 =       "Hallo Welt";

const std::string configXML                 =       "/var/www/html/config/config.xml";

enum States {
    INIT,
    ENGAGE,
    SHUTDOWN,
    WAIT
};

#endif // CONST_GLOBAL_H
