#ifndef VIDEO_H
#define VIDEO_H
/*  --------------------------------------------------------------------------
*   Title:      NTB Bachelorarbeit "VideoModul für ein Kanalreinigungssystem"
*   Autor:      M.Fluck, S.Lutz
*   Datum:      01.07.2016
*   Version:    1.0
*   Zweck:      Aufnehmen der Video-Rohdaten und erstellen des Preview-Videos
    --------------------------------------------------------------------------*/

#include <QThread>
#include <QDir>

#include "const_global.h"

class Video : public QThread
{
public:
    Video();
    ~Video();
    void run();

    /*  bool getStatus
    *   Desc:       Status Videoaufnahme
    *   Parameter:  -
    *   Return:     True = On , False = Off
    */
    bool getStatus();

    /*  void stopVideo
    *   Desc:       Stoppen der Videoaufnahme und erstellen des Preview-Videos
    *   Parameter:  -
    *   Return:     -
    */
    void stopVideo();

    /*  void setConfig
    *   Desc:       Setzen der Video Einstellungen
    *   Parameter:  fps - Frames per Second, resolution - Auflösungshöhe, offsetBlende - [-10 .. +10]
    *   Return:     -
    */
    void setConfig(std::string fps, int resolution, std::string offsetBlende);

private:
    bool videoStatus;
    std::string fps;
    std::string befehl;
    int resolution;
    std::string offsetBlende;
};

#endif // VIDEO_H
