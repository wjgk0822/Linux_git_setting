#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// Version 1
// 행렬 행을 스캔하며 행 주소의 포인터를 사용합니다.
void colorReduce(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        uchar* data = image.ptr<uchar>(row_index);
        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            data[col_index] = data[col_index] / div * div + div / 2;
        }
    }
}

// Version 2
// 입력 이미지에 대해 깊은 복사를 수행합니다.
void colorReduceIO(const cv::Mat& image, cv::Mat& result, int div = 64)
{
    int num_row = image.rows;
    int num_col = image.cols;
    int num_channel = image.channels();

    // 출력 이미지 할당
    result.create(image.rows, image.cols, image.type());

    for (int row_index = 0; row_index < num_row; ++row_index)
    {
        const uchar* data_in = image.ptr<uchar>(row_index);
        uchar* data_out = result.ptr<uchar>(row_index);

        for (int col_index = 0; col_index < num_row * num_channel; ++col_index)
        {
            // 각 픽셀 처리
            data_out[col_index] = data_in[col_index] / div * div + div / 2;
        }
    }
}

// Version 3
// 행렬 행을 스캔하며 행 주소의 포인터를 사용합니다.
void colorReduce1(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();
    uchar div2 = div >> 1;

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        // 행 주소의 포인터
        uchar* data = image.ptr<uchar>(row_index);
        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            *data++ = *data / div * div + div2;
        }
    }
}

// Version 4
// 행렬 행을 스캔하며 행 주소의 포인터를 사용합니다.
void colorReduce2(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();
    uchar div2 = div >> 1;

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        // 행 주소의 포인터
        uchar* data = image.ptr<uchar>(row_index);
        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            // 모듈로 연산 사용
            int pixel_value = *data;
            *data++ = pixel_value - pixel_value % div + div2;
        }
    }
}

// Version 5
// 행렬 행을 스캔하며 행 주소의 포인터를 사용합니다.
void colorReduce3(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();
    // div는 2의 거듭제곱이어야만 마스크를 사용할 수 있습니다.
    int numbers = static_cast<int>(std::log(static_cast<double>(div)) / std::log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 이진 마스크
    uchar mask = 0xFF << numbers;    // 예: div=16일 때 mask=0xF0
    uchar div2 = 1 << (numbers - 1); // div2 = div / 2;

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        // 행 주소의 포인터
        uchar* data = image.ptr<uchar>(row_index);
        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            // 이진 마스크 연산 사용
            *data &= mask;
            *data++ |= div2; // div/2 더하기
        }
    }
}

// Version 6
// 행렬 행을 스캔하며 행 주소의 포인터를 사용합니다.
void colorReduce4(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();
    int numbers = static_cast<int>(std::log(static_cast<double>(div)) / std::log(2.0) + 0.5);

    int step = image.step; // 유효한 폭
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << numbers;
    uchar div2 = div >> 1;

    // 이미지 버퍼에 대한 포인터를 가져옵니다.
    uchar* data = image.data;

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            *(data + col_index) &= mask;
            *(data + col_index) += div2;
        }
        data += step; // 다음 라인
    }
}

// Version 7
void colorReduce5(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int numbers = static_cast<int>(std::log(static_cast<double>(div)) / std::log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << numbers;

    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        uchar* data = image.ptr<uchar>(row_index);

        for (int col_index = 0; col_index < image.cols * image.channels(); ++col_index)
        {
            // 각 픽셀 처리.
            *data &= mask;
            *data++ += div / 2;
        }
    }
}

// Version 8
// 연속 이미지의 경우 최적화
void colorReduce6(cv::Mat image, int div = 64)
{
    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();

    if (image.isContinuous())
    {
        // 패딩된 픽셀이 없으면
        num_pixels_row = num_pixels_row * num_rows;
        num_rows = 1;
    }

    int numbers = static_cast<int>(std::log(static_cast<double>(div)) / std::log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << numbers;
    uchar div2 = div >> 1;

    // 이 for 루프는 한 번만 실행됩니다.
    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        uchar* data = image.ptr<uchar>(row_index);

        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            *data &= mask;
            *data++ += div2;
        }
    }
}


