
#include "CustomDeleters.hpp"

void cvImageDeleter::operator() (IplImage* image){
	cvReleaseImage(&image);
}

void cvBlobDeleter::operator() (cvb::CvBlob* blob) {
	cvReleaseBlob(blob);
}
