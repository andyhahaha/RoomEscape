#include "../h/PositionImgSetting.h"
#include "../h/PyramidBlending.h"
#include "../h/ChooseImageSSIM.h"
#include "../h/Define.h"
#include "../h/ssim.h"

#include <opencv2/contrib/contrib.hpp>	//要用timer就需要
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <windows.h>
#include <opencv2/legacy/legacy.hpp>
#include <tchar.h> 

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int img_amount_top, img_amount_mid, img_amount_bot, img_amount;
int interval, central_img, left_img, right_img;
Mat img_mid, img_l, img_r;
TickMeter  t;

PositionImgSetting::PositionImgSetting() {
	_room_name = "noname";
	_number = 1;
}

PositionImgSetting::PositionImgSetting(string& room_name, int number) {
	_room_name = room_name;
	_number = number;
}

void PositionImgSetting::set_room_name(int room_name) {
	_room_name = room_name;
}

string& PositionImgSetting::get_room_name() {
	return _room_name;
}

void PositionImgSetting::set_number(int number) {
	_number = number;
}

int PositionImgSetting::get_number() {
	return _number;
}

Mat PositionImgSetting::get_image(int img_number) {
	Mat img = imread("D:\\Repo\\image\\" + _room_name + "\\position" + to_string(_number) + "\\img" + to_string(img_number) + ".jpg");

	return img;
}