// Version 9
// 연속된 이미지에 reshape를 적용합니다.
void colorReduce7(cv::Mat image, int div = 64)
{
    if (image.isContinuous())
    {
        // 패딩된 픽셀이 없으면
        // (새로운 채널 수, 새로운 행 수)
        image.reshape(1, 1);
    }

    int num_rows = image.rows;
    int num_pixels_row = image.cols * image.channels();
    int numbers = static_cast<int>(std::log(static_cast<double>(div)) / std::log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << numbers;
    uchar div2 = div >> 1;

    // 이 for 루프는 한 번만 실행됩니다.
    for (int row_index = 0; row_index < num_rows; ++row_index)
    {
        uchar* data = image.ptr<uchar>(row_index);

        for (int col_index = 0; col_index < num_pixels_row; ++col_index)
        {
            // 각 픽셀 처리.
            *data &= mask;
            *data++ += div2;
        }
    }
}

// Version 10
// 루프 내에서 3개 채널을 Mat_ 이터레이터로 처리합니다.
void colorReduce8(cv::Mat image, int div = 64)
{
    uchar div2 = div >> 1;

    cv::Mat_<cv::Vec3b>::iterator iterator_begin = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator iterator_end = image.end<cv::Vec3b>();
    for (; iterator_begin != iterator_end; ++iterator_begin)
    {
        // 각 픽셀 처리.
        (*iterator_begin)[0] = (*iterator_begin)[0] / div * div + div2;
        (*iterator_begin)[1] = (*iterator_begin)[1] / div * div + div2;
        (*iterator_begin)[2] = (*iterator_begin)[2] / div * div + div2;
    }
}

// Version 11
// 루프 내에서 3개 채널을 Mat_ 이터레이터로 처리합니다.
// Vec3b에서 이터레이터 사용
void colorReduce9(cv::Mat image, int div = 64)
{
    cv::Mat_<cv::Vec3b>::iterator iterator_begin = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator iterator_end = image.end<cv::Vec3b>();

    const cv::Vec3b offset(div / 2, div / 2, div / 2);

    for (; iterator_begin != iterator_end; ++iterator_begin)
    {
        // 각 픽셀 처리.
        (*iterator_begin) = (*iterator_begin) / div * div + offset;
    }
}

// Version 12
// 이진 마스크와 함께 이터레이터 사용
void colorReduce10(cv::Mat image, int div = 64)
{
    // div는 2의 거듭제곱이어야 합니다.
    int number = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << number; // 예: div=16일 때 mask= 0xF0
    uchar div2 = div >> 1;  // div2 = div/2

    cv::Mat_<cv::Vec3b>::iterator iterator_begin = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::iterator iterator_end = image.end<cv::Vec3b>();

    for (; iterator_begin != iterator_end; ++iterator_begin)
    {
        // 각 픽셀 처리.
        (*iterator_begin)[0] &= mask;
        (*iterator_begin)[0] += div2;
        (*iterator_begin)[1] &= mask;
        (*iterator_begin)[1] += div2;
        (*iterator_begin)[2] &= mask;
        (*iterator_begin)[2] += div2;
    }
}

// Version 13
// Mat_에서 가져온 이터레이터 사용
void colorReduce11(cv::Mat image, int div = 64)
{
    cv::Mat_<cv::Vec3b> cimage = image;
    cv::Mat_<cv::Vec3b>::iterator iterator_begin = cimage.begin();
    cv::Mat_<cv::Vec3b>::iterator iterator_end = cimage.end();
    uchar div2 = div >> 1;

    for (; iterator_begin != iterator_end; ++iterator_begin)
    {
        // 각 픽셀 처리.
        (*iterator_begin)[0] = (*iterator_begin)[0] / div * div + div2;
        (*iterator_begin)[1] = (*iterator_begin)[1] / div * div + div2;
        (*iterator_begin)[2] = (*iterator_begin)[2] / div * div + div2;
    }
}

// Version 14
// at 메서드 사용
void colorReduce12(cv::Mat image, int div = 64)
{
    int num_row = image.rows;
    int num_col = image.cols;
    uchar div2 = div >> 1;

    for (int row_index = 0; row_index < num_row; ++row_index)
    {
        for (int col_index = 0; col_index < num_col; ++col_index)
        {
            // 각 픽셀 처리
            image.at<cv::Vec3b>(row_index, col_index)[0] =
                image.at<cv::Vec3b>(row_index, col_index)[0] / div * div + div2;
            image.at<cv::Vec3b>(row_index, col_index)[1] =
                image.at<cv::Vec3b>(row_index, col_index)[1] / div * div + div2;
            image.at<cv::Vec3b>(row_index, col_index)[2] =
                image.at<cv::Vec3b>(row_index, col_index)[2] / div * div + div2;
        }
    }
}

// Version 15
// 룩업 테이블 사용
void colorReduce13(cv::Mat image, int div = 64)
{
    cv::Mat lookup(1, 256, CV_8U);

    for (int i = 0; i < 256; i++)
    {
        lookup.at<uchar>(i) = i / div * div + div / 2;
    }

    cv::LUT(image, lookup, image);
}

// Version 16
// Mat 오버로딩된 연산자 사용
void colorReduce14(cv::Mat image, int div = 64)
{
    int number = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
    // 픽셀 값을 반올림하는 데 사용되는 마스크
    uchar mask = 0xFF << number; // 예: div=16일 때 mask= 0xF0
    uchar div2 = div >> 1;

    // 색상 감소 수행
    image = (image & cv::Scalar(mask, mask, mask)) + cv::Scalar(div2, div2, div2);
}

// ----------------------------
const unsigned int NTESTS = 15;
const unsigned int NITERATIONS = 10;


int main(int argc, char** argv)
{
    // 이미지를 읽어옵니다.
    auto image = cv::imread("images/boldt.jpg");
    if (image.empty())
    {
        std::cout << "Error reading image file." << std::endl;
        return 1;
    }

    // 이미지 처리에 소요된 시간을 측정합니다.
    const int64 start = cv::getTickCount();
    colorReduce(image, 64);
    // 경과 시간(초 단위) 계산
    double duration = (cv::getTickCount() - start) / cv::getTickFrequency();

    std::cout << "Duration= " << duration << "secs" << std::endl;

    // 이미지를 표시합니다.
    cv::namedWindow("Image");
    cv::imshow("Image", image);
    cv::waitKey(0);

    // 테스트 버전
    int64 t[NTESTS], tinit;
    // 타이머 값 초기화
    for (int i = 0; i < NTESTS; i++)
        t[i] = 0;

    cv::Mat images[NTESTS];

    // 테스트할 버전들
    typedef void (*FunctionPointer)(cv::Mat, int);
    FunctionPointer functions[NTESTS] = { colorReduce, colorReduce1, colorReduce2, colorReduce3, colorReduce4,
                                         colorReduce5, colorReduce6, colorReduce7, colorReduce8, colorReduce9,
                                         colorReduce10, colorReduce11, colorReduce12, colorReduce13, colorReduce14 };
    // 테스트를 여러 번 반복
    int n = NITERATIONS;
    for (int k = 0; k < n; k++)
    {
        std::cout << k << " of " << n << std::endl;

        // 각 버전을 테스트합니다.
        for (int c = 0; c < NTESTS; c++)
        {
            images[c] = cv::imread("images/boldt.jpg");

            // 타이머 설정 및 함수 호출
            tinit = cv::getTickCount();
            functions[c](images[c], 64);
            t[c] += cv::getTickCount() - tinit;

            std::cout << ".";
        }

        std::cout << std::endl;
    }

    // 각 함수에 대한 간단한 설명
    std::string descriptions[NTESTS] = {
        "original version:",
        "with dereference operator:",
        "using modulo operator:",
        "using a binary mask:",
        "direct ptr arithmetic:",
        "row size recomputation:",
        "continuous image:",
        "reshape continuous image:",
        "with iterators:",
        "Vec3b iterators:",
        "iterators and mask:",
        "iterators from Mat_:",
        "at method:",
        "overloaded operators:",
        "look-up table:",
    };

    // 각 함수의 이미지를 표시
    for (int i = 0; i < NTESTS; i++)
    {
        cv::namedWindow(descriptions[i]);
        cv::imshow(descriptions[i], images[i]);
    }

    // 평균 실행 시간 출력
    std::cout << std::endl
        << "-------------------------------------------" << std::endl
        << std::endl;
    for (int i = 0; i < NTESTS; i++)
    {
        std::cout << i << ". " << descriptions[i] << 1000. * t[i] / cv::getTickFrequency() / n << "ms" << std::endl;
    }

    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}
