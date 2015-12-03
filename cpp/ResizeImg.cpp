#include <string>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


void image_resize(string& room_name, int position_number,  int vertical_angle, int img_number, int percent)
{
	//string path_src = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "_choosen\\";
	//string path_dst = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "_choosen\\small\\";

	string path_src = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\stitch\\" + to_string(vertical_angle) + "_final\\stitch";
	string path_dst = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\stitch\\" + to_string(vertical_angle) + "_final\\small\\stitch";

	Mat img, result;

	img = imread(path_src + to_string(img_number) + ".jpg");

	if (img.data)
	{
		resize(img, result, Size(int(img.cols*percent / 100), int(img.rows*percent / 100)));

		imwrite(path_dst + to_string(img_number) + ".jpg", result);

		cout << path_dst + to_string(img_number) + ".jpg" << endl;
	}
	else
	{
		cout << "NO img" << img_number << "."<<endl;
	}
	
}

void resize_all(string& room_name, int position_number,int vertical_angle, int percent)
{
	string path_src = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "_choosen\\";
	Mat img;

	for (int i = 0; i < 800; i++)
	{
		img = imread(path_src + to_string(i) + ".jpg");

		if (img.data)
			image_resize(room_name, position_number, vertical_angle, i, percent);
		else
			break;
	}
}