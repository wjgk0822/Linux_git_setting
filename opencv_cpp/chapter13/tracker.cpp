#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/video/tracking.hpp>


#include "featuretracker.h"


int main()
{

	VideoProcessor processor;

	FeatureTracker tracker;

	processor.setInput("bike.avi");

	processor.setFrameProcessor(&tracker);

	processor.displayOutput("Tracked Features");

	processor.setDelay(1000. / processor.getFrameRate());

	processor.stopAtFrameNo(90);

	processor.run();

	cv::waitKey();


}