#include "picproc.h"
#include "const_global.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iomanip>
#include <ctime>


using namespace cv;
using namespace std;

int procPictures()
{
    Mat picture;
    string src, dest;
    VideoWriter outputVideo;
    outputVideo.open(videoPath,CV_FOURCC_DEFAULT,1,Size(800,600),true);

    for (int i = 0; i < 20; i++)
    {
        ostringstream number;
        number << i;

        //Bilder einlesen
        src = pictureSaveDestination + pictureName + number.str() + pictureExtension;
        picture = imread(src, CV_LOAD_IMAGE_COLOR);

        //Drehen
        picture = turnPicture(picture, 180);

        //Text hinzufügen
        addText(picture);

        //Video erstellen
        outputVideo.write(picture);


        //Bilder speichern
        //dest =  pictureProcDestination + pictureName + number.str() + pictureExtension;
        //imwrite(dest, picture);
    }
    outputVideo.release();
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
    Scalar color = Scalar(0,0,255);
    //Text einfügen
    putText(srcPicture,"Operator:" + textToAddOperator,orgTextLeft,FONT_HERSHEY_SIMPLEX,1,color,2,8);
    putText(srcPicture,"Ort:" + textToAddDestination,orgTextMiddle,FONT_HERSHEY_SIMPLEX,1,color,2,8);
    putText(srcPicture,"T:" + textToAddFree,orgTextRight,FONT_HERSHEY_SIMPLEX,1,color,2,8);
    // Datum einfügen
    putText(srcPicture,textToAddDate,orgDate,FONT_HERSHEY_SIMPLEX,1,color,2,8);
    return textedPicture;
}