vector< DMatch > PositionImgSetting::get_good_dist_matches(vector< DMatch > matches, int method){
	double max_dist = 0;
	double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	//printf("-- Max dist : %f \n", max_dist);
	//printf("-- Min dist : %f \n", min_dist);

	//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
	vector< DMatch > good_matches;

	for (int i = 0; i < matches.size(); i++)
	{
		if (method == METHOD1 || method == METHOD3)
		{
			if (matches[i].distance < 6 * min_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}
		else
		{
			if (matches[i].distance < 7 * min_dist)
			{
				good_matches.push_back(matches[i]);
			}
		}
	}
	return good_matches;
}

vector< DMatch > PositionImgSetting::get_correct_range_matches(vector <DMatch>  matches, Image img1, Image img2, int direction){
	//look if the match is inside a defined area of the image
	double tresholdDist_x = 0.6*img2.mat().cols;
	double tresholdDist_y = 0.6*img2.mat().rows;

	vector< DMatch > good_matches;
	good_matches.reserve(matches.size());

	for (int i = 0; i < matches.size(); i++)
	{
		//calculate local distance for each possible match
		vector < KeyPoint > keypoints1 = img1.keypoints();
		vector < KeyPoint > keypoints2 = img2.keypoints();

		Point2f point1 = keypoints1[matches[i].queryIdx].pt;
		Point2f point2 = keypoints2[matches[i].trainIdx].pt;

		if (direction == STITCH2_LEFT)
		{
			//if (point2.x > img2.mat().cols - tresholdDist_x)	// img2.x > 0.4 * img2 width
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_RIGHT)
		{
			//if (point1.x>STITCH_SCREEN_WIDTH/3 && point2.x <tresholdDist_x)	//img1.x > (1/3)*img1 width, img2.x < 0.6 * img2 width
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_UP)
		{
			//if (point1.x>STITCH_SCREEN_WIDTH / 12 && point2.y > img2.mat().rows - tresholdDist_y)	//img1.x > (1/12)*img1 width, img2.y > 0.4 * img2 height
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_DOWN)
		{
			//if (point1.y>STITCH_SCREEN_HEIGHT*5 / 12 && point2.y < tresholdDist_y)		// img1.y > (5/12)*img1 height, img2.y < 0.6 * img2 height
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_LEFT_UP)
		{
			//if (point2.x > 0.2*img2.mat().cols && point2.y > 0.2*img2.mat().rows)
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_LEFT_DOWN)
		{
			//if (point1.y>STITCH_SCREEN_HEIGHT * 5 / 12/*point2.x > img2.mat().cols - tresholdDist_x && point2.y < tresholdDist_y*/)
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_RIGHT_UP)
		{
			//if (point1.x>(STITCH_SCREEN_WIDTH / 3)/*&& to.x >img2.mat().rows - tresholdDist_x */)	//img1.x > (1/3)*img1 width
				good_matches.push_back(matches[i]);
		}
		else if (direction == STITCH2_RIGHT_DOWN)
		{
			//if (point1.x>STITCH_SCREEN_WIDTH / 3 && point1.y>STITCH_SCREEN_HEIGHT*5 / 12/* && to.x <tresholdDist_x && to.y < tresholdDist_y*/)	//img1.x > (1/3)*img1 width
				good_matches.push_back(matches[i]);
		}
	}
	return good_matches;
}

vector< DMatch > PositionImgSetting::get_correct_range_matches_vertical(vector <DMatch>  matches, Image img1, Image img2, int direction){
	//look if the match is inside a defined area of the image
	double tresholdDist = 0.6*img2.mat().rows;

	vector< DMatch > good_matches;
	good_matches.reserve(matches.size());

	for (int i = 0; i < matches.size(); i++)
	{
		//calculate local distance for each possible match
		vector < KeyPoint > keypoints1 = img1.keypoints();
		vector < KeyPoint > keypoints2 = img2.keypoints();

		Point2f from = keypoints1[matches[i].queryIdx].pt;
		Point2f to = keypoints2[matches[i].trainIdx].pt;

		if (direction == STITCH2_UP)
		{
			if (from.y > (img1.mat().rows - tresholdDist) && to.y < tresholdDist)
			{
				good_matches.push_back(matches[i]);
			}
		}
		else
		{
			if (from.y < tresholdDist && to.y >(img2.mat().rows - tresholdDist))
			{
				good_matches.push_back(matches[i]);
			}
		}
	}
	return good_matches;
}

void PositionImgSetting::symmetryTest(const vector<DMatch> matches1, const vector<DMatch> matches2, vector<DMatch> &symMatches)
{
	//matches1是img1->img2，matches2是img2->img1
	symMatches.clear();
	for (vector<DMatch>::const_iterator matchIterator1 = matches1.begin(); matchIterator1 != matches1.end(); ++matchIterator1)
	{
		for (vector<DMatch>::const_iterator matchIterator2 = matches2.begin(); matchIterator2 != matches2.end(); ++matchIterator2)
		{
			if ((*matchIterator1).queryIdx == (*matchIterator2).trainIdx && (*matchIterator2).queryIdx == (*matchIterator1).trainIdx)
			{
				symMatches.push_back(DMatch((*matchIterator1).queryIdx, (*matchIterator1).trainIdx, (*matchIterator1).distance));
				break;
			}
		}
	}
}

void PositionImgSetting::draw_matches(Mat img1, Mat img2, vector< KeyPoint > keypoints1, vector< KeyPoint > keypoints2, vector< DMatch > matches, int number){
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2,
		matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imwrite("D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\Good Matches\\good_match" + to_string(number) + ".jpg", img_matches);
}

void PositionImgSetting::draw_2img_matches(Mat img_1, Mat img_2, int number){
	Image img1(img_1), img2(img_2);
	
	FlannBasedMatcher matcher;
	vector<DMatch>matches1, matches1_1, matches2_1;
	matcher.match(img1.descriptors(), img2.descriptors(), matches1);
	matcher.match(img2.descriptors(), img1.descriptors(), matches1_1);
	draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), matches1, 11);

	//look for symmetry matches
	vector< DMatch > symm_matches1;
	symmetryTest(matches1, matches1_1, symm_matches1);
	draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), symm_matches1, 12);
	cout << "symmetryTest OK" << endl;

	//-- Use only "good" matches (i.e. whose distance is less than 6*min_dist )
	vector< DMatch > good_dist_matches1;
	good_dist_matches1 = get_good_dist_matches(symm_matches1, METHOD2);
	draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), good_dist_matches1, 13);
	cout << "GoodDistTest OK" << endl;

	//look if the match is inside a defined area of the image
	double tresholdDist_x = 0.55*img2.mat().cols;
	double tresholdDist_y = 0.55*img2.mat().rows;

	//vector< DMatch > good_matches;
	vector< DMatch > best_matches1;
	best_matches1.reserve(good_dist_matches1.size());

	for (int i = 0; i < good_dist_matches1.size(); i++)
	{
		//calculate local distance for each possible match
		vector < KeyPoint > keypoints1 = img1.keypoints();
		vector < KeyPoint > keypoints2 = img2.keypoints();

		Point2f from = keypoints2[good_dist_matches1[i].trainIdx].pt;
		Point2f to = keypoints1[good_dist_matches1[i].queryIdx].pt;

		if (from.x < tresholdDist_x && to.x > img2.mat().cols - tresholdDist_x)
		{
			best_matches1.push_back(good_dist_matches1[i]);
		}
	}
	cout << "GoodRangeTest OK" << endl;
	
	Mat img_matches;
	drawMatches(img1.mat(), img1.keypoints(), img2.mat(), img2.keypoints(),
		best_matches1, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imwrite("D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\Good Matches\\good_match" + to_string(number) + ".jpg", img_matches);
	cout<<"D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\Good Matches\\good_match" + to_string(number) + ".jpg"<<endl;
}

void PositionImgSetting::get_homography_matrix(Image img1, Image img2, vector< DMatch > matches1, Mat& H1){
	vector< Point2f > img_good1, img_good2;		//img1是不變的(central)，img2要貼到img1上

	for (size_t i = 0; i < matches1.size(); i++)
	{
		//-- Get the keypoints from the good matches
		vector < KeyPoint > keypoints1 = img1.keypoints();
		vector < KeyPoint > keypoints2 = img2.keypoints();
		img_good1.push_back(keypoints1[matches1[i].queryIdx].pt);
		img_good2.push_back(keypoints2[matches1[i].trainIdx].pt);
	}

	// Find the Homography Matrix
	H1 = findHomography(img_good2, img_good1, CV_RANSAC);
}

