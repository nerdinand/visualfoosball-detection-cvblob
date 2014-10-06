
#include "FramePreparer.hpp"
#include "Config.hpp"
#include "CustomDeleters.hpp"

#include <cv.h>

using namespace std;

FramePreparer::FramePreparer(){
	_showDebugWindows = false;
}

FramePreparer::FramePreparer(bool showDebugWindows) {
	_showDebugWindows = showDebugWindows;
}

unique_ptr<IplImage, cvImageDeleter> FramePreparer::prepare(const IplImage& sourceImage) {
    CvSize imgSize = cvGetSize(&sourceImage);

	if (showDebugWindows()) {
		cvShowImage("Source", &sourceImage);
	}

    unique_ptr<IplImage, cvImageDeleter> hsvImage;

    hsvImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, 8, 3));
    cvCvtColor(&sourceImage, hsvImage.get(), cv::COLOR_BGR2HSV);

    return move(hsvImage);
}

FramePreparer::~FramePreparer() {
	// TODO Auto-generated destructor stub
}

