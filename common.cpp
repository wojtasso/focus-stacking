#include "common.hpp"

using cv::Mat;

Mat BGR2Gray(Mat input)
{
    Mat tmp(input.rows, input.cols, CV_8UC1);

    if (input.channels() != 3)
        throw std::invalid_argument("Image is not in BGR format");

    for (int y = 0; y < tmp.rows; y++) {
        for (int x = 0; x < tmp.cols; x++) {
            tmp.at<uchar>(y, x) =
                0.114f*input.at<cv::Vec3b>(y, x)[0] +
                0.587f*input.at<cv::Vec3b>(y, x)[1] +
                0.299f*input.at<cv::Vec3b>(y, x)[2];
        }
    }

    return tmp;
}

template<typename inputType, typename outputType>
void convolution(const Mat& input, const Mat& kernel, Mat& output)
{
    for (int y = 0; y < input.rows; y++) {
        for (int x = 0; x < input.cols; x++) {
            for (int j = 0; j < kernel.rows; j++) {
                for (int i = 0; i < kernel.cols; i++) {
                    //Avoid taking elements outside the matrix
                    if (y + j - 1 < 0 || x + i - 1 < 0 ||
                            y + j - 1 >= input.rows || x + i - 1 >= input.cols)
                        continue;

                    output.at<outputType>(y, x) +=
                        input.at<inputType>(y + j - 1, x + i - 1) * kernel.at<float>(j, i);
                }
            }
        }
    }
}

template void convolution<uchar, uchar>(const Mat& input, const Mat& kernel, Mat& output);
template void convolution<uchar, float>(const Mat& input, const Mat& kernel, Mat& output);

void gaussianBlur(const Mat& input, Mat& output)
{
    float gausKernel[9] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
    Mat gaussianKernel = Mat(3, 3, CV_32F, gausKernel) / 16.0f;
    convolution<uchar, uchar>(input, gaussianKernel, output);
}

void calcLaplacian(const Mat& input, Mat& output)
{
    float lapKernel[9] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
    Mat laplacianKernel = Mat(3, 3, CV_32F, lapKernel);
    convolution<uchar, float>(input, laplacianKernel, output);
}

template<typename inOutType>
void absolute(Mat& inOut)
{
    for (int y = 0; y < inOut.rows; y++) {
        for (int x = 0; x < inOut.cols; x++)
                inOut.at<inOutType>(y, x) = abs(inOut.at<inOutType>(y, x));
    }
}

template void absolute<float>(Mat& inOut);

template<typename imgType>
void divideMat(const Mat& input1, const Mat& input2, Mat& output)
{
    if (!(input1.size() == input2.size() && input2.size() == output.size()))
        throw std::invalid_argument("Images have different sizes!");

    for (int y = 0; y < input1.rows; y++) {
        for (int x = 0; x < input1.cols; x++) {
            output.at<imgType>(y, x) =
                input1.at<imgType>(y, x) / input2.at<imgType>(y, x);
        }
    }
}

template void divideMat<float>(const Mat& input1, const Mat& input2, Mat& output);

