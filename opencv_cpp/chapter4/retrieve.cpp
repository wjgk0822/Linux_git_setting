
#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "imageComparator.h"

int main()
{
	// Read reference image
	cv::Mat image = cv::imread("waves.jpg");
	if (!image.data)
		return 0;

	// Display image
	cv::namedWindow("Query Image");
	cv::imshow("Query Image", image);

	ImageComparator c;
	c.setReferenceImage(image);

	// Read an image and compare it with reference
	cv::Mat input = cv::imread("dog.jpg");
	cout << "waves vs dog: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("marais.jpg");
	cout << "waves vs marais: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("bear.jpg");
	cout << "waves vs bear: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("beach.jpg");
	cout << "waves vs beach: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("polar.jpg");
	cout << "waves vs polar: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("moose.jpg");
	cout << "waves vs moose: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("lake.jpg");
	cout << "waves vs lake: " << c.compare(input) << endl;

	// Read an image and compare it with reference
	input = cv::imread("fundy.jpg");
	cout << "waves vs fundy: " << c.compare(input) << endl;

	cv::waitKey();
	return 0;
}