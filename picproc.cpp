#include "picproc.h"

using namespace cv;
using namespace std;

string op;
string start;
string ziel;
string datum;
int aufloesung;
int fps;

void procPictures(int angleArray[])
{
    readTextToAdd();
    std::string befehl = "sudo cp " + prepVideo + " " + releaseVideoPath + start + "-" + ziel + "-Preview.mp4";
    system(befehl.c_str());
    VideoCapture cap(prepVideo);
    if(!cap.isOpened())
    {
        qDebug() << "Fehler beim Oeffnen von prepVideo";
    }

    int frameCounter = cap.get(CV_CAP_PROP_FRAME_COUNT);
    Mat frame;
    fps = cap.get(CV_CAP_PROP_FPS);

    for (int i = frameCounter-1 ; i >= 0 ; i--)
    {
        //cap.set(CV_CAP_PROP_POS_FRAMES, i);
        qDebug() << "Frame: " << i;
        cap >> frame;

        qDebug() << "Drehung um: " << angleArray[i];
        frame = turnPicture(frame, angleArray[i]);

        //Text hinzufügen
        frame = addText(frame);

        ostringstream num;

        if(i < 10)
        {
            num << "0";
        }
        if(i < 100)
        {
            num << "0";
        }
        if(i < 1000)
        {
            num << "0";
        }
        if(i < 10000)
        {
            num << "0";
        }
        if(i < 100000)
        {
            num << "0";
        }
        num << (i);
        imwrite(pictureProcDestination + pictureName + num.str() + pictureExtension, frame);
    }
}

Mat addText(Mat frame)
{    
    Point orgDate(10, 20);
    Point orgTextLeft(10, 50);
    Point orgTextMiddle(10, 80);
    Point orgTextRight(10, 110);


    //Text einfügen
    putText(frame,"Benutzer: " + op ,orgTextLeft,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(frame,"Start: " + start,orgTextMiddle,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(frame,"Ziel: " + ziel,orgTextRight,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    putText(frame,"Datum: " +datum,orgDate,FONT_HERSHEY_SIMPLEX,0.8,textColor,2,8);
    return frame;
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

Mat turnPicture(Mat srcPicture, double angle)
{
    Mat turnedPicture;
    Point2f pt(srcPicture.cols/2.,srcPicture.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1);
    warpAffine(srcPicture, turnedPicture, r, Size(srcPicture.cols, srcPicture.rows));

    return turnedPicture;
}

void releaseVideo()
{
    ostringstream sfps;
    sfps << fps;
    std::string befehl = "/home/pi/bin/ffmpeg -i /home/pi/Desktop/Proc/img%06d.jpg -framerate " + sfps.str() + " -vcodec libx264 -crf 25 " + releaseVideoPath + start + "-" + ziel + ".mp4";
    system(befehl.c_str());

}
