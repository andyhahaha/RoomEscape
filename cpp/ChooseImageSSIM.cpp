#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/contrib/contrib.hpp>	//要用timer就需要

#include "../h/Define.h"
#include "../h/ssim.h"

using namespace std;
using namespace cv;


#define C1 (float) (0.01 * 255 * 0.01  * 255)
#define C2 (float) (0.03 * 255 * 0.03  * 255)


// sigma on block_size
double sigma(Mat & m, int i, int j, int block_size)
{
	double sd = 0;

	Mat m_tmp = m(Range(i, i + block_size), Range(j, j + block_size));
	Mat m_squared(block_size, block_size, CV_64F);

	multiply(m_tmp, m_tmp, m_squared);

	// E(x)
	double avg = mean(m_tmp)[0];
	// E(x²)
	double avg_2 = mean(m_squared)[0];


	sd = sqrt(avg_2 - avg * avg);

	return sd;
}

// Covariance
double cov(Mat & m1, Mat & m2, int i, int j, int block_size)
{
	Mat m3 = Mat::zeros(block_size, block_size, m1.depth());
	Mat m1_tmp = m1(Range(i, i + block_size), Range(j, j + block_size));
	Mat m2_tmp = m2(Range(i, i + block_size), Range(j, j + block_size));


	multiply(m1_tmp, m2_tmp, m3);

	double avg_ro = mean(m3)[0]; // E(XY)
	double avg_r = mean(m1_tmp)[0]; // E(X)
	double avg_o = mean(m2_tmp)[0]; // E(Y)


	double sd_ro = avg_ro - avg_o * avg_r; // E(XY) - E(X)E(Y)

	return sd_ro;
}

// Mean squared error
double eqm(Mat & img1, Mat & img2)
{
	int i, j;
	double eqm = 0;
	int height = img1.rows;
	int width = img1.cols;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			eqm += (img1.at<double>(i, j) - img2.at<double>(i, j)) * (img1.at<double>(i, j) - img2.at<double>(i, j));

	eqm /= height * width;

	return eqm;
}



/**
*	Compute the PSNR between 2 images
*/
double psnr(Mat & img1, Mat & img2, int block_size)
{
	int D = 255;
	return (10 * log10((D*D) / eqm(img1, img2)));
}


/**
* Compute the SSIM between 2 images
*/
double ssim(Mat & img1, Mat & img2, int block_size, bool show_progress = FALSE)
{
	double ssim = 0;

	int nbBlockPerHeight = img1.rows / block_size;
	int nbBlockPerWidth = img1.cols / block_size;
	for (int k = 0; k < nbBlockPerHeight; k++)
	{
		for (int l = 0; l < nbBlockPerWidth; l++)
		{
			int m = k * block_size;
			int n = l * block_size;

			double avg_o = mean(img1(Range(k, k + block_size), Range(l, l + block_size)))[0];
			double avg_r = mean(img2(Range(k, k + block_size), Range(l, l + block_size)))[0];
			double sigma_o = sigma(img1, m, n, block_size);
			double sigma_r = sigma(img2, m, n, block_size);
			double sigma_ro = cov(img1, img2, m, n, block_size);
			ssim += ((2 * avg_o * avg_r + C1) * (2 * sigma_ro + C2)) / ((avg_o * avg_o + avg_r * avg_r + C1) * (sigma_o * sigma_o + sigma_r * sigma_r + C2));

		}
		// Progress
		if (show_progress)
			cout << "\r>>SSIM [" << (int)((((double)k) / nbBlockPerHeight) * 100) << "%]";
	}
	ssim /= nbBlockPerHeight * nbBlockPerWidth;

	if (show_progress)
	{
		cout << "\r>>SSIM [100%]" << endl;
		cout << "SSIM : " << ssim << endl;
	}

	return ssim;
}



double compute_quality_metrics(Mat img_1, Mat img_2, int block_size)
{
	Mat img1;
	Mat img2;

	cvtColor(img_1, img1, CV_RGB2GRAY);
	cvtColor(img_2, img2, CV_RGB2GRAY);

	img1.convertTo(img1, CV_64F);
	img2.convertTo(img2, CV_64F);

	int height_o = img1.rows;
	int height_r = img2.rows;
	int width_o = img1.cols;
	int width_r = img2.cols;

	// Check pictures size
	if (height_o != height_r || width_o != width_r)
	{
		cout << "Images must have the same dimensions" << endl;
		return 0;
	}

	// Check if the block size is a multiple of height / width
	if (height_o % block_size != 0 || width_o % block_size != 0)
	{
		cout << "WARNING : Image WIDTH and HEIGHT should be divisible by BLOCK_SIZE for the maximum accuracy" << endl
			<< "HEIGHT : " << height_o << endl
			<< "WIDTH : " << width_o << endl
			<< "BLOCK_SIZE : " << block_size << endl
			<< endl;
	}

	double ssim_val = ssim(img1, img2, block_size);
	//double psnr_val = psnr(img1, img2, block_size);

	cout << "SSIM : " << ssim_val << endl;
	//cout << "PSNR : " << psnr_val << endl;

	return ssim_val;
}


//use calcSSIM
int choose_30max(int num_next, string path_src, Mat img1_new, Mat &img2, Mat mask, double ssim)
{
	int num_next_new = num_next;
	Mat compare;

	for (int i = num_next + 1; i < num_next + 31; i++)
	{
		compare = imread(path_src + to_string(i) + ".jpg");
		if (!compare.data) break;

		double ssim_compare = calcSSIM(img1_new, compare, 0, CV_BGR2YUV, mask);
		cout << "SSIM_compare = " << ssim_compare << endl;
		if (ssim_compare > ssim)
		{
			num_next_new = i;
			ssim = ssim_compare;
			img2 = compare;

			if (ssim > 0.9) break;
		}
		else if (ssim_compare < 0.47)
		{
			break;
		}
	}
	return num_next_new;
}


