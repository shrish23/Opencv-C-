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
	Mat imgResize, imgCrop;

	//cout << img.size() << endl;

	resize(img, imgResize, Size(),0.5,0.5);	// Resize image (half the size)

	// Crop image
	Rect roi(200, 110, 300, 300);	// Region of interest
	imgCrop = img(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);

	waitKey(0);

	return 0;
}