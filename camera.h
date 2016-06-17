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

private:
    raspicam::RaspiCam_Cv       cam_camera;
    bool                        cam_enable;
    cv::Mat                     cam_picture;
    int                         cam_pictureNr;

};

#endif // CAMERA_H