Mat PositionImgSetting::get_blending_matrix(Mat left, Mat right, Mat mask){
	//做pyramid blending讓光線柔和
	Mat_<Vec3f> l, r;
	left.convertTo(l, CV_32F, 1.0 / 255.0);//Vec3f表示有三通道，即 l[row][column][depth]
	right.convertTo(r, CV_32F, 1.0 / 255.0);//Vec3f表示有三通道，即 l[row][column][depth]

	Mat_<Vec3f> blend;
	Mat blend_mat;

	blend = LaplacianBlend(l, r, mask);

	blend.convertTo(blend_mat, CV_8UC3, 255);
	cout << "blend success" << endl;
	return blend_mat;
}

Mat PositionImgSetting::get_stitch_matrix(Mat img1, Mat img2, int direction, Mat H1, vector<int> &fill){
	// Use the Homography Matrix to warp the images
	Mat left, right,result;
	Mat mask(STITCH_SCREEN_HEIGHT, STITCH_SCREEN_WIDTH, CV_8U, Scalar(0));
	Mat point1(3, 1, CV_64F), point2(3, 1, CV_64F), point3(3, 1, CV_64F), point4(3, 1, CV_64F);

	point1.at<double>(0, 0) = 0.0;		//img2 左上角
	point1.at<double>(1, 0) = 0.0;
	point1.at<double>(2, 0) = 1.0;

	point2.at<double>(0, 0) = img2.cols;	//img2右上角
	point2.at<double>(1, 0) = 0.0;
	point2.at<double>(2, 0) = 1.0;

	point3.at<double>(0, 0) = img2.cols;	//img2左下角
	point3.at<double>(1, 0) = img2.rows;
	point3.at<double>(2, 0) = 1.0;

	point4.at<double>(0, 0) = 0.0;			//img2右下角
	point4.at<double>(1, 0) = img2.rows;
	point4.at<double>(2, 0) = 1.0;

	Mat point1_1 = H1*point1;
	Mat point2_1 = H1*point2;
	Mat point3_1 = H1*point3;
	Mat point4_1 = H1*point4;

	int x1 = (int)round(point1_1.at<double>(0, 0) / point1_1.at<double>(2, 0));
	int x2 = (int)round(point2_1.at<double>(0, 0) / point2_1.at<double>(2, 0));
	int x3 = (int)round(point3_1.at<double>(0, 0) / point3_1.at<double>(2, 0));
	int x4 = (int)round(point4_1.at<double>(0, 0) / point4_1.at<double>(2, 0));
	int y1 = (int)round(point1_1.at<double>(1, 0) / point1_1.at<double>(2, 0));
	int y2 = (int)round(point2_1.at<double>(1, 0) / point2_1.at<double>(2, 0));
	int y3 = (int)round(point3_1.at<double>(1, 0) / point3_1.at<double>(2, 0));
	int y4 = (int)round(point4_1.at<double>(1, 0) / point4_1.at<double>(2, 0));

	//cout << "x1=" << x1 << endl << "x2=" << x2 << endl << "x3=" << x3 << endl << "x4=" << x4 << endl;
	/** Create some points */
	Point rook_points[1][4];
	int lineType = 8;
	int npt[] = { 4 };


	if (direction == STITCH2_LEFT)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		mask(Range::all(), Range(0, x2-300)) = 1.0;

		/*rook_points[0][0] = Point(x1-50, y1-50);
		rook_points[0][1] = Point(x2-300, y2-50);
		rook_points[0][2] = Point(x3-300, y3+50);
		rook_points[0][3] = Point(x4-50, y4+50);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);*/

		if (x1 < 0 && x4 < 0) fill[0] = 1;
		cout <<"fill[0] = "<< fill[0] << endl;
		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_RIGHT)
	{
		warpPerspective(img2, right, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		mask(Range::all(), Range(0, x1 + 300)) = 1.0;

		if (x2 > STITCH_SCREEN_WIDTH && x3 >STITCH_SCREEN_WIDTH) fill[1] = 1;
		cout << "fill[1] = " << fill[1] << endl;

		result = get_blending_matrix(img1,right, mask);
	}
	else if (direction == STITCH2_UP)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1 + 20, y1-10);
		rook_points[0][1] = Point(x2 - 20, y2-10);
		rook_points[0][2] = Point(x3 - 60, y3 - 200);
		rook_points[0][3] = Point(x4 + 60, y4 - 200);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_DOWN)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1 + 60, y1 + 200);
		rook_points[0][1] = Point(x2 - 60, y2 + 200);
		rook_points[0][2] = Point(x3 - 20, y3);
		rook_points[0][3] = Point(x4 + 20, y4);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_LEFT_UP)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1, y1);
		rook_points[0][1] = Point(x2 - 200, y2);
		rook_points[0][2] = Point(x3 - 200, y3 - 200);
		rook_points[0][3] = Point(x4 + 10, y4 - 200);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		if (x1 < 0 && x4 <0) fill[2] = 1;
		cout << "fill[2] = " << fill[2] << endl;

		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_RIGHT_UP)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1 + 200, y1);
		rook_points[0][1] = Point(x2, y2);
		rook_points[0][2] = Point(x3 - 10, y3 - 200);
		rook_points[0][3] = Point(x4 + 200, y4 - 200);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		if (x2 > STITCH_SCREEN_WIDTH && x3 >STITCH_SCREEN_WIDTH) fill[3] = 1;
		cout << "fill[3] = " << fill[3] << endl;

		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_LEFT_DOWN)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1 + 10, y1 + 200);
		rook_points[0][1] = Point(x2 - 200, y2 + 200);
		rook_points[0][2] = Point(x3 - 200, y3);
		rook_points[0][3] = Point(x4, y4);

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		if (x1 < 0 && x4 <0) fill[4] = 1;
		cout << "fill[4] = " << fill[4] << endl;

		result = get_blending_matrix(left, img1, mask);
	}
	else if (direction == STITCH2_RIGHT_DOWN)
	{
		warpPerspective(img2, left, H1, Size(STITCH_SCREEN_WIDTH, STITCH_SCREEN_HEIGHT));
		rook_points[0][0] = Point(x1 + 200, y1 + 200);
		rook_points[0][1] = Point(x2 - 10, y2 + 200);
		rook_points[0][2] = Point(x3 - 10, y3);
		rook_points[0][3] = Point(x4 + 200, y4 );

		const Point* ppt[1] = { rook_points[0] };
		fillPoly(mask, ppt, npt, 1, Scalar(1), lineType);

		if (x2 > STITCH_SCREEN_WIDTH && x3 >STITCH_SCREEN_WIDTH) fill[5] = 1;
		cout << "fill[5] = " << fill[5] << endl;

		result = get_blending_matrix(left, img1, mask);
	}

	//imshow("get_stitch_matrix", result2);
	return result;
}

