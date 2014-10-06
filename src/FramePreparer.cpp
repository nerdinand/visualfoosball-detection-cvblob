
#include "FramePreparer.hpp"
#include "Config.hpp"
#include "CustomDeleters.hpp"
#include "Util.hpp"

#include <cv.h>
#include <cvblob.h>

using namespace std;

FramePreparer::FramePreparer(){
	_showDebugWindows = false;
}

FramePreparer::FramePreparer(bool showDebugWindows) {
	_showDebugWindows = showDebugWindows;
}

unique_ptr<IplImage, cvImageDeleter> FramePreparer::prepare(IplImage* sourceImage, const cvb::CvBlob* ballBlob) {
    CvSize imgSize = cvGetSize(sourceImage);

    cvResetImageROI(sourceImage);

    CvRect regionOfInterest;
	if (ballBlob != nullptr) {
		long x = (long) (ballBlob->centroid.x - Config::ballROISize/2);
		long y = (long) (ballBlob->centroid.y - Config::ballROISize/2);

		x = Util::clamp(x, 0, imgSize.width);
		y = Util::clamp(y, 0, imgSize.height);

		regionOfInterest = cvRect(x, y, Config::ballROISize, Config::ballROISize);

		// cout << "ROI: " << regionOfInterest.x << " " << regionOfInterest.y << " " << regionOfInterest.width << " " << regionOfInterest.height << endl;

		cvSetImageROI(sourceImage, regionOfInterest);
	}

    imgSize = cvGetSize(sourceImage);

	if (showDebugWindows()) {
		cvShowImage("Source", sourceImage);
	}

    unique_ptr<IplImage, cvImageDeleter> hsvImage;

    hsvImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, 8, 3));
    cvCvtColor(sourceImage, hsvImage.get(), cv::COLOR_BGR2HSV);

    return move(hsvImage);
}

FramePreparer::~FramePreparer() {
	// TODO Auto-generated destructor stub
}

