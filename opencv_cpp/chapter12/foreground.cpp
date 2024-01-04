#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/bgsegm.hpp>

#include "videoprocessor.h"
#include "BGFGSegmentor.h"

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture("bike.avi");

	if (!capture.isOpened())
		return 0;

	Mat frame;

	Mat foreground;

	Mat background;

	namedWindow("Extracted Foreground");

	Ptr<BackgroundSubtractor> ptrMOG = bgsegm::createBackgroundSubtractorMOG();

	bool stop(false);

	while (!stop) {

		if (!capture.read(frame))
			break;


		ptrMOG->apply(frame, foreground,0.01);

		threshold(foreground, foreground, 128, 255, THRESH_BINARY_INV);

		imshow("Extracted Foreground", foreground);

		if (waitKey(10) >= 0)
			stop = true;


	}

	waitKey();


	VideoProcessor processor;

	BGFGSegmentor segmentor;

	segmentor.setThreshold(25);

	processor.setInput("bike.avi");

	processor.setFrameProcessor(&segmentor);

	processor.displayOutput("Extracted Foreground");

	processor.setDelay(1000. / processor.getFrameRate());

	processor.run();

	waitKey();



}