#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////////// Color Detection ///////////////////////

int hmin = 0, smin = 111, vmin = 149;
int hmax = 23, smax = 255, vmax = 255;

int main()
{

	string path = "D:/OPEN CV C++/Resources/lambo.png";
	Mat img = imread(path);
	Mat imgHSV, mask;

	cvtColor(img, imgHSV, COLOR_BGR2HSV);	// Convert to HSV- Hue Saturation Value

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179); // Hue range is 0-179
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255); // Saturation range is 0-255
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255); // Value range is 0-255
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);

		waitKey(1);
	}

	


	return 0;
}