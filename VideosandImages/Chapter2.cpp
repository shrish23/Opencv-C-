#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////////////////////////// Basic Functions /////////////////////////////////////////

int main()
{
	string path = "D:/OPEN CV C++/Resources/test.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDial, imgErode;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);	// Convert to grayscale
	GaussianBlur(img, imgBlur, Size(7, 7), 3, 0);	// Blur image
	Canny(imgBlur, imgCanny, 25, 75);	// Edge detection

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // Create kernel (use only odd numbers)
	dilate(imgCanny, imgDial, kernel);	// Dilate image - make edges thicker
	erode(imgDial, imgErode, kernel);	// Erode image - make edges thinner

	imshow("Image", img);
	imshow("Gray Image", imgGray);
	imshow("Blur Image", imgBlur);
	imshow("Canny Image", imgCanny);
	imshow("Dialated Image", imgDial);
	imshow("Eroded Image", imgErode);

	waitKey(0);

	return 0;
}