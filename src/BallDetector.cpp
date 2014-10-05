
#include "BallDetector.hpp"

BallDetector::BallDetector() {
	// TODO Auto-generated constructor stub

}

std::unique_ptr<cvb::CvBlob> BallDetector::detect(std::unique_ptr<IplImage> sourceImage) {
    std::unique_ptr<cvb::CvBlob> cvBlob(new cvb::CvBlob());

    return cvBlob;
}

BallDetector::~BallDetector() {
	// TODO Auto-generated destructor stub
}
