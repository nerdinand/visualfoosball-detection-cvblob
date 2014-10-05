
#include "FramePreparer.hpp"
#include "Config.hpp"

#include <cv.h>

using namespace std;

FramePreparer::FramePreparer() {
	// TODO Auto-generated constructor stub

}

unique_ptr<IplImage> FramePreparer::prepare(unique_ptr<IplImage> sourceImage) {
    CvSize imgSize = cvGetSize(sourceImage.get());

    unique_ptr<IplImage> hsvImage;

    hsvImage = unique_ptr<IplImage>(cvCreateImage(imgSize, 8, 3));
    cvCvtColor(sourceImage.get(), hsvImage.get(), cv::COLOR_BGR2HSV);

    return hsvImage;
}

FramePreparer::~FramePreparer() {
	// TODO Auto-generated destructor stub
}