//img2會貼到img1
Mat PositionImgSetting::stitch2(Mat img_1, Mat img_2, int method, int direction, vector<int> &fill){
	assert(img_1.rows>0 && img_2.rows>0);
	Rect rect1, rect2;
	Mat roiImage1, roiImage2;
	Image img1, img2;
	vector<KeyPoint> img1_keypoints, img2_keypoints;
	
	if (direction == STITCH2_LEFT)	//img1.x<(2/3)*img1 wdith, img2.x>0.3*img2 width
	{
		rect1=Rect(0, 0, int(STITCH_SCREEN_WIDTH*2/3), STITCH_SCREEN_HEIGHT);
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		Rect rect2(int(STITCH_IMG_WIDTH * 0.3), 0, int(STITCH_IMG_WIDTH * 0.7), STITCH_IMG_HEIGHT);
		img_2(rect2).copyTo(roiImage2);
		img2.set_image(roiImage2);

		img2_keypoints = img2.keypoints();
		for (int i = 0; i < img2.keypoints().size(); i++)
			img2_keypoints[i].pt.x += int(STITCH_IMG_WIDTH * 0.3);

		img2.set_keypoints(img2_keypoints);
	}
	else if (direction == STITCH2_RIGHT)	//img1.x > (1/3)*img1 width, img2.x < 0.7 * img2 width
	{
		rect1 = Rect(int(STITCH_SCREEN_WIDTH * 1 / 3), 0, int(STITCH_SCREEN_WIDTH * 2 / 3), STITCH_SCREEN_HEIGHT);
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
			img1_keypoints[i].pt.x += int(STITCH_SCREEN_WIDTH * 1 / 3);

		img1.set_keypoints(img1_keypoints);

		rect2 = Rect(0, 0, int(STITCH_IMG_WIDTH * 0.7), STITCH_IMG_HEIGHT);
		img_2(rect2).copyTo(roiImage2);
		img2.set_image(roiImage2);
	}
	else if (direction == STITCH2_UP)	//(1/6)*img1 width<img1.x < (5/6)*img1 width, img1.y < (7/12)*img1 height, img2.y > 0.4 * img2 height
	{
		rect1 = Rect(int(STITCH_SCREEN_WIDTH * 1 / 6), 0, int(STITCH_SCREEN_WIDTH * 4 / 6), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
			img1_keypoints[i].pt.x += int(STITCH_SCREEN_WIDTH * 1 / 6);

		img1.set_keypoints(img1_keypoints);

		rect2 = Rect(0, int(STITCH_IMG_HEIGHT*0.4), STITCH_IMG_WIDTH, int(STITCH_IMG_HEIGHT*0.6));
		img_2(rect2).copyTo(roiImage2);
		img2.set_image(roiImage2);

		img2_keypoints = img2.keypoints();
		for (int i = 0; i < img2.keypoints().size(); i++)
			img2_keypoints[i].pt.y += int(STITCH_IMG_HEIGHT*0.4);

		img2.set_keypoints(img2_keypoints);
	}
	else if (direction == STITCH2_DOWN)	// img1.y > (5/12)*img1 height, img2.y < 0.6 * img2 height
	{
		rect1 = Rect(int(STITCH_SCREEN_WIDTH * 1 / 6), int(STITCH_SCREEN_HEIGHT * 5 / 12), int(STITCH_SCREEN_WIDTH * 4 / 6), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
		{
			img1_keypoints[i].pt.x += int(STITCH_SCREEN_WIDTH / 6);
			img1_keypoints[i].pt.y += int(STITCH_SCREEN_HEIGHT * 5 / 12);
		}
		img1.set_keypoints(img1_keypoints);

		rect2 = Rect(0, 0, STITCH_IMG_WIDTH, int(STITCH_IMG_HEIGHT*0.6));
		img_2(rect2).copyTo(roiImage2);
		img2.set_image(roiImage2);
	}
	else if (direction == STITCH2_LEFT_UP)	//img1.x<(2/3)*img1 width, img1.y<(7/12)*img1 height
	{
		rect1 = Rect(0, 0, int(STITCH_SCREEN_WIDTH * 2 / 3), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);
		img2.set_image(img_2);
	}
	else if (direction == STITCH2_LEFT_DOWN)	//img1.x<(2/3)*img1 width, img1.y > (5/12)*img1 height
	{
		rect1 = Rect(0, int(STITCH_SCREEN_HEIGHT * 5 / 12), int(STITCH_SCREEN_WIDTH * 2 / 3), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);
		
		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
			img1_keypoints[i].pt.y += int(STITCH_SCREEN_HEIGHT * 5 / 12);

		img1.set_keypoints(img1_keypoints);
		img2.set_image(img_2);
	}
	else if (direction == STITCH2_RIGHT_UP)	//img1.x > (1/3)*img1 width, img1.y<(7/12)*img1 height
	{
		rect1 = Rect(int(STITCH_SCREEN_WIDTH * 1 / 3), 0, int(STITCH_SCREEN_WIDTH * 2 / 3), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
			img1_keypoints[i].pt.x += int(STITCH_SCREEN_WIDTH * 1 / 3);

		img1.set_keypoints(img1_keypoints);
		img2.set_image(img_2);
	}
	else if (direction == STITCH2_RIGHT_DOWN)	//	//img1.x > (1/3)*img1 width, img1.y > (5/12)*img1 height
	{
		rect1 = Rect(int(STITCH_SCREEN_WIDTH * 1 / 3), int(STITCH_SCREEN_HEIGHT * 5 / 12), int(STITCH_SCREEN_WIDTH * 2 / 3), int(STITCH_SCREEN_HEIGHT * 7 / 12));
		img_1(rect1).copyTo(roiImage1);
		img1.set_image(roiImage1);

		img1_keypoints = img1.keypoints();
		for (int i = 0; i < img1.keypoints().size(); i++)
		{
			img1_keypoints[i].pt.x += int(STITCH_SCREEN_WIDTH / 3);
			img1_keypoints[i].pt.y += int(STITCH_SCREEN_HEIGHT * 5 / 12);
		}
		img1.set_keypoints(img1_keypoints);
		img2.set_image(img_2);
	}

	FlannBasedMatcher matcher;
	vector<DMatch>matches1,matches1_1, matches2_1;
	/*if (img1.descriptors().type() != CV_32F) {
		//img1.descriptors().convertTo(img1.descriptors(), CV_32F);
		cout << "haha1" << endl;
	}
	if (img2.descriptors().type() != CV_32F) {
		//img2.descriptors().convertTo(img2.descriptors(), CV_32F);
		cout << "haha2" << endl;
	}*/
	matcher.match(img1.descriptors(), img2.descriptors(), matches1);
	matcher.match(img2.descriptors(), img1.descriptors(), matches1_1);
	draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), matches1, 1);
	draw_matches(img1.mat(), img2.mat(), img1.keypoints(), img2.keypoints(), matches1, 2);

	vector<DMatch>good_matches1;

	if (method == METHOD1 || method == METHOD2)
	{
		//look for symmetry matches
		vector< DMatch > sym_matches1;

		symmetryTest(matches1, matches1_1, sym_matches1);
		draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), sym_matches1, 3);
		draw_matches(img1.mat(), img2.mat(), img1.keypoints(), img2.keypoints(), sym_matches1, 4);

		//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
		good_matches1 = get_good_dist_matches(sym_matches1, method);
		draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), good_matches1, 5);
		draw_matches(img1.mat(), img2.mat(), img1.keypoints(), img2.keypoints(), good_matches1, 6);
	}
	else
	{
		//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
		good_matches1 = get_good_dist_matches(matches1, METHOD3);
		draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), good_matches1, 7);
		draw_matches(img1.mat(), img2.mat(), img1.keypoints(), img2.keypoints(), good_matches1, 8);
	}

	//找接近圖片重疊範圍的match(最兩邊的不要)
	//vector<DMatch>best_matches1;
	//best_matches1 = get_correct_range_matches(good_matches1, img1, img2, direction);
	//draw_matches(img_1, img_2, img1.keypoints(), img2.keypoints(), best_matches1, 5);

	// Find the Homography Matrix from best matches
	Mat H1;
	get_homography_matrix(img1, img2,  good_matches1, H1);
	//cout << H1 << endl;

	// Use the Homography Matrix to warp the images
	Mat stitch2_result;
	stitch2_result = get_stitch_matrix(img_1, img_2,  direction, H1, fill);

	cout << "stitch2 success" << endl<<"----------------------------"<<endl;
	//imshow("stitch3_result",stitch3_result);
	return stitch2_result;
}


