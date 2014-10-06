
#include "FramePreparer.hpp"
#include "BallDetector.hpp"
#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <highgui.h>
#include <cvblob.h>

using namespace std;

int main(int argc, char* argv[]) {
    unique_ptr<FramePreparer> framePreparer(new FramePreparer);
    unique_ptr<BallDetector> ballDetector(new BallDetector);

    int startIndex = 1;
    int endIndex = 217;

    for (int i = startIndex; i <= endIndex; i++) {
        unique_ptr<IplImage, cvImageDeleter> sourceImage;
        unique_ptr<IplImage, cvImageDeleter> preparedImage;
        shared_ptr<cvb::CvBlob> ballBlob;

		stringstream ss;
		ss << "frames/image-" << std::setw(3) << std::setfill('0') << i << ".png";
		sourceImage = unique_ptr<IplImage, cvImageDeleter>(cvLoadImage(ss.str().c_str()));
		// cout << ss.str() << endl;

		if (sourceImage == NULL) {
			cout << endl << "No image found?";
			return -1;
		}

		preparedImage = framePreparer->prepare(move(sourceImage));

		ballBlob = ballDetector->detect(move(preparedImage));

		if (ballBlob.get() != nullptr) {
			cout << ballBlob->centroid.x << ", " << ballBlob->centroid.y << endl;
		}
    }

    return 0;
}
