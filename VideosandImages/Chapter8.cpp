#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;



///////////////////////////////////// Images /////////////////////////////////////////

int main()
{
	string path = "d:/open cv c++/resources/test.png";
	Mat img = imread(path);

	CascadeClassifier faceCascade;
	faceCascade.load("d:/open cv c++/resources/haarcascade_frontalface_default.xml");

	// Check if it is loaded or not (Optional)
	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

	// Detect faces- we need to store the bounding boxes around the faces
	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
	
	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("image", img);

	waitKey(0);

	return 0;
}