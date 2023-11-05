#include <iostream>
#include <random>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// 소금과 후추 노이즈를 추가하는 함수 정의
void salt_pepper_noise(cv::Mat image, int num)
{
    // C++의 <random> 헤더를 사용하여 난수 생성
    std::default_random_engine generator;
    // 이미지의 행(row) 좌표 범위를 정의
    std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
    // 이미지의 열(column) 좌표 범위를 정의
    std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

    // 주어진 횟수만큼 소금과 후추 노이즈를 추가
    for (int k = 0; k < num; ++k)
    {
        // 임의의 행(row) 및 열(column) 좌표를 생성
        int row_coordinate = randomRow(generator);
        int col_coordinate = randomCol(generator);

        if (image.type() == CV_8UC1)
        {
            // 그레이스케일 이미지에 노이즈 추가
            image.at<uchar>(row_coordinate, col_coordinate) = 255;
        }
        else if (image.type() == CV_8UC3)
        {
            // 컬러 이미지에 노이즈 추가 (모든 채널에 흰색 픽셀)
            image.at<cv::Vec3b>(row_coordinate, col_coordinate)[0] = 255;
            image.at<cv::Vec3b>(row_coordinate, col_coordinate)[1] = 255;
            image.at<cv::Vec3b>(row_coordinate, col_coordinate)[2] = 255;
        }
    }
}

// 소금 노이즈를 추가하는 함수 정의 (그레이스케일 이미지에만 적용)
void salt_noise(cv::Mat image, int n)
{
    CV_Assert(image.type() == CV_8UC1); // 그레이스케일 이미지인지 확인

    // C++의 <random> 헤더를 사용하여 난수 생성
    std::default_random_engine generator;
    // 이미지의 행(row) 좌표 범위를 정의
    std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
    // 이미지의 열(column) 좌표 범위를 정의
    std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

    // 주어진 횟수만큼 소금 노이즈를 추가
    cv::Mat_<uchar> img(image);
    for (int k = 0; k < n; ++k)
    {
        // 임의의 열(column) 및 행(row) 좌표를 생성
        int x = randomCol(generator);
        int y = randomRow(generator);

        // 해당 좌표에 흰색 픽셀(255)을 설정하여 소금 노이즈 추가
        img(y, x) = 255;
    }
}

int main(int argc, char** argv)
{
    // 이미지 파일을 읽어옵니다.
    cv::Mat image = cv::imread("boldt.jpg", 1); // 1은 컬러 이미지로 읽기를 지정

    // 소금과 후추 노이즈를 이미지에 추가
    salt_pepper_noise(image, 3000);

    // 윈도우를 생성하고 이미지를 화면에 표시합니다.
    cv::namedWindow("SaltImage");
    cv::imshow("SaltImage", image);

    // 이미지를 파일로 저장합니다.
    cv::imwrite("salted.bmp", image);

    // 사용자 입력을 기다립니다.
    cv::waitKey(0);

    // 이미지를 다시 그레이스케일로 읽어옵니다.
    image = cv::imread("boldt.jpg", 0); // 0은 그레이스케일 이미지로 읽기를 지정

    // 소금 노이즈를 이미지에 추가 (그레이스케일 이미지만 지원)
    salt_noise(image, 500);

    // 다시 윈도우를 생성하고 이미지를 화면에 표시합니다.
    cv::namedWindow("SaltImage");
    cv::imshow("SaltImage", image);

    // 사용자 입력을 기다립니다.
    cv::waitKey();

    // 모든 창을 닫습니다.
    cv::destroyAllWindows();

    return 0;
}



//salt_pepper_noise 함수는 주어진 이미지에 흰색 픽셀(255)을 무작위로 추가하여 소금과 후추 노이즈를 생성하고, 
//salt_noise 함수는 그레이스케일 이미지에 소금 노이즈를 추가합니다. 
//이후, 이미지를 화면에 표시하고 파일로 저장하는 등의 작업을 수행합니다.