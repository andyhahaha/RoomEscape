#include <string>
#include <opencv2/contrib/contrib.hpp> 

using namespace std;
using namespace cv;

class Image {		//一張圖的資訊
public:
	Image();
	Image(string&);	//讀取路徑並做SIFT
	Image(Mat);	//輸入矩陣並做SIFT

	Mat mat();	//輸出img的Mat	
	vector < KeyPoint > keypoints();
	Mat descriptors();
	//int get_image_number();

	void set_image(string&);	//讀取路徑並做SIFT，找出keypoints和descriptors
	void set_image(Mat);	//輸入矩陣並做SIFT，找出keypoints和descriptors

	void set_keypoints(string&);	//讀取路徑並做SIFT，找出keypoints而已
	void set_keypoints(Mat);	//輸入矩陣並做SIFT，找出keypoints而已
	void set_keypoints(vector < KeyPoint >);	//指定keypoints

	//void set_descriptors(vector < KeyPoint >);	//用指定keypoints找到descriptors

private:
	Mat _img;
	vector < KeyPoint > _keypoints;
	Mat _descriptors;
	//int _number;	//圖片編號，方便之後在position的時候對圖片順序做管理
};