
#ifndef SRC_FRAMEPREPARER_HPP_
#define SRC_FRAMEPREPARER_HPP_

#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>

class FramePreparer {
public:
	FramePreparer();

	std::unique_ptr<IplImage, cvImageDeleter> prepare(std::unique_ptr<IplImage, cvImageDeleter> sourceImage);

	virtual ~FramePreparer();

};

#endif /* SRC_FRAMEPREPARER_HPP_ */
