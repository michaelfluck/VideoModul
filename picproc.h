#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iomanip>
#include <ctime>

int procPictures();
cv::Mat turnPicture(cv::Mat srcPicture, double angle);
cv::Mat addText(cv::Mat srcPicture);
