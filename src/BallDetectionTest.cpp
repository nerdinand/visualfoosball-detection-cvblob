
#include <cv.h>
#include <highgui.h>
#include <cvblob.h>

#include "BallDetectionTest.hpp"

#include "Config.hpp"
#include "Util.hpp"

using namespace cvb;
using namespace std;

int BallDetectionTest() {
    CvSize imgSize;
    IplImage *sourceImage, *hsvImage, *colorInRangeImage, *smoothedImage, *labelImg;
    CvBlobs blobs;

    unsigned int result = 0;

    int successfulFramesCount = 0;
    int startIndex = 1;
    int endIndex = 217;

    int showIndex = -1;

    double calcTime = 0;

    clock_t totalTimeBegin = clock();

    CvBlob* lastBlob = NULL;

    // cvNamedWindow("Processed Image", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Processed Image", 750, 100);
    // cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Original Image", 100, 100);
    // cvNamedWindow("Color Range", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Color Range", 100, 600);

    for (int i = startIndex; i <= endIndex; i++) {
        stringstream ss;
        ss << "frames/image-" << std::setw(3) << std::setfill('0') << i << ".png";
        sourceImage = cvLoadImage(ss.str().c_str());
        cout << ss.str() << endl;

        if (sourceImage == NULL) {
            cout << endl << "No image found?";
            return -1;
        }

        clock_t imageCalculationBegin = clock();

        // cout << endl << "Width (pixels): " << image->width;
        // cout << endl << "Height (pixels): " << image->height;
        // cout << endl << "Channels: " << image->nChannels;
        // cout << endl << "Bit Depth: " << image->depth;
        // cout << endl << "Image Data Size (kB): "
        //         << image->imageSize / 1024 << endl << endl;

        imgSize = cvGetSize(sourceImage);

        cvResetImageROI(sourceImage);

        CvRect regionOfInterest;
        if (lastBlob != NULL) {
            long x = (long) (lastBlob->centroid.x - Config::ballROISize/2);
            long y = (long) (lastBlob->centroid.y - Config::ballROISize/2);

            x = clamp(x, 0, imgSize.width);
            y = clamp(y, 0, imgSize.height);

            regionOfInterest = cvRect(x, y, Config::ballROISize, Config::ballROISize);

            // cout << regionOfInterest.x << " " << regionOfInterest.y << " " << regionOfInterest.width << " " << regionOfInterest.height << endl;

            cvSetImageROI(sourceImage, regionOfInterest);
        }

        imgSize = cvGetSize(sourceImage);

        hsvImage = cvCreateImage(imgSize, 8, 3);
        cvCvtColor(sourceImage, hsvImage, cv::COLOR_BGR2HSV);

        colorInRangeImage = cvCreateImage(imgSize, 8, 1);
        cvInRangeS(hsvImage, Config::minBallHSV, Config::maxBallHSV, colorInRangeImage);
        if (i == showIndex && showIndex != -1) {
            cvShowImage("In range", colorInRangeImage);
        }

        smoothedImage = cvCreateImage(imgSize, 8, 1);
        cvSmooth(colorInRangeImage, smoothedImage, CV_MEDIAN, 7, 7);
        if (i == showIndex && showIndex != -1) {
            cvShowImage("Smoothed", smoothedImage);
        }

        labelImg = cvCreateImage(cvGetSize(sourceImage), IPL_DEPTH_LABEL, 1);
        result = cvLabel(smoothedImage, labelImg, blobs);
        cvFilterByArea(blobs, Config::minBallBlobSize, Config::maxBallBlobSize);

        if (i == showIndex && showIndex != -1) {
            cvRenderBlobs(labelImg, blobs, sourceImage, sourceImage, CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_TO_STD, 1.);
        }

        lastBlob = NULL;
        int blobCount = 0;
        for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
        {
            lastBlob = it->second;

            regionOfInterest = cvGetImageROI(sourceImage);
            lastBlob->centroid.x += regionOfInterest.x;
            lastBlob->centroid.y += regionOfInterest.y;

            cout << "Blob #" << lastBlob->label << ": Area=" << lastBlob->area << ", Centroid=(" << lastBlob->centroid.x << ", " << lastBlob->centroid.y << ")" << endl;
            blobCount++;
        }

        if (blobCount == 1) {
            successfulFramesCount++;
        }

        if (i == showIndex && showIndex != -1) {
            cvShowImage("Original Image", sourceImage);
            cvShowImage("Processed Image", colorInRangeImage);
        }

        cvReleaseImage(&labelImg);
        cvReleaseImage(&smoothedImage);
        cvReleaseImage(&colorInRangeImage);
        cvReleaseImage(&hsvImage);
        cvReleaseImage(&sourceImage);

        clock_t imageCalculationEnd = clock();
        calcTime += double(imageCalculationEnd - imageCalculationBegin);
    }

    cvReleaseBlobs(blobs);


    clock_t totalTimeEnd = clock();
    double totalTime = double(totalTimeEnd - totalTimeBegin) / CLOCKS_PER_SEC;

    cout << "Successful: " << successfulFramesCount <<  " of " << endIndex - startIndex + 1 << " frames" << endl;
    cout << "Calc time: " << calcTime / CLOCKS_PER_SEC << endl;
    cout << "Total time: " << totalTime << endl;

    cvDestroyAllWindows();

    return 0;
}
