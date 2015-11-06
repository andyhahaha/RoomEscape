#include <string>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "../h/Image.h"

using namespace std;

// 預設建構函式
Image::Image() {
	
}

Image::Image(Mat img) {
	_img = img; 

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Mat data is null!" << endl;
	}
	else
	{
		cout << "Mat open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints); 

		SurfDescriptorExtractor extractor;//定义描述子对象
		extractor.compute(img_gray, _keypoints, _descriptors);

		/*if (_descriptors.type() != CV_32F) {
			_descriptors.convertTo(_descriptors, CV_32F);
			cout << "haha" << endl;
		}*/
	}
}

Image::Image(string& path) {
	_img = imread(path); 

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Path open error!" << endl;
	}
	else
	{
		cout << "Path open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints);

		SurfDescriptorExtractor extractor;//定义描述子对象
		extractor.compute(img_gray, _keypoints, _descriptors);

		/*if (_descriptors.type() != CV_32F) {
			_descriptors.convertTo(_descriptors, CV_32F);
			cout << "haha" << endl;
		}*/
	}
}

Mat Image::mat() {
	return _img;
}

vector < KeyPoint > Image::keypoints() {
	return _keypoints;
}

Mat Image::descriptors() {
	return _descriptors;
}


void Image::set_image(string& path) {
	cout << path << endl;
	_img = imread(path); // 名字

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Path open error!" << endl;
	}
	else
	{
		cout << "Path open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints);

		SurfDescriptorExtractor extractor;
		extractor.compute(img_gray, _keypoints, _descriptors);

		/*if (_descriptors.type() != CV_32F) {
			_descriptors.convertTo(_descriptors, CV_32F);
			cout << "haha" << endl;
		}*/
	}
}

void Image::set_image(Mat img) {
	_img = img;

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Mat data is null!" << endl;
	}
	else
	{
		cout << "Mat open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints);

		SurfDescriptorExtractor extractor;
		extractor.compute(img_gray, _keypoints, _descriptors);

		/*if (_descriptors.type() != CV_32F) {
			_descriptors.convertTo(_descriptors, CV_32F);
			cout << "haha" << endl;
		}*/
	}
}

void Image::set_keypoints(string& path) {
	cout << path << endl;
	_img = imread(path); // 名字

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Path open error!" << endl;
	}
	else
	{
		cout << "Path open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints);
	}
}

void Image::set_keypoints(Mat img) {
	_img = img;

	if (!_img.data)//如果數據為空
	{
		cout << "Error: Mat data is null!" << endl;
	}
	else
	{
		cout << "Mat open right" << endl;

		Mat img_gray;
		cvtColor(_img, img_gray, CV_RGB2GRAY);

		SurfFeatureDetector detector;
		detector.detect(img_gray, _keypoints);
	}
}

void Image::set_keypoints(vector < KeyPoint > keypoints) {
	if (!_img.data)//如果數據為空
	{
		cout << "Error: Mat data is null!" << endl;
	}
	else
	{
		cout << "Mat open right" << endl;

		if (keypoints.size() == 0)
		{
			cout << "Error: keypoints not defined!" << endl;
		}
		else
		{
			_keypoints.clear();
			_keypoints = keypoints;
		}
	}
}

/*void Image::set_descriptors(vector < KeyPoint >keypoints) {
	
	if (!_img.data)//如果數據為空
	{
		cout << "open error" << endl;
	}
	else
	{
		cout << "open right" << endl;

		if (keypoints.size() == 0)
		{
			cout << "keypoints not defined" << endl;
		}
		else
		{
			_keypoints.clear();
			_keypoints = keypoints;

			Mat img_gray;
			cvtColor(_img, img_gray, CV_RGB2GRAY);

			SurfDescriptorExtractor extractor;
			extractor.compute(img_gray, _keypoints, _descriptors);
		}
	}
}*/