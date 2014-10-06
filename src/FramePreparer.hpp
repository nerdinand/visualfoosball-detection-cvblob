
#ifndef SRC_FRAMEPREPARER_HPP_
#define SRC_FRAMEPREPARER_HPP_

#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <cvblob.h>

class FramePreparer {
public:
	FramePreparer();
	FramePreparer(bool showDebugWindows);

	std::unique_ptr<IplImage, cvImageDeleter> prepare(IplImage* sourceImage, const cvb::CvBlob* ballBlob);

	bool showDebugWindows() const {
		return _showDebugWindows;
	}

	void setShowDebugWindows(bool showDebugWindows) {
		_showDebugWindows = showDebugWindows;
	}

	virtual ~FramePreparer();

private:
	bool _showDebugWindows;

};

#endif /* SRC_FRAMEPREPARER_HPP_ */
