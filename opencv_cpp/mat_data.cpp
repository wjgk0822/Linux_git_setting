#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// 함수를 호출하여 새로운 이미지를 생성하는 함수
cv::Mat function_img()
{
    // 500x500 크기의 8비트 단일 채널 행렬을 생성하고, 픽셀 값을 50으로 설정
    cv::Mat img(500, 500, CV_8U, 50);

    return img;
}

int main(int argc, char** argv)
{
    // Step 1: 이미지 생성과 표시
    cv::Mat image1(240, 320, CV_8U, 100);
    cv::imshow("Image", image1);
    cv::waitKey(0);

    // Step 2: 이미지 크기 변경 및 값 설정
    image1.create(200, 200, CV_8U);
    image1 = 200;
    cv::imshow("Image", image1);
    cv::waitKey(0);

    // Step 3: 3채널 컬러 이미지 생성과 표시
    cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));
    cv::imshow("ColorImage", image2);
    cv::waitKey(0);

    // Step 4: 이미지 파일 불러오기
    cv::Mat image3 = cv::imread("dog.jpg");

    if (image3.empty())
    {
        std::cout << "이미지 파일을 읽는 중 오류 발생." << std::endl;
        return 1;
    }

    // Step 5: 이미지 복사 및 별칭 설정
    cv::Mat image4(image3);
    image1 = image3;

    // 이미지 복사
    image3.copyTo(image2);

    // 이미지 클론
    cv::Mat image5 = image3.clone();

    // 이미지 좌우 반전
    cv::flip(image3, image3, 1);

    // 생성된 이미지 표시
    cv::imshow("Image 3", image3);
    cv::imshow("Image 1", image1);
    cv::imshow("Image 2", image2);
    cv::imshow("Image 4", image4);
    cv::imshow("Image 5", image5);

    cv::waitKey(0);

    // Step 6: 함수를 호출하여 그레이스케일 이미지 생성
    cv::Mat gray_img = function_img();
    cv::imshow("GrayImage", gray_img);
    cv::waitKey(0);

    // Step 7: 이미지를 불러와서 데이터 형식 변환
    image1 = cv::imread("dog.jpg");
    image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);
    cv::imshow("ImageGray", image2);
    cv::waitKey(0);

    return 0;
}
