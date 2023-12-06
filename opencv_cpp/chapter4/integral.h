#if !defined IINTEGRAL
#define IINTEGRAL

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>

template <typename T,int N>

class IntegralImage {
	cv::Mat integralImage;


public:

	IntegralImage(cv::Mat image) {

		cv::integral(image, integralImage, cv::DataType<T>::type);
	}


	cv::Vec<T, N> operator()(int xo, int yo, int width, int height) {

		return (integralImage.at<cv::Vec<T, N> >(yo + height, xo + width)
			- integralImage.at<cv::Vec<T, N> >(yo + height, xo)
			- integralImage.at<cv::Vec<T, N> >(yo, xo + width)
			+ integralImage.at<cv::Vec<T, N> >(yo, xo));
	}

	cv::Vec<T, N> operator()(int x, int y, int radius) {

		// square window centered at (x,y) of size 2*radius+1
		return (integralImage.at<cv::Vec<T, N> >(y + radius + 1, x + radius + 1)
			- integralImage.at<cv::Vec<T, N> >(y + radius + 1, x - radius)
			- integralImage.at<cv::Vec<T, N> >(y - radius, x + radius + 1)
			+ integralImage.at<cv::Vec<T, N> >(y - radius, x - radius));
	}


};

void convertToBinaryPlanes(const cv::Mat& input, cv::Mat& output, int nPlanes) {

	int n = 8 - static_cast<int>(log(static_cast<double>(nPlanes)) / log(2.0));

	uchar mask = 0xFF << n;

	std::vector<cv::Mat> planes;

	cv::Mat reduced = input & mask;

	for (int i = 0; i < nPlanes; i++) {

		planes.push_back((reduced == (i << n)) & 0x1);
	}

	cv::merge(planes, output);


}




#endif
