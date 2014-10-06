
#include "FramePreparer.hpp"
#include "BallDetector.hpp"
#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <highgui.h>
#include <cvblob.h>
#include <opencv2/opencv.hpp>

using namespace std;

int readVideo() {
	unique_ptr<FramePreparer> framePreparer(new FramePreparer);
	unique_ptr<BallDetector> ballDetector(new BallDetector);

	unique_ptr<cv::VideoCapture, cvCaptureDeleter> capture;
	capture = unique_ptr<cv::VideoCapture, cvCaptureDeleter>(new cv::VideoCapture("data/video/video.mov"));

	unique_ptr<cv::Mat, cvMatDeleter> sourceImage = unique_ptr<cv::Mat, cvMatDeleter>(new cv::Mat());
	shared_ptr<cvb::CvBlob> ballBlob;

	bool opened = capture->isOpened();

	while (capture->read(*sourceImage.get())) {
		IplImage sourceImageIpl = IplImage(*sourceImage.get());
		unique_ptr<IplImage, cvImageDeleter> preparedImage;

		preparedImage = framePreparer->prepare(sourceImageIpl);
		ballBlob = ballDetector->detect(move(preparedImage));

		if (ballBlob.get() != nullptr) {
			cout << ballBlob->centroid.x << ", " << ballBlob->centroid.y << endl;
		} else {
			cout << "I got nothing for " << capture->get(CV_CAP_PROP_POS_FRAMES - 1) << endl;
		}
	}

	cout << "Done." << endl;

	return 0;
}

//int readFrames() {
//	unique_ptr<FramePreparer> framePreparer(new FramePreparer);
//	unique_ptr<BallDetector> ballDetector(new BallDetector);
//
//	int startIndex = 1;
//	int endIndex = 217;
//
//	unique_ptr<IplImage, cvImageDeleter> sourceImage;
//	unique_ptr<IplImage, cvImageDeleter> preparedImage;
//	shared_ptr<cvb::CvBlob> ballBlob;
//
//	for (int i = startIndex; i <= endIndex; i++) {
//		stringstream ss;
//		ss << "data/frames/image-" << std::setw(3) << std::setfill('0') << i << ".png";
//		sourceImage = unique_ptr<IplImage, cvImageDeleter>(cvLoadImage(ss.str().c_str()));
//		// cout << ss.str() << endl;
//
//		if (sourceImage == NULL) {
//			cout << endl << "No image found?";
//			return -1;
//		}
//
//		preparedImage = framePreparer->prepare(move(sourceImage));
//		ballBlob = ballDetector->detect(move(preparedImage));
//
//		if (ballBlob.get() != nullptr) {
//			cout << ballBlob->centroid.x << ", " << ballBlob->centroid.y << endl;
//		} else {
//			cout << "I got nothing for " << ss.str() << endl;
//		}
//	}
//
//    return 0;
//}

int main(int argc, char* argv[]) {
//	return readFrames();
	return readVideo();
}
