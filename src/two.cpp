#include <algorithm>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void) {
    cv::Mat img = cv::imread("../data/2.png", -1);
    cv::Mat mask, gray;

    int output[7] = {0};
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierachy;
    float contoursArea;
    std::vector<cv::Point> lines;
    //转化为二值图像
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, mask, 128, 255, cv::THRESH_BINARY_INV);
    // cv::imshow("output", mask);
    // cv::waitKey();
    cv::findContours(mask, contours, hierachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for (std::size_t i = 0; i < contours.size(); i++) {
        contoursArea = cv::contourArea(contours[i]);
        //去除噪声干扰
        if (contoursArea < 3) {
            continue;
        }
        //对边缘进行多边形拟合 得到的是角点的集合
        cv::approxPolyDP(contours[i], lines, 10, true);
        output[lines.size()] = output[lines.size()] + 1;
    }
    for (int i = 3; i <= 6; i++) {
        std::cout << i << "边数量" << output[i] << std::endl;
    }
}