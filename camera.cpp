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
    //cam_camera.open();
    cam_camera.grab();
    cam_camera.retrieve(cam_picture);
    //cam_camera.release();
    setLEDsOff();

    // Get Picture Number ready for String
    ostringstream number;
    number << cam_pictureNr;
    // Set Savepath and Naming for the Pictures
    string name = pictureSaveDestination + pictureName + number.str() + pictureExtension;
    imwrite(name, cam_picture);
    cam_pictureNr ++;
}

void Camera::initCam()
{
    cam_camera.set(CV_CAP_PROP_FORMAT,CV_8UC1);
    cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT,600);
    cam_camera.set(CV_CAP_PROP_FRAME_WIDTH,800);
    //cam_camera.set(CV_CAP_PROP_EXPOSURE,100);
    //cam_camera.set(CV_CAP_PROP_GAIN,100);
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
    int nr = cam_pictureNr;
    cam_pictureNr = 0;
    return nr;
}

void Camera::openCamera()
{
    qDebug() << "Opening Camera...";
    if(!cam_camera.open())
    {
        qDebug() << "Error at Opening Camera...";
    }
}

void Camera::closeCamera()
{
    qDebug() << "Close Camera...";
    cam_camera.release();
}