/*Mat PositionImgSetting::stitch3(Image img1, Image img2, Image img3, int method, int direction){

	FlannBasedMatcher matcher;
	vector<DMatch>matches1, matches2, matches1_1, matches2_1;
	matcher.match(img1.descriptors(), img2.descriptors(), matches1);
	matcher.match(img2.descriptors(), img3.descriptors(), matches2);
	matcher.match(img2.descriptors(), img1.descriptors(), matches1_1);
	matcher.match(img3.descriptors(), img2.descriptors(), matches2_1);
	draw_matches(img1, img2, matches1, 1);
	draw_matches(img2, img3, matches2, 2);

	vector<DMatch>good_matches1, good_matches2;

	if (method == METHOD1 || method == METHOD2)
	{
		//look for symmetry matches
		vector< DMatch > sym_matches1, sym_matches2;

		symmetryTest(matches1, matches1_1, sym_matches1);
		symmetryTest(matches2, matches2_1, sym_matches2);
		draw_matches(img1, img2, sym_matches1, 3);
		draw_matches(img2, img3, sym_matches2, 4);

		//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
		if (method == METHOD1)
		{
			good_matches1 = get_good_dist_matches(sym_matches1, METHOD1);
			good_matches2 = get_good_dist_matches(sym_matches2, METHOD1);
		}
		else
		{
			good_matches1 = get_good_dist_matches(sym_matches1, METHOD2);
			good_matches2 = get_good_dist_matches(sym_matches2, METHOD2);
		}
		draw_matches(img1, img2, good_matches1, 5);
		draw_matches(img2, img3, good_matches2, 6);
	}
	else
	{
		//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
		good_matches1 = get_good_dist_matches(matches1, METHOD3);
		good_matches2 = get_good_dist_matches(matches2, METHOD3);
		draw_matches(img1, img2, good_matches1, 3);
		draw_matches(img2, img3, good_matches2, 4);
	}

	//找接近圖片重疊範圍的match(最兩邊的不要)
	vector<DMatch>best_matches1, best_matches2;

	if (direction == STITCH3_HORIZON)
	{
		best_matches1 = get_correct_range_matches_horizon(good_matches1, img1, img2, MATCH_LEFT_TO_RIGHT);
		best_matches2 = get_correct_range_matches_horizon(good_matches2, img2, img3, MATCH_LEFT_TO_RIGHT);
	}
	else
	{
		best_matches1 = get_correct_range_matches_vertical(good_matches1, img1, img2, MATCH_LEFT_TO_RIGHT);
		best_matches2 = get_correct_range_matches_vertical(good_matches2, img2, img3, MATCH_LEFT_TO_RIGHT);
	}
	draw_matches(img1, img2, best_matches1, 7);
	draw_matches(img2, img3, best_matches2, 8);

	// Find the Homography Matrix from best matches
	Mat H1, H2;

	if (direction == STITCH3_HORIZON)
		get_homography_matrix(img1, img2, img3, best_matches1, best_matches2, STITCH3_HORIZON, H1, H2);
	else
		get_homography_matrix(img1, img2, img3, best_matches1, best_matches2, STITCH3_VERTICAL, H1, H2);

	cout << H1 << endl << H2 << endl;

	// Use the Homography Matrix to warp the images
	Mat stitch3_result;

	if (direction == STITCH3_HORIZON)
		stitch3_result = get_stitch_matrix(img1, img2, img3, STITCH3_HORIZON, H1, H2);
	else
		stitch3_result = get_stitch_matrix(img1, img2, img3, STITCH3_VERTICAL, H1, H2);

	cout << "stitch3 success" << endl;
	//imshow("stitch3_result",stitch3_result);
	return stitch3_result;
}*/


