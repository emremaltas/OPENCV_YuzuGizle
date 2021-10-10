#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//Biyomedikal Mühendisi EMRE MALTAS 24.09.2021

class proje {
public:
	string wName = "Pencere1";
	string wName2 = "Pencere2";
	vector<Rect>tespit;
	int m, y, k;
	vector<int>Mavi;
	vector<int>Kirmizi;
	vector<int>Yesil;
	RNG& deger = theRNG();
	RNG& deger2 = theRNG();
	CascadeClassifier yuzum;
	Mat frame, griFrame;
	proje()
	{
		cout << "XML dosyasi yukleniyor" << endl;
		yuzum.load("cascade.xml");
	}
	void kameraAc();

}YuzunRenkOrt;

void proje::kameraAc()
{
	VideoCapture vCap;
	vCap.open(0);

	if (vCap.isOpened())
	{
		cout << "Kamera aciliyor..." << endl;
		namedWindow(wName, WINDOW_AUTOSIZE);

		while (true)
		{
			vCap.read(frame);

			cvtColor(frame, griFrame, COLOR_BGR2GRAY);
			yuzum.detectMultiScale(griFrame, tespit, 1.1, 3, 0, Size(20, 20), Size(150, 150));

			if (tespit.size() >= 1)
			{
				cout << "Yuz Tespit Edildi" << endl;
				rectangle(frame, tespit[0], Scalar(0, 0, 255), 2, 8);

				for (int i = tespit[0].y; i <= tespit[0].y + tespit[0].height; i++)
				{
					for (int j = tespit[0].x; j <= tespit[0].x + tespit[0].width; j++)
					{
						m = frame.at<Vec3b>(i, j)[0];
						y = frame.at<Vec3b>(i, j)[1];
						k = frame.at<Vec3b>(i, j)[2];
						if ((m - 90) >= 0 && (m + 90) <= 255)
						{
							frame.at<Vec3b>(i, j)[0] = deger.uniform(m - 90, m + 90);
						}
						else
						{
							frame.at<Vec3b>(i, j)[0] = deger2.uniform(0, 255);
						}
						if ((y - 90) >= 0 && (y + 90) <= 255)
						{
							frame.at<Vec3b>(i, j)[1] = deger.uniform(y - 90, y + 90);
						}
						else
						{
							frame.at<Vec3b>(i, j)[1] = deger2.uniform(125, 230);
						}
						if ((k - 90) >= 0 && (k + 90) <= 255)
						{
							frame.at<Vec3b>(i, j)[2] = deger.uniform(k - 90, k + 90);
						}
						else
						{
							frame.at<Vec3b>(i, j)[2] = deger2.uniform(0, 255);
						}
					}
				}
				imshow(wName, frame);
			}
			else
			{
				cout << "Yuz tespit edilemedi" << endl;
				destroyWindow(wName);
			}
			if (waitKey(100) == 27)break;
		}
	}
}
int main()
{
	YuzunRenkOrt.kameraAc();
}

