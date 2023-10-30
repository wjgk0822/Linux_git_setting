#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

void onMouse(int event, int x, int y, int flags, void* param)
{

	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);

	switch (event)
	{

	case cv::EVENT_FLAG_LBUTTON:
		std::cout << "at (" << x << "," << y << ") value is: "
			<< static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;

		break; 

	default:
		break;
	}


}

int main(int argc, char** argv)
{


	cv::Mat image = cv::imread("dog.jpg",cv::IMREAD_GRAYSCALE);

	if (image.empty())
	{
		std::cout << "Error reading image file." << std::endl;
		return 1;

	}
	cv::namedWindow("DrawingImage");

	cv::setMouseCallback("DrawingImage", onMouse, reinterpret_cast<void*>(&image));

	cv::circle(image, cv::Point(155, 110), 65, 0, 3);

	cv::putText(image, "This is a dog.", cv::Point(40, 200), cv::FONT_HERSHEY_PLAIN, 2.0, 255, 2);

	cv::imshow("DrawingImage", image);

	cv::waitKey(0);


	return 0;
}