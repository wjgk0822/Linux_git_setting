#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("boldt.jpg", 0);
	if (!image.data)
		return 0;

	namedWindow("Original Image");
	imshow("Original Image", image);


	Mat result;
	blur(image, result, Size(5, 5));

	namedWindow("Mean filtered Image");
	imshow("Mean filtered Image", result);

	blur(image, result, Size(9, 9));

	namedWindow("Mean filtered Image (9x9)");
	imshow("Mean filtered Image (9x9)", result);


	GaussianBlur(image, result,
		Size(5, 5),
		1.5);


	namedWindow("Gaussian filtered Image");
	imshow("Gaussian filtered Image", result);

	GaussianBlur(image, result, Size(9, 9), 1.7);


	namedWindow("Gaussian filtered Image (9x9)");
	imshow("Gaussian filtered Image (9x9)", result);

	Mat gauss = getGaussianKernel(9, 1.5, CV_32F);

	Mat_<float>::const_iterator it = gauss.begin<float>();
	Mat_<float>::const_iterator itend = gauss.end<float>();

	cout << "1.5=[";
	for (; it != itend; ++it) {
		cout << *it << " ";
	}

	cout << "]" << endl;


	gauss = getGaussianKernel(9, 0.5, CV_32F);

	it = gauss.begin<float>();
	itend = gauss.end<float>();
	cout << "0.5=[";
	for (; it != itend; ++it) {

		cout << *it << " ";
	}
	cout << "]" << endl;

	gauss = getGaussianKernel(9, 2.5, CV_32F);

	it = gauss.begin<float>();
	itend = gauss.end<float>();
	cout << "2.5 = [";
	for (; it != itend; ++it) {
		cout << *it << " ";
	}
	cout << "]" << std::endl;

	gauss = getGaussianKernel(9, -1, CV_32F);

	it = gauss.begin<float>();
	itend = gauss.end<float>();

	cout << "9=[";
	for (; it != itend; ++it) {

		cout << *it << " ";
	}
	cout << "]" << endl;

	Mat kx, ky;

	getDerivKernels(kx, ky, 2, 2, 7, true);

	Mat_<float>::const_iterator kit = kx.begin<float>();
	Mat_<float>::const_iterator kitend = kx.end<float>();
	cout << "[";
	for (; kit != kitend; ++kit) {

		cout << *kit << " ";
	}

	cout << "]" << endl;

	image = imread("salted.bmp",0);

	if (!image.data)
		return 0;

	namedWindow("S&P Image");
	imshow("S&P Image", image);

	blur(image, result, Size(5, 5));

	namedWindow("Mean filtered S&P Image");
	imshow("Mean filtered S&P Image", result);

	medianBlur(image, result,5);

	namedWindow("Median filteted Image");
	imshow("Median filtered Image", result);

	image = imread("boldt.jpg", 0);
	Mat reduced(image.rows / 4, image.cols / 4, CV_8U);

	for (int i = 0; i < reduced.rows; i++)
		for (int j = 0; j < reduced.cols; j++)
			reduced.at<uchar>(i, j) = image.at<uchar>(i * 4, j * 4);


	namedWindow("Badly reduced Image");
	imshow("Badly reduced Image", reduced);

	resize(reduced, reduced, Size(), 4, 4, INTER_NEAREST);

	namedWindow("Badly reduced");
	imshow("Badly reduced", reduced);

	imwrite("badlyreducedimage.bmp",reduced);

	GaussianBlur(image, image, Size(11, 11), 1.75);

	Mat reduced2(image.rows / 4, image.cols / 4, CV_8U);
	for (int i = 0; i < reduced2.rows; i++)
		for (int j = 0; j < reduced2.cols; j++)
			reduced2.at<uchar>(i, j) = image.at<uchar>(i * 4, j * 4);

	namedWindow("Reduced Image, original size");
	imshow("Reduced Image, original size", reduced2);

	imwrite("reducedimage.bmp", reduced2);

	Mat newImage;
	resize(reduced2, newImage, Size(), 4, 4, INTER_NEAREST);

	namedWindow("Reduced Image");
	imshow("Reduced Image", newImage);

	resize(reduced2, newImage, Size(), 4, 4, INTER_LINEAR);

	namedWindow("Bilinear resizing");
	imshow("Bilinear resizing", newImage);

	Mat pyramid(image.rows, image.cols + image.cols / 2 + image.cols / 4 + image.cols / 8, CV_8U, Scalar(255));

	image.copyTo(pyramid(Rect(0, 0, image.cols, image.rows)));

	pyrDown(image, reduced);
	reduced.copyTo(pyramid(Rect(image.cols, image.rows / 2, image.cols / 2, image.rows / 2)));
	pyrDown(reduced, reduced2);
	reduced2.copyTo(pyramid(Rect(image.cols + image.cols / 2, image.rows - image.rows / 4, image.cols / 4, image.rows / 4)));

	pyrDown(reduced2, reduced);
	reduced.copyTo(pyramid(cv::Rect(image.cols + image.cols / 2 + image.cols / 4, image.rows - image.rows / 8, image.cols / 8, image.rows / 8)));

	namedWindow("Pyramid of images");
	imshow("Pyramid of images", pyramid);

	waitKey();

	return 0;



}