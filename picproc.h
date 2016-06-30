#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QDir>
#include <QDateTime>

#include "xmlreader.h"
#include "const_global.h"

int procPictures(int pictureNr);
void readTextToAdd();
cv::Mat turnPicture(cv::Mat srcPicture, double angle);
cv::Mat addText(cv::Mat srcPicture);
