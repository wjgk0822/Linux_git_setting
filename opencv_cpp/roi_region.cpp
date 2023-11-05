#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv)
{
    // 이미지 파일을 읽어옵니다.
    cv::Mat image = cv::imread("puppy.bmp");
    if (image.empty())
    {
        std::cout << "이미지 파일을 읽어오는 중 오류가 발생했습니다." << std::endl;
        return 1;
    }

    // 로고 이미지 파일을 읽어옵니다.
    cv::Mat logo = cv::imread("smalllogo.png");
    if (logo.empty())
    {
        std::cout << "로고 이미지 파일을 읽어오는 중 오류가 발생했습니다." << std::endl;
        return 1;
    }

    // 이미지의 오른쪽 하단에 로고를 삽입하기 위한 ROI(Region of Interest)를 정의합니다.
    cv::Mat imageROI(image, cv::Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));

    // 로고를 이미지에 삽입합니다.
    logo.copyTo(imageROI);

    // 이미지를 표시할 창을 생성합니다.
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);

    // 이미지를 화면에 표시합니다.
    cv::imshow("Image", image);

    // 사용자가 키 입력을 기다립니다.
    cv::waitKey(0);

    // 원본 이미지를 다시 읽어옵니다.
    image = cv::imread("puppy.bmp");
    if (image.empty())
    {
        std::cout << "이미지 파일을 다시 읽어오는 중 오류가 발생했습니다." << std::endl;
        return 1;
    }

    // 로고를 삽입할 ROI를 재정의합니다.
    imageROI = image(cv::Range(image.rows - logo.rows, image.rows),
        cv::Range(image.cols - logo.cols, image.cols));

    // 로고의 마스크 이미지를 만듭니다.
    cv::Mat mask(logo);

    // 로고를 이미지에 삽입합니다. 로고 이미지 내의 픽셀 값만 적용됩니다.
    logo.copyTo(imageROI, mask);

    // 이미지를 화면에 다시 표시합니다.
    cv::imshow("Image", image);

    // 사용자가 키 입력을 기다립니다.
    cv::waitKey(0);

    // 모든 창을 닫습니다.
    cv::destroyAllWindows();

    return 0;
}