int PositionImgSetting::getImgAmount(string target_folder){

	DIR *dp;
	struct dirent *ep;
	char target_char[100];

	strcpy(target_char, target_folder.c_str());
	dp = opendir(target_char);
	int count = 0;
	if (dp != NULL)
	{
		while (ep = readdir(dp)){
			puts(ep->d_name);
			count++;
		}

		(void)closedir(dp);
	}
	else
		perror("Couldn't open the directory");

	//cout << "count = " << count << endl;

	return count-2;
}


void PositionImgSetting::Initial3Img(int img_number, int vertical_angle, int stitch_part){
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\";

	if (stitch_part == STITCH_SCREEN_TOP)
	{
		vertical_angle = vertical_angle - 1;
		img_amount = img_amount_top;	
	}
	else if (stitch_part == STITCH_SCREEN_BOTTOM)
	{
		vertical_angle = vertical_angle + 1;
		img_amount =img_amount_bot;	
	}
	else
	{
		img_amount = img_amount_mid ;
	}

	assert(image_amount > 0);
	interval = (int)round(img_amount * 5.0 / 360.0);	//img next(left or right) number interval

	central_img = (int)round((float)img_number * 2.0 / 360.0 * (float)img_amount);
	if (central_img - interval >= 0)		//img max number is (image_amount - 1), min number is 0
		left_img = central_img - interval;
	else
		left_img = img_amount + central_img - interval;		

	if (central_img + interval < img_amount)
		right_img = central_img + interval;
	else
		right_img = central_img + interval - img_amount;

	cout << "central_img = " << central_img << endl << "left_img = " << left_img << endl << "right_img = " << right_img << endl;

	cout << path + to_string(vertical_angle) + "_choosen\\small\\" + to_string(left_img) + ".jpg" << endl;
	img_l = imread(path + to_string(vertical_angle) + "_choosen\\small\\" + to_string(left_img) + ".jpg");
	img_mid = imread(path + to_string(vertical_angle) + "_choosen\\small\\" + to_string(central_img) + ".jpg");
	img_r = imread(path + to_string(vertical_angle) + "_choosen\\small\\" + to_string(right_img) + ".jpg");

}


