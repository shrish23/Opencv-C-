#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	string image_path = "C:/Users/Shrish/Pictures/Saved Pictures/wallpaperflare.com_wallpaper.jpg";

	Mat image = imread(image_path, IMREAD_COLOR);
	resize(image, image, Size(500, 500));

	imshow("Image", image);
	waitKey(0);
	return 0;
}