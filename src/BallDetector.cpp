
#include "BallDetector.hpp"

#include "Config.hpp"
#include <cv.h>
#include <cvblob.h>

using namespace std;


BallDetector::BallDetector() {
	// TODO Auto-generated constructor stub

}

unique_ptr<cvb::CvBlob> BallDetector::detect(unique_ptr<IplImage> hsvImage) {
    unique_ptr<cvb::CvBlob> cvBlob(new cvb::CvBlob());

    unique_ptr<IplImage> colorInRangeImage;
    unique_ptr<IplImage> smoothedImage;
    unique_ptr<IplImage> labelImage;

    cvb::CvBlobs blobs;

    unsigned int result = 0;

    CvSize imgSize = cvGetSize(hsvImage.get());

    unique_ptr<cvb::CvBlob> lastBlob(nullptr);

    colorInRangeImage = unique_ptr<IplImage>(cvCreateImage(imgSize, 8, 1));
	cvInRangeS(hsvImage.get(), Config::minBallHSV, Config::maxBallHSV, colorInRangeImage.get());
//	if (i == showIndex && showIndex != -1) {
//		cvShowImage("In range", colorInRangeImage);
//	}

	smoothedImage = unique_ptr<IplImage>(cvCreateImage(imgSize, 8, 1));
	cvSmooth(colorInRangeImage.get(), smoothedImage.get(), CV_MEDIAN, 7, 7);
//	if (i == showIndex && showIndex != -1) {
//		cvShowImage("Smoothed", smoothedImage);
//	}

	labelImage = unique_ptr<IplImage>(cvCreateImage(imgSize, IPL_DEPTH_LABEL, 1));
	result = cvLabel(smoothedImage.get(), labelImage.get(), blobs);
	cvFilterByArea(blobs, Config::minBallBlobSize, Config::maxBallBlobSize);

//	if (i == showIndex && showIndex != -1) {
//		cvRenderBlobs(labelImage, blobs, sourceImage, sourceImage, CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_TO_STD, 1.);
//	}

	lastBlob = NULL;
	int blobCount = 0;
	for (cvb::CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
	{
		lastBlob = unique_ptr<cvb::CvBlob>(it->second);

		cv::Rect regionOfInterest = cvGetImageROI(hsvImage.get());
		lastBlob->centroid.x += regionOfInterest.x;
		lastBlob->centroid.y += regionOfInterest.y;

		cout << "Blob #" << lastBlob->label << ": Area=" << lastBlob->area << ", Centroid=(" << lastBlob->centroid.x << ", " << lastBlob->centroid.y << ")" << endl;
		blobCount++;
	}

	if (blobCount == 1) {
		_successfulFramesCount++;
	}

//	if (i == showIndex && showIndex != -1) {
//		cvShowImage("Original Image", sourceImage);
//		cvShowImage("Processed Image", colorInRangeImage);
//	}

    return move(lastBlob);
}

BallDetector::~BallDetector() {
	// TODO Auto-generated destructor stub
}
