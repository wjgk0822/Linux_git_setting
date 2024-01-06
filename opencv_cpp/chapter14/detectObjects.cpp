#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

int main()
{

	vector<Mat> referenceImages;

	referenceImages.push_back(imread("stopSamples/stop00.png"));
	referenceImages.push_back(imread("stopSamples/stop01.png"));
	referenceImages.push_back(imread("stopSamples/stop02.png"));
	referenceImages.push_back(imread("stopSamples/stop03.png"));
	referenceImages.push_back(imread("stopSamples/stop04.png"));
	referenceImages.push_back(imread("stopSamples/stop05.png"));
	referenceImages.push_back(imread("stopSamples/stop06.png"));
	referenceImages.push_back(imread("stopSamples/stop07.png"));

	Mat positveImages(2 * referenceImages[0].rows, 4 * referenceImages[0].cols, CV_8UC3);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 4; j++) {

			referenceImages[i * 2 + j].copyTo(positveImages(cv::Rect(j * referenceImages[i * 2 + j].cols, i * referenceImages[i * 2 + j].rows, referenceImages[i * 2 + j].cols, referenceImages[i * 2 + j].rows)));
		}

	cv::imshow("Positive samples", positveImages);

	cv::Mat negative = cv::imread("stopSamples/bg01.jpg");
	cv::resize(negative, negative, cv::Size(), 0.33, 0.33);
	cv::imshow("One negative sample", negative);

	cv::Mat inputImage = cv::imread("stopSamples/stop9.jpg");
	cv::resize(inputImage, inputImage, cv::Size(), 0.5, 0.5);

	cv::CascadeClassifier cascade;
	if (!cascade.load("stopSamples/classifier/cascade.xml")) {
		std::cout << "Error when loading the cascade classfier!" << std::endl;
		return -1;
	}



	std::vector<cv::Rect> detections;

	cascade.detectMultiScale(inputImage, // input image 
		detections, // detection results
		1.1,        // scale reduction factor
		1,          // number of required neighbor detections
		0,          // flags (not used)
		cv::Size(48, 48),    // minimum object size to be detected
		cv::Size(128, 128)); // maximum object size to be detected

	std::cout << "detections= " << detections.size() << std::endl;
	for (int i = 0; i < detections.size(); i++)
		cv::rectangle(inputImage, detections[i], cv::Scalar(255, 255, 255), 2);

	cv::imshow("Stop sign detection", inputImage);

	// Detecting faces
	cv::Mat picture = cv::imread("girl.jpg");
	cv::CascadeClassifier faceCascade;
	if (!faceCascade.load("stopSamples/classifier/haarcascade_frontalface_default.xml")) {
		std::cout << "Error when loading the face cascade classfier!" << std::endl;
		return -1;
	}

	faceCascade.detectMultiScale(picture, // input image 
		detections, // detection results
		1.1,        // scale reduction factor
		3,          // number of required neighbor detections
		0,          // flags (not used)
		cv::Size(48, 48),    // minimum object size to be detected
		cv::Size(128, 128)); // maximum object size to be detected

	std::cout << "detections= " << detections.size() << std::endl;
	// draw detections on image
	for (int i = 0; i < detections.size(); i++)
		cv::rectangle(picture, detections[i], cv::Scalar(255, 255, 255), 2);

	// Detecting eyes
	cv::CascadeClassifier eyeCascade;
	if (!eyeCascade.load("stopSamples/classifier/haarcascade_eye.xml")) {
		std::cout << "Error when loading the eye cascade classfier!" << std::endl;
		return -1;
	}

	eyeCascade.detectMultiScale(picture,
		detections,
		1.1,
		3,
		0,
		Size(24, 24),
		Size(64, 64));

	cout << "detections= " << detections.size() << endl;

	for (int i = 0; i < detections.size(); i++)
		rectangle(picture, detections[i], Scalar(0, 0, 0), 2);

	imshow("Detection results", picture);

	waitKey();


}