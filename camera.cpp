#include "camera.h"

using namespace cv;
using namespace std;

Camera::Camera()
{
    qDebug() << "Camera GO";
    cam_pictureNr = 0;
    initCam();
}

Camera::~Camera()
{
    qDebug() << "Camera STOPP";
}

bool Camera::getStatus()
{
    return cam_camera.isOpened();
}

void Camera::getPicture()
{
    setLEDsOn();
    cam_camera.open();
    for (int i = 0; i < 2; i++) {
        cam_camera.grab();
        cam_camera.retrieve(cam_picture);
    }
    cam_camera.release();
    setLEDsOff();

    // Get Picture Number ready for String
    ostringstream number;
    number << cam_pictureNr;

    //Bild drehen
    //cam_picture = turnPicture(cam_picture, getAngle());

    // Set Savepath and Naming for the Pictures
    string name = pictureSaveDestination + pictureName + number.str() + pictureExtension;
    imwrite(name, cam_picture);
    cam_pictureNr ++;
}

void Camera::initCam()
{
    cam_camera.set(CV_CAP_PROP_FORMAT,CV_8UC3);
    cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT,600);
    cam_camera.set(CV_CAP_PROP_FRAME_WIDTH,800);
    cam_camera.set(CV_CAP_PROP_EXPOSURE,-1); //Shutter on 33ms (Maximum)
    //cam_camera.set(CV_CAP_PROP_GAIN,50); //ISO Wert
    //cam_camera.set(CV_CAP_PROP_WHITE_BALANCE_RED_V, 50);
    //cam_camera.set(CV_CAP_PROP_WHITE_BALANCE_BLUE_U, -1);
}

void Camera::setResolution(int resolution)
{
    if(resolution == 1024)
    {
        cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT, 768);
        cam_camera.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
    }
    else if(resolution == 800)
    {
        cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
        cam_camera.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    }
    else if(resolution == 640)
    {
        cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        cam_camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    }
}

int Camera::getPictureNr()
{
    return cam_pictureNr;
}

void Camera::setPictureNrToZero()
{
    cam_pictureNr = 0;
}

Mat Camera::turnPicture(Mat srcPicture, double angle)
{
    Mat turnedPicture;
    Point2f pt(srcPicture.cols/2.,srcPicture.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1);
    warpAffine(srcPicture, turnedPicture, r, Size(srcPicture.cols, srcPicture.rows));

    return turnedPicture;
}
