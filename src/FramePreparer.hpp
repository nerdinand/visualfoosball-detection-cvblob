
#ifndef SRC_FRAMEPREPARER_HPP_
#define SRC_FRAMEPREPARER_HPP_

#include <memory>
#include <cv.h>

class FramePreparer {
public:
	FramePreparer();

	std::unique_ptr<IplImage> prepare(std::unique_ptr<IplImage> sourceImage);

	virtual ~FramePreparer();
};

#endif /* SRC_FRAMEPREPARER_HPP_ */
