#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

#include "visualTracker.h"

using namespace std;
using namespace cv;

int main()
{

	VideoProcessor processor;

	vector<string>imgs;

	string prefix = "goose/goose";
	string ext = ".bmp";

	for (long i = 130; i < 317; i++) {

		string name(prefix);
		ostringstream ss; ss << setfill('0') << setw(3) << i; name += ss.str();
		name += ext;

		cout << name << endl;
		imgs.push_back(name);
	}


	VisualTracker tracker(cv::TrackerKCF::create());

	// Open video file
	processor.setInput(imgs);

	// set frame processor
	processor.setFrameProcessor(&tracker);

	// Declare a window to display the video
	processor.displayOutput("Tracked object");

	// Define the frame rate for display
	processor.setDelay(50);

	// Specify the original target position
	cv::Rect bb(290, 100, 65, 40);
	tracker.setBoundingBox(bb);

	// Start the tracking
	processor.run();

	cv::waitKey();

	// Illustration of the Median Tracker principle
	cv::Mat image1 = cv::imread("goose/goose130.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);

	// define a regular grid of points
	std::vector<cv::Point2f> grid;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cv::Point2f p(bb.x + i * bb.width / 10., bb.y + j * bb.height / 10);
			grid.push_back(p);
		}
	}

	// track in next image
	cv::Mat image2 = cv::imread("goose/goose131.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);
	std::vector<cv::Point2f> newPoints;
	std::vector<uchar> status; // status of tracked features
	std::vector<float> err;    // error in tracking

	// track the points
	cv::calcOpticalFlowPyrLK(image1, image2, // 2 consecutive images
		grid,      // input point position in first image
		newPoints, // output point postion in the second image
		status,    // tracking success
		err);      // tracking error

	// Draw the points
	for (cv::Point2f p : grid) {

		cv::circle(image1, p, 1, cv::Scalar(255, 255, 255), -1);
	}
	cv::imshow("Initial points", image1);

	for (cv::Point2f p : newPoints) {

		cv::circle(image2, p, 1, cv::Scalar(255, 255, 255), -1);
	}
	cv::imshow("Tracked points", image2);

	cv::waitKey();


}