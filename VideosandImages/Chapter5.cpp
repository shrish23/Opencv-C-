#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////////////////////////// Warp Images /////////////////////////////////////////

float w = 250, h = 350;

int main()
{
	string path = "D:/OPEN CV C++/Resources/cards.jpg";
	Mat img = imread(path);
	Mat matrixk,matrixq,matrixj,imgWarpk,imgWarpq, imgWarpj;
	imshow("Image", img);

	Point2f srck[4] = { {529,143},{769,195}, {405,394}, {672,457} };
	Point2f srcq[4] = { {65,324}, {338,279}, {91,634}, {402,571} };
	Point2f srcj[4] = { {777,108}, {1017,84}, {844,357}, {1114,331} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f}, {0.0f,h}, {w,h} };

	matrixk = getPerspectiveTransform(srck, dst);
	warpPerspective(img, imgWarpk, matrixk, Point(w, h));
	// Create circles at the points
	for (int i = 0; i < 4; i++)
	{
		circle(img, srck[i], 5, Scalar(0, 0, 255), FILLED);
	}


	imshow("Image Warp", imgWarpk);

	//matrixq = getPerspectiveTransform(srcq, dst);
	//warpPerspective(img, imgWarpq, matrixq, Point(w, h));

	//// Create circles at the points
	//for (int i = 0; i < 4; i++)
	//{
	//	circle(img, srcq[i], 5, Scalar(0, 255, 255), FILLED);
	//}


	//imshow("Image Warp", imgWarpq);

	//matrixj = getPerspectiveTransform(srcj, dst);
	//warpPerspective(img, imgWarpj, matrixj, Point(w, h));

	//// Create circles at the points
	//for (int i = 0; i < 4; i++)
	//{
	//	circle(img, srcj[i], 5, Scalar(255, 0, 0), FILLED);
	//}


	//imshow("Image Warp", imgWarpj);

	

	waitKey(0);

	return 0;
}