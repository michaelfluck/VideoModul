#ifndef CONST_GLOBAL_H
#define CONST_GLOBAL_H

#include <string>
#include <QString>



const std::string pictureName               =       "images";
const std::string pictureExtension          =       ".jpg";
const std::string pictureSaveDestination    =       "/home/pi/Desktop/Testbilder/";
const std::string pictureProcDestination    =       "/home/pi/Desktop/Proc/";
const std::string videoPath                 =       "/var/www/html/video/Film.avi";

const std::string textToAddOperator         =       "M.Fluck";
const std::string textToAddDestination      =       "NTB";
const std::string textToAddFree             =       "FreeText";
const std::string textToAddDate             =       "20.06.2016";

const QString configXML                     =       "/var/www/html/config/config.xml";
const QString onoffXML                      =       "/var/www/html/config/onoff.xml";

enum States {
    INIT,
    ENGAGE,
    SHUTDOWN,
    WAIT
};

#endif // CONST_GLOBAL_H
