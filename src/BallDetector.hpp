
#ifndef SRC_BALLDETECTOR_HPP_
#define SRC_BALLDETECTOR_HPP_

#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <cvblob.h>

class BallDetector {
public:
	BallDetector();
	BallDetector(bool showDebugWindows);

	std::shared_ptr<cvb::CvBlob> detect(std::unique_ptr<IplImage, cvImageDeleter> hsvImage);

	virtual ~BallDetector();

	bool showDebugWindows() const {
		return _showDebugWindows;
	}

	void setShowDebugWindows(bool showDebugWindows) {
		_showDebugWindows = showDebugWindows;
	}

private:
	int _successfulFramesCount = 0;
	std::shared_ptr<cvb::CvBlob> _lastBlob;
	bool _showDebugWindows;
};

#endif /* SRC_BALLDETECTOR_HPP_ */
