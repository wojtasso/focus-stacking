#ifndef _COMMON_HPP
#define _COMMON_HPP

#include <opencv2/opencv.hpp>

cv::Mat BGR2Gray(cv::Mat input);

template<typename inputType, typename outputType>
void convolution(const cv::Mat& input, const cv::Mat& kernel, cv::Mat& output);

void gaussianBlur(const cv::Mat& input, cv::Mat& output);
void calcLaplacian(const cv::Mat& input, cv::Mat& output);


#endif
