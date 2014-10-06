
#ifndef SRC_BALLDETECTOR_HPP_
#define SRC_BALLDETECTOR_HPP_

#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <cvblob.h>

class BallDetector {
public:
	BallDetector();

	std::shared_ptr<cvb::CvBlob> detect(std::unique_ptr<IplImage, cvImageDeleter> hsvImage);

	virtual ~BallDetector();

private:
	int _successfulFramesCount = 0;
	std::shared_ptr<cvb::CvBlob> _lastBlob;
};

#endif /* SRC_BALLDETECTOR_HPP_ */