int choose_100max(int num_next, string path_src, Mat H, Mat img1, double ssim)
{
	int num_next_new = num_next;

	for (int i = num_next; i < num_next + 101; i++)
	{
		Mat compare = imread(path_src + to_string(i) + ".jpg");
		warpPerspective(compare, compare, H, Size(img1.cols, img1.rows));

		double ssim_compare = compute_quality_metrics(img1, compare, 120);
		if (ssim_compare > ssim)
		{
			num_next_new = i;
			ssim = ssim_compare;

			if (ssim > 0.9) break;
			
		}
		if (ssim_compare < 0.1)break;
		
	}
	return num_next_new;
}

//找到img_from變成img_to的H
Mat find_homography_matrix(string path, int img_to_num, int img_from_num)
{
	// Load the images
	Mat image1 = imread(path + to_string(img_to_num) + ".jpg");
	Mat image2 = imread(path + to_string(img_from_num ) + ".jpg");
	Mat img_1, img_2;

	// Convert to Grayscale
	cvtColor(image1, img_1, CV_RGB2GRAY);
	cvtColor(image2, img_2, CV_RGB2GRAY);

	//第一步，用SIFT算子检测关键点
	SurfFeatureDetector detector;//构造函数采用内部默认的
	vector<KeyPoint> keypoints_1, keypoints_2;//构造2个专门由点组成的点向量用来存储特征点

	detector.detect(img_1, keypoints_1);//将img_1图像中检测到的特征点存储起来放在keypoints_1中
	detector.detect(img_2, keypoints_2);//同理

	//计算特征向量
	SurfDescriptorExtractor extractor;//定义描述子对象
	Mat descriptors_1, descriptors_2;//存放特征向量的矩阵

	extractor.compute(img_1, keypoints_1, descriptors_1);//计算特征向量
	extractor.compute(img_2, keypoints_2, descriptors_2);

	//-- Step 3: Matching descriptor vectors using FLANN matcher----------------------以下做Stitch--------------------------------
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
	vector< DMatch > good_matches;

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	vector< Point2f > img1, img2;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		img1.push_back(keypoints_1[good_matches[i].queryIdx].pt);
		img2.push_back(keypoints_2[good_matches[i].trainIdx].pt);
	}

	// Find the Homography Matrix
	Mat H = findHomography(img2, img1, CV_RANSAC);
	return H;
}



//use calcSSIM
void choose_image(string& room_name, int position_number, int vertical_angle, int img_num1, int img_num2)
{
	string path_src = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "\\";
	string path_dst = "D:\\image\\" + room_name + "\\position" + to_string(position_number) + "\\" + to_string(vertical_angle) + "_choosen\\";
	int num_now = 0;
	int num_next = 1;
	int img_num = 0;
	double ssim, ssim2, min = 0.50, max = 0.75;

	Mat img1, img2, img1_new, img2_new, white_new;
	TickMeter  tm;

	//img1 & img2 之間的矩陣(img1乘上這個矩陣變img2的樣子)
	Mat H = find_homography_matrix(path_src, img_num2, img_num1);

	//先把第一張圖存起來
	img1 = imread(path_src + to_string(num_now) + ".jpg");

	int img_width = img1.cols;
	int img_height = img1.rows;
	
	//img1轉到img2的視角(乘H)
	imwrite(path_dst + to_string(img_num) + ".jpg", img1);
	cout << path_dst;
	warpPerspective(img1, img1_new, H, Size(img_width, img_height));

	//先做一個白色的轉H的圖
	Mat white(img_height, img_width, CV_8U, Scalar(255));;
	warpPerspective(white, white_new, H, Size(img_width, img_height));

	while (1)
	{
		img2 = imread(path_src + to_string(num_next) + ".jpg");

		if (!img2.data)		//如果找完所有圖沒找到最後一張(可能是找超過了，或是標準太高還沒找到)，降低標準，最多降低兩次就break
		{
			if (max < 0.5)
			{
				break;
			}
			else
			{
				num_next = num_now + 1;
				max = max - 0.1;
				min = min - 0.1;
			}
		}
		else
		{
			cout << num_next << endl;

			ssim2 = calcSSIM(img1, img2);	//將num_now和num_next的圖直接做比較，如果兩者太像就不要
			cout << "ssim for img1 & img2 ------------- " << endl << "SSIM = " << ssim2 << endl;

			ssim = calcSSIM(img1_new, img2, 0, CV_BGR2YUV, white_new);
			cout << "ssim for img1_new & img2 with mask -------- " << endl << "SSIM = " << ssim << endl;

			if (ssim > max && ssim2<0.8)
			{
				max = 0.75;
				min = 0.5;
				if (ssim < 0.9) num_next = choose_30max(num_next, path_src, img1_new, img2, white_new, ssim);

				Mat first_choose = imread(path_dst + "0.jpg");
				warpPerspective(img2, img2_new, H, Size(img_width, img_height));
				if (img_num > 150 && calcSSIM(first_choose, img2_new) > 0.75) break;

				imwrite(path_dst + to_string(++img_num) + ".jpg", img2);
				num_now = num_next;
				num_next++;

				img1 = imread(path_src + to_string(num_now) + ".jpg");
				warpPerspective(img1, img1_new, H, Size(img_width, img_height));
			}
			else if (ssim < min)
			{
				num_next = num_now + 1;
				max = max - 0.1;
				if (max < 0) max = 0;

				min = min - 0.1;
				if (min < 0) min = 0;
			}
			else
			{
				num_next++;
			}
		}
	}
}