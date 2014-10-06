
#include "FramePreparer.hpp"
#include "Config.hpp"

#include <cv.h>

using namespace std;

FramePreparer::FramePreparer() {
	// TODO Auto-generated constructor stub

}

shared_ptr<IplImage> FramePreparer::prepare(unique_ptr<IplImage> sourceImage) {
    CvSize imgSize = cvGetSize(sourceImage.get());

    shared_ptr<IplImage> hsvImage;

    hsvImage = shared_ptr<IplImage>(cvCreateImage(imgSize, 8, 3));
    cvCvtColor(sourceImage.get(), hsvImage.get(), cv::COLOR_BGR2HSV);

    return hsvImage;
}

FramePreparer::~FramePreparer() {
	// TODO Auto-generated destructor stub
}

