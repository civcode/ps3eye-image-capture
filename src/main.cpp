#include <chrono>
#include <opencv2/opencv.hpp>

#include <iostream>

#include "webcam.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {

    cout << "hello/n";

    Webcam webcam("/dev/video2", 640, 480, 60);

    cv::namedWindow("img", 1);

    auto buffer = webcam.get_buffer();

    cv::Mat out;
    cv::Mat buffer_yuyv(cv::Size(640, 480), CV_8UC2, (char*)buffer.data);

    char* buf = new char[buffer.size];

    auto start = std::chrono::high_resolution_clock::now();
    while (int k = cv::waitKey(10) != 'q') {

        buffer = webcam.get_buffer();
        //webcam.get_buffer();
        //memcpy(buf, buffer.data, buffer.size);
        //cv::Mat buffer_yuyv(cv::Size(640, 480), CV_8UC2, buf);
        //cv::cvtColor(buffer_yuyv, out, cv::COLOR_YUV2GRAY_YUYV);
        cv::cvtColor(buffer_yuyv, out, cv::COLOR_YUV2GRAY_YUYV);
        //cv::cvtColor(buffer_yuyv, out, cv::COLOR_YUV2BGR_YUYV);

        cv::imshow("img", out);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        start = std::chrono::high_resolution_clock::now();
        cout << "dt = " << duration.count() << endl;

    }


    return 0;

}