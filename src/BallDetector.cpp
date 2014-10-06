
#include "BallDetector.hpp"
#include "Config.hpp"
#include "CustomDeleters.hpp"
#include "Util.hpp"

#include <cv.h>
#include <highgui.h>
#include <cvblob.h>

using namespace std;


BallDetector::BallDetector(){
	_showDebugWindows = false;
}

BallDetector::BallDetector(bool showDebugWindows) {
	_showDebugWindows = showDebugWindows;
}

shared_ptr<cvb::CvBlob> BallDetector::detect(unique_ptr<IplImage, cvImageDeleter> hsvImage) {
    unique_ptr<IplImage, cvImageDeleter> colorInRangeImage;
    unique_ptr<IplImage, cvImageDeleter> smoothedImage;
    unique_ptr<IplImage, cvImageDeleter> labelImage;

    cvb::CvBlobs blobs;

    unsigned int result = 0;

    shared_ptr<cvb::CvBlob> lastBlob = _lastBlob;

    cvResetImageROI(hsvImage.get());

    CvSize imgSize = cvGetSize(hsvImage.get());

	CvRect regionOfInterest;
	if (lastBlob.get() != nullptr) {
		long x = (long) (lastBlob->centroid.x - Config::ballROISize/2);
		long y = (long) (lastBlob->centroid.y - Config::ballROISize/2);

		x = Util::clamp(x, 0, imgSize.width);
		y = Util::clamp(y, 0, imgSize.height);

		regionOfInterest = cvRect(x, y, Config::ballROISize, Config::ballROISize);

		// cout << regionOfInterest.x << " " << regionOfInterest.y << " " << regionOfInterest.width << " " << regionOfInterest.height << endl;

		cvSetImageROI(hsvImage.get(), regionOfInterest);
	}

    imgSize = cvGetSize(hsvImage.get());


    colorInRangeImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, 8, 1));
	cvInRangeS(hsvImage.get(), Config::minBallHSV, Config::maxBallHSV, colorInRangeImage.get());
	if (showDebugWindows()) {
		cvShowImage("In range", colorInRangeImage.get());
	}

	smoothedImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, 8, 1));
	cvSmooth(colorInRangeImage.get(), smoothedImage.get(), CV_MEDIAN, 7, 7);
	if (showDebugWindows()) {
		cvShowImage("Smoothed", smoothedImage.get());
	}

	labelImage = unique_ptr<IplImage, cvImageDeleter>(cvCreateImage(imgSize, IPL_DEPTH_LABEL, 1));
	result = cvLabel(smoothedImage.get(), labelImage.get(), blobs);
	cvFilterByArea(blobs, Config::minBallBlobSize, Config::maxBallBlobSize);

	if (showDebugWindows()) {
		cvRenderBlobs(labelImage.get(), blobs, hsvImage.get(), hsvImage.get(), CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_TO_STD, 1.);
	}

	_lastBlob = nullptr;

	int blobCount = 0;
	for (cvb::CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
	{
		lastBlob = unique_ptr<cvb::CvBlob, cvBlobDeleter>(it->second);

		cv::Rect regionOfInterest = cvGetImageROI(hsvImage.get());
		lastBlob->centroid.x += regionOfInterest.x;
		lastBlob->centroid.y += regionOfInterest.y;

		_lastBlob = lastBlob;
		// cout << "Blob #" << lastBlob->label << ": Area=" << lastBlob->area << ", Centroid=(" << lastBlob->centroid.x << ", " << lastBlob->centroid.y << ")" << endl;
		blobCount++;
	}

	if (blobCount == 1) {
		_successfulFramesCount++;
	}

	if (showDebugWindows()) {
		cvShowImage("Original Image", hsvImage.get());
		cvShowImage("Processed Image", colorInRangeImage.get());
	}

    return _lastBlob;
}

BallDetector::~BallDetector() {
	// TODO Auto-generated destructor stub
}
