#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////////////////////////// Draw Shapes and Text /////////////////////////////////////////

int main()
{
	//Blank image
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); // 8 bit unsigned integer 3 channel

	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED); // circle(img, center, radius, color, thickness)
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); // rectangle(img, point1(top left), point2(bottom right), color, thickness)
	line(img, Point(130, 296), Point(382, 450), Scalar(255, 255, 255), 2); // line(img, point1, point2, color, thickness)

	putText(img, "OPENCV TEST", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2); // putText(img, text, point, font, scale, color, thickness)

	imshow("Image", img);

	waitKey(0);

	return 0;
}