void PositionImgSetting::StitchPart(int img_number, int vertical_angle, int method, int stitch_part, vector<int> &fill, Mat& stitch)
{
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\";
	int stitch_direction_l, stitch_direction_r, check_fill_l, check_fill_r, img_vertical_angle;

	if (stitch_part == STITCH_SCREEN_TOP)
	{
		stitch_direction_l = STITCH2_LEFT_UP;
		stitch_direction_r = STITCH2_RIGHT_UP;
		check_fill_l = 2;
		check_fill_r = 3;
		img_vertical_angle = vertical_angle - 1;
	}
	else if (stitch_part == STITCH_SCREEN_MID)
	{
		stitch_direction_l = STITCH2_LEFT;
		stitch_direction_r = STITCH2_RIGHT;
		check_fill_l = 0;
		check_fill_r = 1;
		img_vertical_angle = vertical_angle;
	}
	else
	{
		stitch_direction_l = STITCH2_LEFT_DOWN;
		stitch_direction_r = STITCH2_RIGHT_DOWN;
		check_fill_l = 4;
		check_fill_r = 5;
		img_vertical_angle = vertical_angle + 1;
	}

	while (1)	//stitch left
	{
		cout << "left_img_num = " << left_img << endl;
		stitch = stitch2(stitch, img_l, method, stitch_direction_l, fill);
		imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);

		if (fill[check_fill_l] == 1) break;

		if (left_img - interval >= 0)
			left_img -= interval;
		else
			left_img = img_amount + left_img - interval;

		img_l = imread(path + to_string(img_vertical_angle) + "_choosen\\small\\" + to_string(left_img) + ".jpg");
	}

	while (1)	//stitch right
	{
		cout << "right_img_num = " << right_img << endl;
		stitch = stitch2(stitch, img_r, method, stitch_direction_r, fill);
		imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);
		
		if (fill[check_fill_r] == 1) break;

		if (right_img + interval < img_amount)
			right_img += interval;
		else
			right_img = right_img + interval - img_amount;

		img_r = imread(path + to_string(img_vertical_angle) + "_choosen\\small\\" + to_string(right_img) + ".jpg");
	}
}

