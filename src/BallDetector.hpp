
#ifndef SRC_BALLDETECTOR_HPP_
#define SRC_BALLDETECTOR_HPP_

#include <memory>
#include <cv.h>
#include <cvblob.h>

class BallDetector {
public:
	BallDetector();

	std::unique_ptr<cvb::CvBlob> detect(std::unique_ptr<IplImage> sourceImage);

	virtual ~BallDetector();
};

#endif /* SRC_BALLDETECTOR_HPP_ */
