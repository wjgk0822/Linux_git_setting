#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "watershedSegmentation.h"

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("group.jpg");
	if (!image.data)
		return 0;


	namedWindow("Original Image");
	imshow("Original Image", image);

	Mat binary;
	binary = imread("binary.bmp", 0);

	namedWindow("Binary Image");
	imshow("Binary Image", binary);

	Mat fg;
	erode(binary, fg, Mat(), Point(-1, -1), 4);

	namedWindow("Foreground Image");
	imshow("Foreground Image", fg);

	Mat bg;
	dilate(binary, bg, Mat(), Point(-1, -1), 4);
	threshold(bg, bg, 1, 128, THRESH_BINARY_INV);

	namedWindow("Background Image");
	imshow("Background Image", bg);

	Mat markers(binary.size(), CV_8U, Scalar(0));
	markers = fg + bg;
	namedWindow("Markers");
	imshow("Markers", markers);


	WatershedSegmenter segmenter;

	segmenter.setMarkers(markers);

	segmenter.process(image);

	namedWindow("Segmentation");
	imshow("Segmentation", segmenter.getSegmentation());

	namedWindow("Watersheds");
	imshow("Watersheds", segmenter.getWatersheds());

	image = imread("tower.jpg");

	Mat imageMask(image.size(), CV_8U, Scalar(0));
	rectangle(imageMask, Point(image.cols / 2 - 10, image.rows / 2 - 10),
		Point(image.cols / 2 + 10, image.rows / 2 + 10), Scalar(1),10);

	segmenter.setMarkers(imageMask);
	segmenter.process(image);

	rectangle(image, Point(5, 5), Point(image.cols - 5, image.rows - 5), Scalar(255, 255, 255), 3);
	rectangle(image, cv::Point(image.cols / 2 - 10, image.rows / 2 - 10),
		cv::Point(image.cols / 2 + 10, image.rows / 2 + 10), cv::Scalar(1, 1, 1), 10);

	namedWindow("Watershed");
	imshow("Watershed", segmenter.getWatersheds());

	waitKey();

	return 0;

}