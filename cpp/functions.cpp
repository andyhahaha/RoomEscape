#include <string>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


void image_resize(string& room_name, int position_number,  int vertical_angle, int img_number, int percent)
{
	string path_src = "D:\\image\\image_use\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "\\";
	string path_dst = "D:\\image\\image_use\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "\\small\\";

	//string path_src = "D:\\image\\image_use\\" + room_name + "\\position" + to_string(position_number) + "\\stitch\\stitch";
	//string path_dst = "D:\\image\\image_use\\" + room_name + "\\position" + to_string(position_number) + "\\stitch_small\\stitch";

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
		cout << "NO img" << img_number << ".";
	}
	
}

void resize_all(string& room_name, int position_number,int vertical_angle, int percent)
{
	string path_src = "D:\\image\\image_use\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "\\";
	Mat img;

	for (int i = 0; i < 500; i++)
	{
		img = imread(path_src + to_string(i) + ".jpg");

		if (img.data)
			image_resize(room_name, position_number, vertical_angle, i, percent);
		else
			break;
	}
}