#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/xfeatures2d.hpp>

int main()
{
    // Read input images
    cv::Mat image1 = cv::imread("church01.jpg", 0);
    cv::Mat image2 = cv::imread("church03.jpg", 0);

    if (!image1.data || !image2.data)
        return 0;

    // Display the images
    cv::namedWindow("Right Image");
    cv::imshow("Right Image", image1);
    cv::namedWindow("Left Image");
    cv::imshow("Left Image", image2);

    // vector of keypoints and descriptors
    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;
    cv::Mat descriptors1, descriptors2;

    // Construction of the SIFT feature detector
    cv::Ptr<cv::Feature2D> ptrFeature2D = cv::SIFT::create(164);

    // Detection of the SURF features
    ptrFeature2D->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
    ptrFeature2D->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

    std::cout << "Number of SIFT points (1): " << keypoints1.size() << std::endl;
    std::cout << "Number of SIFT points (2): " << keypoints2.size() << std::endl;

    // Draw the keypoints
    cv::Mat imageKP;
    cv::drawKeypoints(image1, keypoints1, imageKP, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("Right SIFT Features");
    cv::imshow("Right SIFT Features", imageKP);
    cv::drawKeypoints(image2, keypoints2, imageKP, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow("Left SIFT Features");
    cv::imshow("Left SIFT Features", imageKP);

    // Construction of the matcher
    cv::BFMatcher matcher(cv::NORM_L2, true);

    // Match the two image descriptors
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    std::cout << "Number of matched points: " << matches.size() << std::endl;

    // Manually select a few Matches
    std::vector<cv::DMatch> selMatches;

    // Make sure to double-check if the selected matches are valid
    selMatches.push_back(matches[2]);
    selMatches.push_back(matches[5]);
    selMatches.push_back(matches[16]);
    selMatches.push_back(matches[29]);
    selMatches.push_back(matches[14]);
    selMatches.push_back(matches[34]);
    selMatches.push_back(matches[20]);

    // Draw the selected matches
    cv::Mat imageMatches;
    cv::drawMatches(image1, keypoints1, image2, keypoints2, selMatches, imageMatches, cv::Scalar(255, 255, 255), cv::Scalar(255, 255, 255));
    cv::namedWindow("Matches");
    cv::imshow("Matches", imageMatches);

    // Convert 1 vector of keypoints into 2 vectors of Point2f
    std::vector<int> pointIndexes1;
    std::vector<int> pointIndexes2;
    for (std::vector<cv::DMatch>::const_iterator it = selMatches.begin(); it != selMatches.end(); ++it)
    {
        // Get the indexes of the selected matched keypoints
        pointIndexes1.push_back(it->queryIdx);
        pointIndexes2.push_back(it->trainIdx);
    }

    // Convert keypoints into Point2f
    std::vector<cv::Point2f> selPoints1, selPoints2;
    cv::KeyPoint::convert(keypoints1, selPoints1, pointIndexes1);
    cv::KeyPoint::convert(keypoints2, selPoints2, pointIndexes2);

    // Check by drawing the points
    std::vector<cv::Point2f>::const_iterator it = selPoints1.begin();
    while (it != selPoints1.end())
    {
        // Draw a circle at each corner location
        cv::circle(image1, *it, 3, cv::Scalar(255, 255, 255), 2);
        ++it;
    }

    it = selPoints2.begin();
    while (it != selPoints2.end())
    {
        // Draw a circle at each corner location
        cv::circle(image2, *it, 3, cv::Scalar(255, 255, 255), 2);
        ++it;
    }

    // Compute F matrix from 7 matches
    cv::Mat fundamental = cv::findFundamentalMat(selPoints1, selPoints2, cv::FM_7POINT);

    std::cout << "F-Matrix size= " << fundamental.rows << "," << fundamental.cols << std::endl;

    cv::Mat fund(fundamental, cv::Rect(0, 0, 3, 3));

    // Draw the left points corresponding epipolar lines in the right image
    std::vector<cv::Vec3f> lines1;
    cv::computeCorrespondEpilines(selPoints1, 1, fund, lines1);

    std::cout << "size of F matrix:" << fund.rows << "x" << fund.cols << std::endl;

    // For all epipolar lines
    for (std::vector<cv::Vec3f>::const_iterator it = lines1.begin(); it != lines1.end(); ++it)
    {
        // Draw the epipolar line between the first and last column
        cv::line(image2, cv::Point(0, -(*it)[2] / (*it)[1]), cv::Point(image2.cols, -((*it)[2] + (*it)[0] * image2.cols) / (*it)[1]), cv::Scalar(255, 255, 255));
    }

    // Draw the left points corresponding epipolar lines in the left image
    std::vector<cv::Vec3f> lines2;
    cv::computeCorrespondEpilines(cv::Mat(selPoints2), 2, fund, lines2);

    for (std::vector<cv::Vec3f>::const_iterator it = lines2.begin(); it != lines2.end(); ++it)
    {
        // Draw the epipolar line between the first and last column
        cv::line(image1, cv::Point(0, -(*it)[2] / (*it)[1]), cv::Point(image1.cols, -((*it)[2] + (*it)[0] * image1.cols) / (*it)[1]), cv::Scalar(255, 255, 255));
    }

    // Combine both images
    cv::Mat both(image1.rows, image1.cols + image2.cols, CV_8U);
    image1.copyTo(both.colRange(0, image1.cols));
    image2.copyTo(both.colRange(image1.cols, image1.cols + image2.cols));

    // Display the images with points and epipolar lines
    cv::namedWindow("Epilines");
    cv::imshow("Epilines", both);

    cv::waitKey();
    return 0;
}
