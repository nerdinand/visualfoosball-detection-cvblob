
#include "FramePreparer.hpp"
#include "BallDetector.hpp"
#include "CustomDeleters.hpp"

#include <memory>
#include <cv.h>
#include <highgui.h>
#include <cvblob.h>
#include <opencv2/opencv.hpp>

using namespace std;

int readWebcam() {
	const char* cameraOutputWindow = "camera";

    CvCapture *camCapture;
    int ret = 0;

    if (!(camCapture = cvCaptureFromCAM(1))) {
        cout << "Failed to capture from camera" << endl;

        ret = 1;

        return -1;
    }

    cout << "Camera opened successfully" << endl;

    cvNamedWindow(cameraOutputWindow, CV_WINDOW_AUTOSIZE);

    IplImage *cameraFrame;
    int grabFrameRet;

    while (true) {
        if ((cameraFrame = cvQueryFrame(camCapture))) {
            cvShowImage(cameraOutputWindow, cameraFrame);
        }

        if (cvWaitKey(60) != -1) {
            cout << "Input" << endl;
            break;
        }
    }

    cout << "Done" << endl;

    cvReleaseCapture(&camCapture);
    cvDestroyWindow(cameraOutputWindow);
    return ret;
}

int readVideo() {
	bool showDebugWindows = false;

	unique_ptr<FramePreparer> framePreparer(new FramePreparer());
	unique_ptr<BallDetector> ballDetector(new BallDetector());

	unique_ptr<cv::VideoCapture, cvCaptureDeleter> capture;
	capture = unique_ptr<cv::VideoCapture, cvCaptureDeleter>(new cv::VideoCapture("data/video/video.mov"));

	unique_ptr<cv::Mat, cvMatDeleter> sourceImage = unique_ptr<cv::Mat, cvMatDeleter>(new cv::Mat());
	shared_ptr<cvb::CvBlob> ballBlob;

	bool opened = capture->isOpened();

	CvPoint2D64f lastCentroid;

	int successfulCount = 0;
	int unsuccessfulCount = 0;

	double totalTime;
	double prepareTime;
	double detectTime;

	clock_t totalBegin = clock();

	int frameIndex = 1;

	while (capture->read(*sourceImage.get())) {
		IplImage sourceImageIpl = IplImage(*sourceImage.get());
		unique_ptr<IplImage, cvImageDeleter> preparedImage;

		clock_t prepareBegin = clock();
		preparedImage = framePreparer->prepare(&sourceImageIpl, ballBlob.get());
		clock_t prepareEnd = clock();
		prepareTime += double(prepareEnd - prepareBegin);

		clock_t detectBegin = clock();
		ballBlob = ballDetector->detect(move(preparedImage));
		clock_t detectEnd = clock();
		detectTime += double(detectEnd - detectBegin);

		if (ballBlob.get() != nullptr) {
			successfulCount++;

			cv::Rect regionOfInterest = cvGetImageROI(&sourceImageIpl);
			ballBlob->centroid.x += regionOfInterest.x;
			ballBlob->centroid.y += regionOfInterest.y;

			cout << ballBlob->centroid.x << ", " << ballBlob->centroid.y << endl;
			lastCentroid = ballBlob->centroid;

		} else {
			// cout << lastCentroid.x << ", " << lastCentroid.y << endl;
			cout << "I got nothing for frame " << frameIndex << "." << endl;
			unsuccessfulCount++;
		}

		frameIndex++;

//		break;
	}

	clock_t totalEnd = clock();

	cout << "Done." << endl;

	int totalCount = successfulCount + unsuccessfulCount;

	cout << successfulCount << " successful frames." << endl;
	cout << unsuccessfulCount << " unsuccessful frames." << endl;
	cout << totalCount << " total frames." << endl;

	cout << (totalEnd - totalBegin) / CLOCKS_PER_SEC << "s total processing time." << endl;
	cout << prepareTime / CLOCKS_PER_SEC << "s prepare time." << endl;
	cout << detectTime / CLOCKS_PER_SEC << "s detect time." << endl;
	cout << (prepareTime + detectTime) / CLOCKS_PER_SEC / totalCount << "s average processing per frame." << endl;

	if (showDebugWindows) {
		cout <<  "Waiting for a key press so you can look at the windows..." << endl;
		cv::waitKey();
	}

	cout << "Quit." << endl;

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
//	return readWebcam();
}
