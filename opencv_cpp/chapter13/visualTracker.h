#if !defined FTRACKER
#define FTRACKER

#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking/tracking.hpp>

#include "videoprocessor.h"


cv::Rect convertRect2dToRect(const cv::Rect2d& rect2d) {
    return cv::Rect(static_cast<int>(rect2d.x),
        static_cast<int>(rect2d.y),
        static_cast<int>(rect2d.width),
        static_cast<int>(rect2d.height));
}

class VisualTracker : public FrameProcessor {
    cv::Ptr<cv::Tracker> tracker;
    cv::Rect box;
    bool reset;

public:
    // constructor specifying the tracker to be used
    VisualTracker(cv::Ptr<cv::Tracker> tracker) : reset(true), tracker(tracker) {}

    // set the bounding box to initiate tracking
    void setBoundingBox(const cv::Rect2d& bb) {
        box = bb;
        reset = true;
    }

    // callback processing method
    void process(cv::Mat& frame, cv::Mat& output) {
        if (reset) { // new tracking session
            reset = false;
            tracker->init(frame, box);
        }
        else { // update the target's position
            //cv::Rect rectAsRect = convertRect2dToRect(box);
            tracker->update(frame,box);
        }

        // draw bounding box on current frame
        frame.copyTo(output);
        cv::rectangle(output, box, cv::Scalar(255, 255, 255), 2);
    }
};

#endif
