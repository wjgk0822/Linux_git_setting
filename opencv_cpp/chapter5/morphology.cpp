#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("binary.bmp");
	if (!image.data)
		return 0;

	namedWindow("Image");
	imshow("Image", image);

	Mat eroded;
	erode(image, eroded, Mat());

	namedWindow("Eroded Image");
	imshow("Eroded Image", eroded);

	Mat dilated;
	dilate(image, dilated, Mat());

	namedWindow("Dilated Image");
	imshow("Dilated Image", dilated);

	Mat element(7, 7, CV_8U, Scalar(1));

	erode(image, eroded, element);

	namedWindow("Eroded Image (7x7)");
	imshow("Eroded Image (7x7)", eroded);

	erode(image, eroded, Mat(), Point(-1, -1), 3);

	namedWindow("Eroded Image (3 times)");
	imshow("Eroded Image (3 times)", eroded);

	Mat element5(5, 5, CV_8U, Scalar(1));
	Mat closed;
	morphologyEx(image, closed,
		MORPH_CLOSE,
		element5);


	namedWindow("Closed Image");
	imshow("Closed Image", closed);

	Mat opened;
	morphologyEx(image, opened, MORPH_OPEN, element5);

	namedWindow("Opened Image");
	imshow("Opened Image", opened);

	Mat result;
	dilate(image, result, element5);

	erode(result, result, element5);

	namedWindow("Closed Image (2)");
	imshow("Closed Image (2)", result);

	morphologyEx(image, image, MORPH_CLOSE, element5);
	morphologyEx(image, image, MORPH_OPEN, element5);

	namedWindow("Closed|Opend Image");
	imshow("Closed|Opened Image", image);
	imwrite("binaryGroup.bmp", image);

	image = imread("binary.bmp");

	morphologyEx(image, image, MORPH_OPEN, element5);
	morphologyEx(image, image, MORPH_CLOSE, element5);

	namedWindow("Opened|Closed Image");
	imshow("Opened|Closed Image", image);

	image = imread("boldt.jpg", 0);

	if (!image.data)
		return 0; 

	morphologyEx(image, result, MORPH_GRADIENT, Mat());

	namedWindow("Edge Image");
	imshow("Edge Image", 255 - result);

	int threshold(80);
	cv::threshold(result, result,
		threshold, 255, THRESH_BINARY);

	namedWindow("Thresholded Edge Image");
	imshow("Threshold Edge Image", result);

	morphologyEx(image, result, MORPH_GRADIENT, Mat());

	image = imread("book.jpg", 0);

	if (!image.data)
		return 0;

	transpose(image, image);
	flip(image, image, 0);

	Mat element7(7, 7, CV_8U, Scalar(1));
	morphologyEx(image, result, MORPH_BLACKHAT, element7);

	namedWindow("7x7 Black Top-hat Image");
	imshow("7x7 Black Top-hat Image", 255 - result);

	threshold = 25;
	cv::threshold(result, result,
		threshold, 255, THRESH_BINARY);

	namedWindow("Threshold Black Top-hat");
	imshow("Threshold Black Top-hat", 255 - result);

	morphologyEx(image, result, MORPH_CLOSE, element7);

	namedWindow("7x7 Closed Image");
	imshow("7x7 Closed Image", 255 - result);

	waitKey();

	return 0;


}