
#include "BallDetectionTest.hpp"
#include "FramePreparer.hpp"
#include "BallDetector.hpp"

#include <memory>
#include <cv.h>
#include <cvblob.h>

using namespace std;

int main(int argc, char* argv[]) {
    BallDetectionTest();

    unique_ptr<FramePreparer> framePreparer(new FramePreparer);
    unique_ptr<BallDetector> ballDetector(new BallDetector);

    unique_ptr<IplImage> sourceImage;

    sourceImage = framePreparer->prepare(move(sourceImage));
    unique_ptr<cvb::CvBlob> ballBlob = ballDetector->detect(move(sourceImage));

    return 0;
}
