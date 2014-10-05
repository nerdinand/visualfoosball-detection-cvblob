
#include "BallDetectionTest.hpp"
#include "FramePreparer.hpp"

#include <memory>
#include <cv.h>

using namespace std;

int main(int argc, char* argv[]) {
    BallDetectionTest();

    unique_ptr<FramePreparer> framePreparer(new FramePreparer);
    unique_ptr<IplImage> sourceImage;
    sourceImage = framePreparer->prepare(move(sourceImage));

    return 0;
}
