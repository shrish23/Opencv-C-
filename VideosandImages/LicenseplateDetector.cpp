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
	VideoCapture cap(1);
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("d:/open cv c++/resources/haarcascade_russian_plate_number.xml");

	// Check if it is loaded or not (Optional)
	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	// Detect faces- we need to store the bounding boxes around the faces
	vector<Rect> plates;

	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("d:/open cv c++/resources/Plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("image", img);

		waitKey(1);
	}

	return 0;
}