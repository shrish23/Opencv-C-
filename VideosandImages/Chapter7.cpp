#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



///////////////////////////////////// Images /////////////////////////////////////////
Mat imgGray, imgBlur, imgCanny, imgDial;


void getContours(Mat imgDial, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	findContours(imgDial, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 1);

	// Filter contours by area
	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		cout << area << endl;
		string objType;
		
		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		if (area > 1000) {
			double peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			
			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objType = "Triangle"; }
			if (objCor == 4) { 
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objType = "Square"; }
				else { objType = "Rectangle"; }
			}
			if (objCor > 4) { objType = "Circle"; }

			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			putText(img, objType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
		}
	}
}

int main()
{
	string path = "D:/OPEN CV C++/Resources/shapes.png";
	Mat img = imread(path);

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	dilate(imgCanny, imgDial, getStructuringElement(MORPH_RECT, Size(3, 3)));

	getContours(imgDial, img);

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dialation", imgDial);*/
	//imshow("Image Contours", imgCon);

	waitKey(0);

	return 0;
}