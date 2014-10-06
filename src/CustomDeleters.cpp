
#include "CustomDeleters.hpp"

void cvImageDeleter::operator() (IplImage* image){
	cvReleaseImage(&image);
}

void cvBlobDeleter::operator() (cvb::CvBlob* blob) {
	cvReleaseBlob(blob);
}

void cvCaptureDeleter::operator() (cv::VideoCapture* videoCapture) {
	videoCapture->release();
}

void cvMatDeleter::operator() (cv::Mat* mat) {
	mat->release();
}
