#ifndef XMLREADER_H
#define XMLREADER_H
/*  --------------------------------------------------------------------------
*   Title:      NTB Bachelorarbeit "VideoModul für ein Kanalreinigungssystem"
*   Autor:      M.Fluck, S.Lutz
*   Datum:      01.07.2016
*   Version:    1.0
*   Zweck:      Auslesen von XML-Files welche über das Webinterface 
*               geschrieben werden.
    --------------------------------------------------------------------------*/
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

#include "const_global.h"

class xmlReader
{
public:
    //Konstruktor & Dekonstruktor
    xmlReader();
    ~xmlReader();
    
    /*  bool getStatus
    *   Desc:       Status Videoaufnahme (WebInterface)
    *   Parameter:  -
    *   Return:     True = On , False = Off
    */
    bool getStatus();
    
    /*  int getResolution
    *   Desc:       Eingestellte Auflösung (WebInterface)
    *   Parameter:  -
    *   Return:     1024 = 1024x768 , 800 = 800x600 , 600 = 600x480
    */
    int getResolution();
    
    /*  string getFPS
    *   Desc:       Eingestellte FPS (WebInterface)
    *   Parameter:  -
    *   Return:     30 , 10 , 2
    */
    std::string getFPS();
    
    /*  QString getOperator
    *   Desc:       Eingestellter Name des Benutzers (WebInterface)
    *   Parameter:  -
    *   Return:     String Freitext
    */
    QString getOperator();
    
    /*  QString getStart
    *   Desc:       Eingestellter Startschacht (WebInterface)
    *   Parameter:  -
    *   Return:     String Freitext
    */    
    QString getStart();
    
    /*  QString getZiel
    *   Desc:       Eingestellter Zielschacht (WebInterface)
    *   Parameter:  -
    *   Return:     String Freitext
    */   
    QString getZiel();
    
    /*  QString getDatum
    *   Desc:       Eingestelltes Datum (WebInterface)
    *   Parameter:  -
    *   Return:     String Freitext
    */     
    QString getDatum();
    
    /*  string getOffsetBlende
    *   Desc:       Eingestellter Schachttyp (WebInterface)
    *   Parameter:  -
    *   Return:     hell = -5 , normal = 0 , dunkel = 5
    */ 
    std::string getOffsetBlende();
private:
    QFile file;
    QXmlStreamReader reader;
    QString readElement;
};

#endif // XMLREADER_H
