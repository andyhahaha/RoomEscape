#ifndef _POSITIONSETTING_H_
#define _POSITIONSETTING_H_
#include "Image.h" 
#include <string>
using namespace std;


class PositionImgSetting {
public:
	PositionImgSetting();
	PositionImgSetting(string&, int);	//給room name 和 position編號

	void set_room_name(int);
	string& get_room_name();	
	void set_number(int);
	int get_number();	//查看位置編號	
	Mat get_image(int);	//讀檔查看編號n的圖
	
	void StitchSceneRange(int, int, int, int);	//stitch from num1 to num2
	void StitchSceneAll(int);	//把360張stitch圖都拼接出來
	
	//stitch完可以做測試用
	void draw_2img_matches(Mat, Mat, int);
	//測試在PositionSetting做好，position為了不浪費記憶體一次只讀一張圖
	Mat GetStitchScene(int);	//讀檔image/position_number/n.jpg
	//Mat get_screen(int, int);	//輸入水平及垂直角度，得到視窗長相
	void show_scene();		//秀出完整視窗，包括拖曳功能

private:
	string _room_name;
	int _number; // 位置編號

	Mat stitch2(Mat, Mat, int, int, vector<int> &);
	int getImgAmount(string);
	void Initial3Img(int, int, int);	//stitch_part 代表上方 中間 或下方
	void StitchPart(int, int, int, int, vector<int> &, Mat&);
	
	void draw_matches(Mat, Mat, vector< KeyPoint >, vector< KeyPoint >, vector< DMatch >, int);
	void symmetryTest(const vector<DMatch>, const vector<DMatch>, vector<DMatch>&);
	vector< DMatch > get_good_dist_matches( vector< DMatch >, int);
	vector< DMatch > get_correct_range_matches(vector<DMatch>, Image, Image, int);
	vector< DMatch > get_correct_range_matches_vertical(vector<DMatch>, Image, Image, int);
	
	void get_homography_matrix(Image, Image, vector< DMatch >, Mat&);
	Mat get_blending_matrix(Mat, Mat, Mat);
	Mat get_stitch_matrix(Mat, Mat, int, Mat, vector<int> &);
	//Mat make_screen(int, int, int);	//輸入編號為多少的stitch9的圖，以及水平轉幾度，垂直轉幾度
	void StitchScene(int, int, int);	//輸入數字n，拼接圖片編號n，並輸出存在image/room name/position_number/stitch/1 or 2/stitch_n.jpg
};

#endif