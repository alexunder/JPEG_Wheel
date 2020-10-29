#include <gtest/gtest.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

using namespace std;

class OpenCV_Mat_Test : public testing::Test
{
protected:
    static void SetUpTestCase()
    {

    }

    static void TearDownTestCase()
    {

    }
};

TEST_F(OpenCV_Mat_Test, Mat_Split)
{
    cv::Mat image = cv::imread("../images/sample_1920_1280.bmp");
    cv::namedWindow("OpenCV Test");
    cv::imshow("Debug", image);

    cout << "image channels=" << image.channels() << endl;

    cv::Mat rgbChannels[3];
    cv::split(image, rgbChannels);

    cv::imshow("Red",   rgbChannels[0]);
    cv::imshow("Green", rgbChannels[1]);
    cv::imshow("Blue",  rgbChannels[2]);

    int k = cv::waitKey(0);
}
