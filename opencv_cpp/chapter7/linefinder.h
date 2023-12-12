#if !defined LINEF

#define LINEF 

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#define PI 3.1415926

using namespace std;
using namespace cv;

class LineFinder {

private:

	Mat img;

	vector<Vec4i>lines;

	double deltaRho;
	double deltaTheta;

	int minVote;

	double minLength;

	double maxGap;

public:

	LineFinder() : deltaRho(1), deltaTheta(PI / 180), minVote(10), minLength(0.), maxGap(0.) {}

	//LineFinder():deltaRho(1),deltaTheta(PI/180),minLength(0.),maxGap(0.),minVote(10){}

	void setAccResolution(double dRho, double dTheta) {

		deltaRho = dRho;
		deltaTheta = dTheta;
	}

	void setMinVote(int minv) {

		minVote = minv;
	}

	void setLineLengthAndGap(double length, double gap) {

		minLength = length;
		maxGap = gap;
	}

	vector<Vec4i> findLines(Mat& binary) {

		lines.clear();
		HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);

		return lines;
	}

	void drawDetectedLines(Mat& image, Scalar color = Scalar(255, 255, 255)) {

		vector<Vec4i>::const_iterator it2 = lines.begin();

		while (it2 != lines.end()) {

			Point pt1((*it2)[0], (*it2)[1]);
			Point pt2((*it2)[2], (*it2)[3]);

			line(image, pt1, pt2, color);

			++it2;
		}
	}


	std::vector<cv::Vec4i> removeLinesOfInconsistentOrientations(
		const cv::Mat& orientations, double percentage, double delta) {

		std::vector<cv::Vec4i>::iterator it = lines.begin();

		// check all lines
		while (it != lines.end()) {

			// end points
			int x1 = (*it)[0];
			int y1 = (*it)[1];
			int x2 = (*it)[2];
			int y2 = (*it)[3];

			// line orientation + 90o to get the parallel line
			double ori1 = atan2(static_cast<double>(y1 - y2), static_cast<double>(x1 - x2)) + PI / 2;
			if (ori1 > PI) ori1 = ori1 - 2 * PI;

			double ori2 = atan2(static_cast<double>(y2 - y1), static_cast<double>(x2 - x1)) + PI / 2;
			if (ori2 > PI) ori2 = ori2 - 2 * PI;

			// for all points on the line
			cv::LineIterator lit(orientations, cv::Point(x1, y1), cv::Point(x2, y2));
			int i, count = 0;
			for (i = 0, count = 0; i < lit.count; i++, ++lit) {

				float ori = *(reinterpret_cast<float*>(*lit));

				// is line orientation similar to gradient orientation ?
				if (std::min(fabs(ori - ori1), fabs(ori - ori2)) < delta)
					count++;

			}

			double consistency = count / static_cast<double>(i);

			// set to zero lines of inconsistent orientation
			if (consistency < percentage) {

				(*it)[0] = (*it)[1] = (*it)[2] = (*it)[3] = 0;

			}

			++it;
		}

		return lines;
	}
};

#endif
