#if !defined LAPLACEZC 
#define LAPLACEZC 

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class LaplacianZC {

private:
	Mat laplace;

	int aperture;

public:

	LaplacianZC():aperture(3){}

	void setAperture(int a) {

		aperture = a;
	}

	int getAperture() const {

		return aperture;
	}

	Mat computeLaplacian(const cv::Mat& image) {

		Laplacian(image, laplace, CV_32F, aperture);

		return laplace;
	}

	Mat getLaplacianImage(double scale = -1.0) {

		if (scale < 0) {

			double lapmin, lapmax;

			minMaxLoc(laplace, &lapmin, &lapmax);
		}

		Mat laplaceImage;
		laplace.convertTo(laplaceImage, CV_8U, scale, 128);

		return laplaceImage;
	}

	Mat getZeroCrossings(Mat laplace) {

		Mat signImage;
		threshold(laplace, signImage, 0, 255, THRESH_BINARY);

		Mat binary;
		signImage.convertTo(binary, CV_8U);

		Mat dilated;
		dilate(binary, dilated, Mat());

		return dilated - binary;
	}
	
};







#endif
