#if !defined COLHISTOGRAM
#define COLHISTOGRAM

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ColorHistogram {
private:
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];

public:

	ColorHistogram() {
		histSize[0] = histSize[1] = histSize[2] = 256;
		hranges[0] = 0.0;
		hranges[1] = 256.0;
		ranges[0] = hranges;
		ranges[1] = hranges;
		ranges[2] = hranges;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;

	}

	void setSize(int size) {
		histSize[0] = histSize[1] = histSize[2] = size;
	}

	cv::Mat getHistogram(const cv::Mat& image) {
		cv::Mat hist;

		hranges[0] = 0.0;
		hranges[1] = 256.0;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;

		cv::calcHist(&image,
			1,
			channels,
			cv::Mat(),
			hist,
			3,
			histSize,
			ranges
		);

		return hist;
	}

	cv::SparseMat getSparseHistogram(const cv::Mat& image) {
		cv::SparseMat hist(3,
			histSize,
			CV_32F);

		hranges[0] = 0.0;
		hranges[1] = 256.0;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;


		cv::calcHist(&image,
			1,
			channels,
			cv::Mat(),
			hist,
			3,
			histSize,
			ranges
		);

		return hist;
	}


	cv::Mat getHueHistogram(const cv::Mat& image,
		int minSaturation = 0) {
		cv::Mat hist;

		cv::Mat hsv;
		cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

		cv::Mat mask;

		if (minSaturation > 0) {
			std::vector<cv::Mat> v;
			cv::split(hsv, v);

			cv::threshold(v[1], mask, minSaturation, 255,
				cv::THRESH_BINARY);
		}

		hranges[0] = 0.0;
		hranges[1] = 180.0;
		channels[0] = 0;

		cv::calcHist(&hsv,
			1,
			channels,
			mask,
			hist,
			1,
			histSize,
			ranges
		);

		return hist;
	}


	cv::Mat getabHistogram(const cv::Mat& image) {

		cv::Mat hist;

		cv::Mat lab;
		cv::cvtColor(image, lab, cv::COLOR_BGR2Lab);

		hranges[0] = 0;
		hranges[1] = 256.0;
		channels[0] = 1;
		channels[1] = 2;

		cv::calcHist(&lab,
			1,
			channels,
			cv::Mat(),
			hist,
			2,
			histSize,
			ranges
		);

		return hist;
	}
};

#endif