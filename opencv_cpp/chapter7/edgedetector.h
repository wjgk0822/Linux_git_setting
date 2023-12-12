#if !defined SOBELEDGES 

#define SOBELEDGES 

#define PI 3.1415926

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class EdgeDetector {

private:

	Mat img;

	Mat sobel;

	int aperture;

	Mat sobelMagnitude;

	Mat sobelOrientation;

public:

	EdgeDetector():aperture(3){}

	void setAperture(int a) {

		aperture = a;
	}

	int getAperture() const {

		return aperture;
	}

	void computeSobel(const cv::Mat& image) {

		Mat sobelX;
		Mat sobelY;

		Sobel(image, sobelX, CV_32F, 1, 0, aperture);
		Sobel(image, sobelY, CV_32F, 0, 1, aperture);

		cartToPolar(sobelX, sobelY, sobelMagnitude, sobelOrientation);
	}

	void computeSobel(const cv::Mat& image, Mat& sobelX, Mat& sobelY) {

		Sobel(image, sobelX, CV_32F, 1, 0, aperture);
		Sobel(image, sobelY, CV_32F, 0, 1, aperture);

		cartToPolar(sobelX, sobelY, sobelMagnitude, sobelOrientation);
	}

	Mat getMagnitude() {

		return sobelMagnitude;
	}

	Mat getOrientation() {

		return sobelOrientation;
	}

	Mat getBinaryMap(double threshold) {

		Mat bin;
		cv::threshold(sobelMagnitude, bin, threshold, 255, THRESH_BINARY_INV);

		return bin;
	}

	Mat getSobelImage() {

		Mat bin;

		double minval, maxval;

		minMaxLoc(sobelMagnitude, &minval, &maxval);
		sobelMagnitude.convertTo(bin, CV_8U, 255 / maxval);

		return bin;
	}


	Mat getSobelOrientationImage() {

		Mat bin;

		sobelOrientation.convertTo(bin, CV_8U, 90 / PI);

		return bin;
	}
};

#endif
