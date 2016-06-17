#include "camera.h"


using namespace cv;
using namespace std;

Camera::Camera()
{
    cam_enable = cam_camera.isOpened();
    cam_pictureNr = 0;
    initCam();
}

Camera::~Camera()
{

}


void Camera::getPicture()
{
    cam_camera.open();
    cam_camera.grab();
    cam_camera.retrieve(cam_picture);
    cam_camera.release();

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
    cam_camera.set(CV_CAP_PROP_FORMAT,CV_8UC3);
    cam_camera.set(CV_CAP_PROP_FRAME_HEIGHT,600);
    cam_camera.set(CV_CAP_PROP_FRAME_WIDTH,800);
}
