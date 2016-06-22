#ifndef CAMERA_H
#define CAMERA_H


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <raspicam/raspicam_cv.h>

#include "const_global.h"

class Camera
{
public:
    Camera();
    ~Camera();
    void getPicture();
    void initCam();
    bool getStatus();

private:
    raspicam::RaspiCam_Cv       cam_camera;
    cv::Mat                     cam_picture;
    int                         cam_pictureNr;

};

#endif // CAMERA_H
