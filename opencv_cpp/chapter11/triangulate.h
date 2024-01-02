#include <opencv2/core.hpp>
#include <vector>

using namespace std;
using namespace cv;

Vec3d triangulate(const cv::Mat& p1, const cv::Mat& p2, const cv::Vec2d& u1, const cv::Vec2d& u2);
void triangulate(const cv::Mat& p1, const cv::Mat& p2, const vector<cv::Vec2d>& pts1, const std::vector<cv::Vec2d>& pts2, std::vector<cv::Vec3d>& pts3D);


