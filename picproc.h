#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QDir>
#include <QDateTime>

#include "xmlreader.h"
#include "const_global.h"
#include "gpio.h"
#include "dataaquisition.h"

void procPictures(int aArray[]);
void readTextToAdd();
void releaseVideo();
cv::Mat turnPicture(cv::Mat srcPicture, double angle);
cv::Mat addText(cv::Mat frame);
