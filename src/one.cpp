#include <algorithm>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

int main(void) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> line;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<int> length;
    cv::Point start, end;
    float k, b;
    //读取图像并转化为HSV色彩空间
    cv::Mat img = cv::imread("../data/1.png");
    cv::Mat img_hsv;
    cv::Mat mask;

    float middle, x_start, x_end;
    cv::Vec4f output;
    cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
    //转化为二值图像
    //转换的过程可以使用滑动条 很方便

    cv::inRange(img_hsv, cv::Scalar(0, 0, 137), cv::Scalar(120, 255, 255), mask);
    // cv::imshow("mask",mask);
    // cv::waitKey();
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    //找到的轮廓会有很多 这里直接选择最大的轮廓作为目标轮廓
    for (int i = 0; i < contours.size(); i++) {
        length.push_back(contours[i].size());
    }
    int maxPosition = max_element(length.begin(), length.end()) - length.begin();
    // cv::RotatedRect rRect = cv::minAreaRect(contours[maxPosition]);
    // cv::Point2f vertices[4];
    //         //获得倾斜矩形的边缘四点
    // rRect.points(vertices);
    // if(rRect.size.width > rRect.size.height){
    //     start = (vertices[1] + vertices[0]) / 2;
    //     end = (vertices[2] + vertices[3]) / 2;
    // }
    // else{
    //     end = (vertices[3] + vertices[0]) / 2;
    //     start = (vertices[1] + vertices[2]) / 2;
    // }
    //直接寻找中线上的各点
    for (int i = 0; i < img.rows; i++) {
        int count = 0;
        int sum = 0;
        for (int j = 0; j < contours[maxPosition].size(); j++) {
            if (contours[maxPosition][j].y == i) {
                sum += contours[1][j].x;
                count += 1;
            }
        }
        middle = sum / count;
        line.push_back(cv::Point(middle, i));
    }
    //直线拟合 得到斜率和解距
    cv::fitLine(line, output, cv::DIST_L2, 0, 0.01, 0.01);
    k = output[1] / output[0];
    b = output[3] - k * output[2];
    x_start = -b / k;
    x_end = (img.rows - 1 - b) / k;
    cv::line(img, cv::Point(int(x_start), 0), cv::Point(int(x_end), img.rows - 1), cv::Scalar(255, 0, 0), 4);
    cv::imshow("output", img);
    cv::waitKey();
}