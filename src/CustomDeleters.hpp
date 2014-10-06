/*
 * CustomDeleters.hpp
 *
 *  Created on: 06.10.2014
 *      Author: ferdi
 */

#ifndef SRC_CUSTOMDELETERS_HPP_
#define SRC_CUSTOMDELETERS_HPP_

#include <cv.h>
#include <cvblob.h>

struct cvImageDeleter{
    void operator() (IplImage* image);
};

struct cvBlobDeleter{
    void operator() (cvb::CvBlob* blob);
};

#endif /* SRC_CUSTOMDELETERS_HPP_ */
