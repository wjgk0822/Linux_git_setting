#include <iostream>
#include <vector>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/viz.hpp>
#include "robustMatcher.h"


using namespace std;
using namespace cv;

int main()
{
	Mat image1 = imread("brebeuf1.jpg", 0);
	Mat image2 = imread("brebeuf2.jpg", 0);
	if (!image1.data || !image2.data)
		return 0;

	RobustMatcher rmatcher(SIFT::create(250));

	vector<DMatch> matches;

	vector<KeyPoint> keypoints1, keypoints2;
	Mat fundamental = rmatcher.match(image1, image2, matches, keypoints1, keypoints2);

	Mat imageMatches;

	drawMatches(image1, keypoints1,
		image2, keypoints2,
		matches,
		imageMatches,
		Scalar(255, 255, 255),
		Scalar(255, 255, 255),
		std::vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	namedWindow("Matches");
	imshow("Matches", imageMatches);

	std::vector<Point2f> points1, points2;

	for (vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it) {

		float x = keypoints1[it->queryIdx].pt.x;
		float y = keypoints1[it->queryIdx].pt.y;
		points1.push_back(keypoints1[it->queryIdx].pt);

		x = keypoints2[it->trainIdx].pt.x;
		y = keypoints2[it->trainIdx].pt.y;
		points2.push_back(keypoints2[it->trainIdx].pt);

	}

	Mat h1, h2;
	stereoRectifyUncalibrated(points1, points2, fundamental, image1.size(), h1, h2);

	Mat rectified1;

	warpPerspective(image1, rectified1, h1, image1.size());
	Mat rectified2;
	warpPerspective(image2, rectified2, h2, image1.size());

	namedWindow("Left Rectified Image");
	imshow("Left Rectified Image", rectified1);
	namedWindow("Right Rectified Image");
	imshow("Right Rectified Image", rectified2);

	points1.clear();
	points2.clear();

	for (int i = 20; i < image1.rows - 20; i += 20) {

		points1.push_back(Point(image1.cols / 2, i));
		points2.push_back(Point(image2.cols / 2, i));


	}

	vector<Vec3f>lines1;
	computeCorrespondEpilines(points1, 1, fundamental, lines1);

	for (vector<Vec3f>::const_iterator it = lines1.begin(); it != lines1.end(); ++it) {

		cv::line(image2, cv::Point(0, -(*it)[2] / (*it)[1]),
			cv::Point(image2.cols, -((*it)[2] + (*it)[0] * image2.cols) / (*it)[1]),
			cv::Scalar(255, 255, 255));
	}


	std::vector<cv::Vec3f> lines2;
	cv::computeCorrespondEpilines(points2, 2, fundamental, lines2);

	for (std::vector<cv::Vec3f>::const_iterator it = lines2.begin();
		it != lines2.end(); ++it) {

		cv::line(image1, cv::Point(0, -(*it)[2] / (*it)[1]),
			cv::Point(image1.cols, -((*it)[2] + (*it)[0] * image1.cols) / (*it)[1]),
			cv::Scalar(255, 255, 255));
	}

	// Display the images with epipolar lines
	cv::namedWindow("Left Epilines");
	cv::imshow("Left Epilines", image1);
	cv::namedWindow("Right Epilines");
	cv::imshow("Right Epilines", image2);


	cv::namedWindow("Left Epilines");
	cv::imshow("Left Epilines", image1);
	cv::namedWindow("Right Epilines");
	cv::imshow("Right Epilines", image2);

	// draw the pair
	cv::drawMatches(image1, keypoints1,  // 1st image 
		image2, keypoints2,              // 2nd image 
		std::vector<cv::DMatch>(),
		imageMatches,		             // the image produced
		cv::Scalar(255, 255, 255),
		cv::Scalar(255, 255, 255),
		std::vector<char>(),
		cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::namedWindow("A Stereo pair");
	cv::imshow("A Stereo pair", imageMatches);

	// Compute disparity
	cv::Mat disparity;
	cv::Ptr<cv::StereoMatcher> pStereo = cv::StereoSGBM::create(0,   // minimum disparity
		32,  // maximum disparity
		5);  // block size
	pStereo->compute(rectified1, rectified2, disparity);


	double minv, maxv;
	disparity = disparity * 64;
	cv::minMaxLoc(disparity, &minv, &maxv);
	std::cout << minv << "+" << maxv << std::endl;
	// Display the disparity map
	cv::namedWindow("Disparity Map");
	cv::imshow("Disparity Map", disparity);

	cv::waitKey();
	return 0;


}