void PositionImgSetting::StitchScene(int vertical_angle, int img_number, int method){	//0~179
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\";
	FILE * fp;
	char filename[200];
	
	t.reset();
	t.start();

	cout <<endl<< "*****************  Stitch Screen " << img_number << "  ******************" << endl;
	vector<int> fill(8, 0);
	
	Initial3Img(img_number, vertical_angle, STITCH_SCREEN_MID);

	Mat stitch(STITCH_SCREEN_HEIGHT, STITCH_SCREEN_WIDTH, img_mid.type());
	Rect rect(int(STITCH_SCREEN_WIDTH / 2 - STITCH_IMG_WIDTH / 2), int(STITCH_SCREEN_HEIGHT / 2 - STITCH_IMG_HEIGHT / 2), STITCH_IMG_WIDTH, STITCH_IMG_HEIGHT);
	img_mid.copyTo(stitch(rect));		//先把正中間的圖放到screen大小的矩陣
	imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);

	StitchPart(img_number, vertical_angle, method, STITCH_SCREEN_MID, fill, stitch);

	//拼上方-----------------------------------------------------------------------------------------------------
	Initial3Img(img_number, vertical_angle, STITCH_SCREEN_TOP);

	stitch = stitch2(stitch, img_mid, method, STITCH2_UP, fill);
	imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);

	StitchPart(img_number, vertical_angle, method, STITCH_SCREEN_TOP, fill, stitch);

	//stitch down----------------------------------------------------------------------------------------------
	Initial3Img(img_number, vertical_angle, STITCH_SCREEN_BOTTOM);

	stitch = stitch2(stitch, img_mid, method, STITCH2_DOWN, fill);
	imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);

	StitchPart(img_number, vertical_angle, method, STITCH_SCREEN_BOTTOM, fill, stitch);

	cout << path + "stitch\\"<<vertical_angle<<"\\stitch" + to_string(img_number) + ".jpg" << endl;
	imwrite(path + "stitch\\" + to_string(vertical_angle) + "\\stitch" + to_string(img_number) + ".jpg", stitch);

	t.stop();
	cout << "process time for stitch screen " << img_number << " = " << t.getTimeSec() << " sec." << endl;

	sprintf(filename, "%sstitch_time.txt", path);
	cout << filename << endl;
	fp = fopen(filename, "a");
	if (!fp)
		cout << "Error: Open stitch_time.txt error!" << endl;
	else
		fprintf(fp, "Process time for stitch screen %d = %f sec.\n", img_number, t.getTimeSec());
	
	fclose(fp);
}

void PositionImgSetting::StitchSceneRange(int vertical_angle, int img_number1, int img_number2, int method){
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\";
	cout << "_room_naem = " << _room_name << endl;
	if (vertical_angle == VERTICAL_CENTRAL)
	{
		img_amount_top = getImgAmount(path + to_string(VERTICAL_UP_20) + "_choosen\\small\\");
		img_amount_mid = getImgAmount(path + to_string(VERTICAL_CENTRAL) + "_choosen\\small\\");
		img_amount_bot = getImgAmount(path + to_string(VERTICAL_DOWN_20) + "_choosen\\small\\");
	}
	else
	{
		img_amount_top = getImgAmount(path + to_string(VERTICAL_CENTRAL) + "_choosen\\small\\");
		img_amount_mid = getImgAmount(path + to_string(VERTICAL_DOWN_20) + "_choosen\\small\\");
		img_amount_bot = getImgAmount(path + to_string(VERTICAL_DOWN_40) + "_choosen\\small\\");
	}

	for (int n = img_number1; n < img_number2 + 1; n++)
	{
		StitchScene(vertical_angle, n, method);
	}
}

void PositionImgSetting::StitchSceneAll(int method){
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\";
	cout <<"_room_naem = "<< _room_name << endl;
	img_amount_top = getImgAmount(path + to_string(VERTICAL_UP_20) + "_choosen\\small\\");
	img_amount_mid = getImgAmount(path + to_string(VERTICAL_CENTRAL) + "_choosen\\small\\");
	img_amount_bot = getImgAmount(path + to_string(VERTICAL_DOWN_20) + "_choosen\\small\\");

	for (int n = 0; n < 180; n++)
	{
		StitchScene(VERTICAL_CENTRAL, n, method);
	}

	img_amount_top = img_amount_mid;
	img_amount_mid = img_amount_bot;
	img_amount_bot = getImgAmount(path + to_string(VERTICAL_DOWN_40) + "_choosen\\small\\");

	for (int n = 0; n < 180; n++)
	{
		StitchScene(VERTICAL_DOWN_20, n, method);
	}
}

Mat PositionImgSetting::GetStitchScene(int img_number){
	string path = "D:\\image\\" + _room_name + "\\position" + to_string(_number) + "\\img" + to_string(img_number) + ".jpg";
	return imread(path);
}

/*Mat PositionImgSetting::get_screen(int angle_horizon, int angle_vertical){
int stitch9_number;
string path = "D://repo/image/position" + to_string(_number) + "/img";
Mat screen;

if (angle_horizon % 30 == 0 || angle_horizon % 30 == 10)
{
if (angle_vertical % 30 == 0 || angle_vertical % 30 == 10)
{
stitch9_number = angle_horizon / 30 + (angle_vertical / 30 - 1)*(-12);
screen = make_screen(stitch9_number, angle_horizon % 30, angle_vertical % 30);
}
else if (angle_vertical % 30 == 20)
{
stitch9_number = angle_horizon / 30 + (angle_vertical / 30 )*(-12);
screen = make_screen(stitch9_number, angle_horizon % 30, -10);
}
}
else if (angle_horizon % 30 == 20)
{
if (angle_vertical % 30 == 0 || angle_vertical % 30 == 10)
{
stitch9_number = angle_horizon / 30 + 1 + (angle_vertical / 30 - 1)*(-12);
screen = make_screen(stitch9_number, -10, angle_vertical % 30);
}
else if (angle_vertical % 30 == 20)
{
stitch9_number = angle_horizon / 30 + 1 + (angle_vertical / 30)*(-12);
screen = make_screen(stitch9_number, -10, -10);
}
}
return screen;
}*/