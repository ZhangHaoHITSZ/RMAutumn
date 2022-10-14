#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define WINDOW_NAME "bgr2hsv"

int h_min;
int s_min;
int v_min;
int h_max;
int s_max;
int v_max;

cv::Mat img;
cv::Mat img_hsv;
cv::Mat mask;

void on_Trackbar(int, void*) {
    cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
    cv::inRange(img_hsv, cv::Scalar(h_min, s_min, v_min), cv::Scalar(h_max, s_max, v_max), mask);

    cv::imshow("WINDOW_NAME", mask);
    cv::imshow("img", img);
}

int main(int argc, char** argv) {
    img = cv::imread("../data/1.png");

    cv::namedWindow(WINDOW_NAME, 1);

    cv::createTrackbar("h_min", WINDOW_NAME, &h_min, 180, on_Trackbar);
    cv::createTrackbar("s_min", WINDOW_NAME, &s_min, 255, on_Trackbar);
    cv::createTrackbar("v_min", WINDOW_NAME, &v_min, 255, on_Trackbar);
    cv::createTrackbar("h_max", WINDOW_NAME, &h_max, 180, on_Trackbar);
    cv::createTrackbar("s_max", WINDOW_NAME, &s_max, 255, on_Trackbar);
    cv::createTrackbar("v_max", WINDOW_NAME, &v_max, 255, on_Trackbar);

    cv::waitKey(0);

    return 0;
}
