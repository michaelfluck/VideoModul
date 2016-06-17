#include "picproc.h"
#include "const_global.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace cv;
using namespace std;

int procPictures()
{
    Mat picture;
    string src, dest;
    for (int i = 0; i < 8; i++)
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

        //Bilder speichern
        dest =  pictureProcDestination + pictureName + number.str() + pictureExtension;
        imwrite(dest, picture);


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
    Point org(50,500);
    Scalar color = Scalar(0,0,255);
    putText(srcPicture,"BA rulez!",org,FONT_HERSHEY_SIMPLEX,3,color,4,8);

    return textedPicture;
}
