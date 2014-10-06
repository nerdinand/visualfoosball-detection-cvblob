
#ifndef SRC_CONFIG_HPP_
#define SRC_CONFIG_HPP_

#include <cv.h>

class Config {

public:
	static const CvScalar minBallHSV;
	static const CvScalar maxBallHSV;

	static const CvScalar minBlueHSV;
	static const CvScalar maxBlueHSV;

	static const CvScalar minRedHSV;
	static const CvScalar maxRedHSV;

	static const int ballROISize;

	static const unsigned int minBallBlobSize;
	static const unsigned int maxBallBlobSize;

	static const unsigned int blurSize;
};

#endif /* SRC_CONFIG_HPP_ */

