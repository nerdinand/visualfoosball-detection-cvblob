
#include "FramePreparer.hpp"
#include "Config.hpp"
#include "CustomDeleters.hpp"

#include <cv.h>

using namespace std;

FramePreparer::FramePreparer() {
	// TODO Auto-generated constructor stub

}

unique_ptr<IplImage, cvImageDeleter> FramePreparer::prepare(unique_ptr<IplImage, cvImageDeleter> sourceImage) {
    CvSize imgSize = cvGetSize(sourceImage.get());

    unique_ptr<IplImage, cvImageDeleter> hsvImage;

    hsvImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, 8, 3));
    cvCvtColor(sourceImage.get(), hsvImage.get(), cv::COLOR_BGR2HSV);

    return hsvImage;
}

FramePreparer::~FramePreparer() {
	// TODO Auto-generated destructor stub
}

