#include "picproc.h"

using namespace cv;
using namespace std;

string op;
string start;
string ziel;
string datum;
int aufloesung;

int procPictures(int pictureNr)
{
    Mat picture;
    string src, dest;
    VideoWriter outputVideo;
    QDateTime dateTime = QDateTime::currentDateTime();
    readTextToAdd();
    string filmname = videoPath + "Film " + (dateTime.toString("dd-MM-yyyy hh:mm")).toAscii().constData() + ".avi";

    if(aufloesung == 1024)
    {
        outputVideo.open(filmname,CV_FOURCC_DEFAULT,1,Size(1024,768),true);
    }
    else if(aufloesung == 800)
    {
        outputVideo.open(filmname,CV_FOURCC_DEFAULT,1,Size(800,600),true);
    }
    else
    {
        outputVideo.open(filmname,CV_FOURCC_DEFAULT,1,Size(640,480),true);
    }

    for (int i = pictureNr - 1 ; i >= 0; i--)
    {
        ostringstream number;
        number << i;

        //Bilder einlesen
        src = pictureSaveDestination + pictureName + number.str() + pictureExtension;
        picture = imread(src, CV_LOAD_IMAGE_COLOR);

        //Text hinzufügen
        addText(picture);

        //Video erstellen
        outputVideo.write(picture);

        //Bilder speichern
        //dest =  pictureProcDestination + pictureName + number.str() + pictureExtension;
        //imwrite(dest, picture);
    }
    outputVideo.release();

    // Alle Bilder löschen
    QDir dir(pictureDestination);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
    return 0;

}

Mat addText(Mat srcPicture)
{    
    Mat textedPicture;
    Point orgTextLeft(10, 580);
    Point orgTextMiddle(350, 580);
    Point orgTextRight(600, 580);
    Point orgDate(10, 25);

    //Text einfügen
    putText(srcPicture,"Benutzer: " + op ,orgTextLeft,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(srcPicture,"Start: " + start,orgTextMiddle,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(srcPicture,"Ziel: " + ziel,orgTextRight,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(srcPicture,datum,orgDate,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    return textedPicture;
}

void readTextToAdd()
{
    xmlReader xmlreader;
    //QStrings aus XML auslesen und umwandeln
    QString qoperator = xmlreader.getOperator();
    op = qoperator.toAscii().constData();
    QString qstart = xmlreader.getStart();
    start = qstart.toAscii().constData();
    QString qziel = xmlreader.getZiel();
    ziel = qziel.toAscii().constData();
    QString qdatum = xmlreader.getDatum();
    datum = qdatum.toAscii().constData();

    //Videoauflösung setzen
    aufloesung = xmlreader.getResolution();

}

