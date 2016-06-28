#include "picproc.h"
#include "xmlreader.h"
#include "const_global.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iomanip>
#include <QDir>

using namespace cv;
using namespace std;

std::string op;
std::string start;
std::string ziel;
std::string datum;

int procPictures(int pictureNr)
{
    Mat picture;
    string src, dest;
    VideoWriter outputVideo;
    readTextToAdd();
    outputVideo.open(videoPath,CV_FOURCC_DEFAULT,1,Size(800,600),true);

    for (int i = pictureNr - 1 ; i >= 0; i--)
    {
        ostringstream number;
        number << i;

        //Bilder einlesen

        src = pictureSaveDestination + pictureName + number.str() + pictureExtension;
        qDebug() << QString::fromLocal8Bit(src.c_str());
        picture = imread(src, CV_LOAD_IMAGE_COLOR);

        //Drehen
        //picture = turnPicture(picture, 180);

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

Mat turnPicture(Mat srcPicture, double angle)
{
    Mat turnedPicture;
    Point2f pt(srcPicture.cols/2.,srcPicture.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1);
    warpAffine(srcPicture, turnedPicture, r, Size(srcPicture.cols, srcPicture.rows));

    return turnedPicture;
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
}
