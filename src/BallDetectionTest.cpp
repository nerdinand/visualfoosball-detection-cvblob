
#include <cv.h>
#include <highgui.h>
#include <cvblob.h>

#include "BallDetectionTest.hpp"
#include "Util.hpp"

using namespace cvb;
using namespace std;

int BallDetectionTest() {
    /// Variables /////////////////////////////////////////////////////////
    CvSize imgSize;
    IplImage *image, *cvtColorImage, *frame, *segmentated, *labelImg;
    CvBlobs blobs;

    unsigned int result = 0;
    bool quit = false;
    ///////////////////////////////////////////////////////////////////////

    CvScalar minBallHSV = cvScalar(10, 172, 140);
    CvScalar maxBallHSV = cvScalar(15, 215, 232);

    CvScalar minBlueHSV = cvScalar(109.0, 203.0, 0.0);
    CvScalar maxBlueHSV = cvScalar(179.0, 255.0, 255.0);

    CvScalar minRedHSV = cvScalar(0.0, 203.0, 0.0);
    CvScalar maxRedHSV = cvScalar(9.0, 255.0, 255.0);

    // cvNamedWindow("Processed Image", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Processed Image", 750, 100);
    // cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Original Image", 100, 100);
    // cvNamedWindow("Color Range", CV_WINDOW_AUTOSIZE);
    // cvMoveWindow("Color Range", 100, 600);

    int numSuccessful = 0;
    int startIndex = 1;
    int endIndex = 217;

    int showIndex = -1;

    double calcTime = 0;

    clock_t totalBegin = clock();

    CvBlob* lastBlob = NULL;

    int roiSize = 100;

    for (int i = startIndex; i <= endIndex; i++) {
        stringstream ss;
        ss << "frames/image-" << std::setw(3) << std::setfill('0') << i << ".png";
        image = cvLoadImage(ss.str().c_str());
        cout << ss.str() << endl;

        if (image == NULL) {
            cout << endl << "No image found?";
            return -1;
        }

        clock_t begin = clock();

        // cout << endl << "Width (pixels): " << image->width;
        // cout << endl << "Height (pixels): " << image->height;
        // cout << endl << "Channels: " << image->nChannels;
        // cout << endl << "Bit Depth: " << image->depth;
        // cout << endl << "Image Data Size (kB): "
        //         << image->imageSize / 1024 << endl << endl;

        imgSize = cvGetSize(image);

        cvResetImageROI(image);

        CvRect regionOfInterest;
        if (lastBlob != NULL) {
            long x = (long) (lastBlob->centroid.x - roiSize/2);
            long y = (long) (lastBlob->centroid.y - roiSize/2);

            x = clamp(x, 0, imgSize.width);
            y = clamp(y, 0, imgSize.height);

            regionOfInterest = cvRect(x, y, roiSize, roiSize);

            // cout << regionOfInterest.x << " " << regionOfInterest.y << " " << regionOfInterest.width << " " << regionOfInterest.height << endl;

            cvSetImageROI(image, regionOfInterest);
        }

        imgSize = cvGetSize(image);
        frame = cvCreateImage(imgSize, image->depth, image->nChannels);
        cvConvertScale(image, frame, 1, 0);

        cvtColorImage = cvCreateImage(imgSize, 8, 3);
        cvCvtColor(image, cvtColorImage, cv::COLOR_BGR2HSV);

        segmentated = cvCreateImage(imgSize, 8, 1);

        cvInRangeS(cvtColorImage, minBallHSV, maxBallHSV, segmentated);

        if (i == showIndex && showIndex != -1) {
            cvShowImage("In range", segmentated);
        }

        cvSmooth(segmentated, segmentated, CV_MEDIAN, 7, 7);

        if (i == showIndex && showIndex != -1) {
            cvShowImage("Smoothed", segmentated);
        }

        labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);

        result = cvLabel(segmentated, labelImg, blobs);
        cvFilterByArea(blobs, 200, 2000);

        if (i == showIndex && showIndex != -1) {
            cvRenderBlobs(labelImg, blobs, frame, frame, CV_BLOB_RENDER_BOUNDING_BOX | CV_BLOB_RENDER_TO_STD, 1.);
        }

        lastBlob = NULL;
        int count = 0;
        for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
        {
            lastBlob = it->second;

            regionOfInterest = cvGetImageROI(image);
            lastBlob->centroid.x += regionOfInterest.x;
            lastBlob->centroid.y += regionOfInterest.y;

            cout << "Blob #" << lastBlob->label << ": Area=" << lastBlob->area << ", Centroid=(" << lastBlob->centroid.x << ", " << lastBlob->centroid.y << ")" << endl;
            count++;
        }

        if (count == 1) {
            numSuccessful++;
        }

        if (i == showIndex && showIndex != -1) {
            cvShowImage("Original Image", frame);
            cvShowImage("Processed Image", segmentated);
        }

        cvReleaseImage(&labelImg);
        cvReleaseImage(&segmentated);
        cvReleaseImage(&cvtColorImage);
        cvReleaseImage(&frame);
        cvReleaseImage(&image);

        clock_t end = clock();
        calcTime += double(end - begin);
    }

    cvReleaseBlobs(blobs);


    clock_t totalEnd = clock();
    double totalTime = double(totalEnd - totalBegin) / CLOCKS_PER_SEC;

    cout << "Successful: " << numSuccessful <<  " of " << endIndex - startIndex + 1 << " frames" << endl;
    cout << "Calc time: " << calcTime / CLOCKS_PER_SEC << endl;
    cout << "Total time: " << totalTime << endl;

    cvDestroyAllWindows();

    return 0;
}
