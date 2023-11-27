#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
	cv::Mat image = cv::imread("boldt.jpg");
	if (!image.data)
		return 0;


	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

	cv::Rect rectangle(50, 25, 210, 180);

	cv::Mat bgModel, fgModel;

	cv::Mat result;

	cv::grabCut(image,
		result,
		rectangle,
		bgModel, fgModel,
		5,
		cv::GC_INIT_WITH_RECT);


	cv::compare(result, cv::GC_PR_FGD,result, cv::CMP_EQ);


	cv::Mat foreground(image.size(), CV_8UC3,
		cv::Scalar(255, 255, 255));

	image.copyTo(foreground, result);

	cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);
	cv::namedWindow("Image with rectangle");
	cv::imshow("Image with rectangle", image);

	cv::namedWindow("Foreground object");
	cv::imshow("Foreground object", foreground);

	cv::waitKey();

	return 0;


}