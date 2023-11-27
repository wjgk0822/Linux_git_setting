#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram.h"

int main()
{
	cv::Mat image = cv::imread("group.jpg",0);
	if (!image.data)
		return 0;

	cv::imwrite("groupBW.jpg", image);

	cv::namedWindow("Image");
	cv::imshow("Image", image);

	Histogram1D h;

	cv::Mat histo = h.getHistogram(image);

	for (int i = 0; i < 256; i++)
		cout << "Value " << i << " = " << histo.at<float>(i) << endl;


	cv::namedWindow("Histogram");
	cv::imshow("Histogram", h.getHistogram(image));

	cv::Mat hi = h.getHistogramImage(image);
	cv::line(hi, cv::Point(70, 0), cv::Point(70, 255), cv::Scalar(128));
	cv::namedWindow("Histogram with threshold value");
	cv::imshow("Histogram with threshold value", hi);

	cv::Mat thresholded;
	cv::threshold(image, thresholded,
		70,
		255,
		cv::THRESH_BINARY);


	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image", thresholded);
	thresholded = 255 - thresholded;
	cv::imwrite("binary.bmp", thresholded);

	cv::Mat eq = h.equalize(image);

	cv::namedWindow("Equalized Image");
	cv::imshow("Equalized Image", eq);

	cv::namedWindow("Equalized H");
	cv::imshow("Equalized H", h.getHistogramImage(eq));

	cv::Mat str = h.stretch(image, 0.01f);

	cv::namedWindow("Stretched Image");
	cv::imshow("Stretched Image", str);

	cv::namedWindow("Stretched H");
	cv::imshow("Stretched H", h.getHistogramImage(str));

	cv::Mat lut(1, 256, CV_8U);


	for (int i = 0; i < 256; i++) {
		lut.at<uchar>(i) = 255 - i;
	}

	cv::namedWindow("Negative image");
	cv::imshow("Negative image", h.applyLookUp(image, lut));

	cv::waitKey();

	return 0;

}