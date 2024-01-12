#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



///////////////////////////////////// Images /////////////////////////////////////////

Mat imgOriginal, imgGray, imgCanny, imgBlur, imgThre, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;
float w = 420, h = 596;

Mat preProcessing(Mat img)
{
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgCanny, kernel);

	return imgCanny;
}

vector<Point> getContours(Mat imgDial)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDial, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 1);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());

	vector<Point> biggest;
	int maxArea{0};

	// Filter contours by area
	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		cout << area << endl;


		if (area > 1000) {
			double peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
				biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}

			
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {
	for (int i = 0; i < points.size(); i++) {
		circle(imgOriginal, points[i], 10, color, FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 2);
	}
}

vector<Point> reorder(vector<Point> points) {
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {
	Point2f src[4] = { points[0],points[1],points[2],points[3]};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;

}

int main()
{
	string path = "D:/OPEN CV C++/Resources/paper.jpg";
	imgOriginal = imread(path);
	//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

	//Preprocessing
	imgThre = preProcessing(imgOriginal);
	//Get Contours - Biggest
	initialPoints = getContours(imgThre);
	docPoints = reorder(initialPoints);
	//drawPoints(docPoints, Scalar(0, 255, 0));

	// Wrap Perspective
	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	Rect roi(5, 5, w - 10, h - 10); // cropping image
	imgCrop = imgWarp(roi);


	imshow("Image", imgOriginal);
	imshow("Image Dilated", imgThre);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);

	waitKey(0);

	return 0;
}