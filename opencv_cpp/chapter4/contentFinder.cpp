#include <iostream>

using namespace std; 

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "histogram.h"
#include "contentFinder.h"
#include "colorhistogram.h"

int main()
{

	cv::Mat image = cv::imread("waves.jpg", 0);
	if (!image.data)
		return 0;

	cv::Mat imageROI;
	imageROI = image(cv::Rect(216, 33, 24, 30));

	cv::namedWindow("Reference");
	cv::imshow("Reference", imageROI);

	Histogram1D h;
	cv::Mat hist = h.getHistogram(imageROI);
	cv::namedWindow("Reference Hist");
	cv::imshow("Reference Hist", h.getHistogramImage(imageROI));

	ContentFinder finder;

	finder.setHistogram(hist);
	finder.setThreshold(-1.0f);

	cv::Mat result1;
	result1 = finder.find(image);


	cv::Mat tmp;
	result1.convertTo(tmp, CV_8U, -1.0, 255.0);
	cv::namedWindow("Backprojection result");
	cv::imshow("Backprojection result", tmp);

	// Get binary back-projection
	finder.setThreshold(0.12f);
	result1 = finder.find(image);



	cv::rectangle(image, cv::Rect(216, 33, 24, 30), cv::Scalar(0, 0, 0));

	cv::namedWindow("Image");

	cv::imshow("Image", image);

	cv::namedWindow("Detection Result");
	cv::imshow("Detection Result", result1);

	ColorHistogram hc;

	cv::Mat color = cv::imread("waves.jpg");

	imageROI = color(cv::Rect(0, 0, 100, 45));

	hc.setSize(8);
	cv::Mat shist = hc.getHistogram(imageROI);

	finder.setHistogram(shist);
	finder.setThreshold(0.05f);


	result1 = finder.find(color);

	cv::namedWindow("Color Detection Result");
	cv::imshow("Color Detection Result", result1);

	cv::Mat color2 = cv::imread("dog.jpg");

	cv::namedWindow("Second Image");
	cv::imshow("Second Image", color2);

	cv::Mat result2 = finder.find(color2);

	cv::namedWindow("Result color (2)");
	cv::imshow("Result color (2)", result2);

	hc.setSize(256);
	cv::Mat colorhist = hc.getabHistogram(imageROI);

	colorhist.convertTo(tmp, CV_8U, -1.0, 255.0);
	cv::namedWindow("ab histogram");
	cv::imshow("ab histogram", tmp);

	finder.setHistogram(colorhist);
	finder.setThreshold(0.05f);

	cv::Mat lab;
	cv::cvtColor(color, lab, cv::COLOR_BGR2Lab);

	int ch[2] = { 1,2 };
	result1 = finder.find(lab, 0, 256.0f, ch);

	cv::namedWindow("Result ab (1)");
	cv::imshow("Result ab (1)", result1);

	cv::cvtColor(color2, lab, cv::COLOR_BGR2Lab);

	result2 = finder.find(lab, 0, 256.0, ch);


	cv::namedWindow("Result ab (2)");
	cv::imshow("Result ab (2)", result2);

	cv::rectangle(color, cv::Rect(0, 0, 100, 45), cv::Scalar(0, 0, 0));

	cv::namedWindow("Color Image");
	cv::imshow("Color Image", color);


	hc.setSize(180);
	colorhist = hc.getHueHistogram(imageROI);

	finder.setHistogram(colorhist);

	cv::Mat hsv; 
	cv::cvtColor(color, hsv, cv::COLOR_BGR2HSV);

	ch[0] = 0;

	result1 = finder.find(hsv, 0.0f, 180.0f, ch);

	cv::namedWindow("Result Hue (1)");
	cv::imshow("Result Hue (1)", result1);

	color2 = cv::imread("dog.jpg");

	cv::cvtColor(color2, hsv, cv::COLOR_BGR2HSV);

	result2 = finder.find(hsv, 0.0f, 180.0f, ch);

	cv::namedWindow("Result Hue (2)");
	cv::imshow("Result Hue (2)", result2);

	cv::waitKey();

	return 0;





}