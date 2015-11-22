#ifndef _CLUE_H_
#define _CLUE_H_
#include <string>
#include <opencv2/contrib/contrib.hpp> 
#include "opencv2/nonfree/nonfree.hpp"

#include <iostream>
#include "Define.h"

using namespace cv;
using namespace std;

class Clue {
public:
	Clue();
	Clue(string, int, string, int, int, int, int, float, float, float, float, float, float, float);	//room name, position number, clue name, start_scene_up, end_scene_up, start_scene_down, end_scene_down
	Clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down, vector<Point3f> obj_corner);
	Clue(string, int, string, vector<Point2i>);
	Clue(string);	//read clue initial file

	void set_clue(string, int, string, int, int, int, int);
	int set_clue(string);

	void set_room_name(string);
	void set_position_num(int);
	void set_clue_name(string);


	void set_start_scene_up(int);			//設定平視第幾個scene會出現(0~179)
	void set_end_scene_up(int);				//設定平視最後一個出現的scene(0~179)
	void set_start_scene_down(int);			//設定俯視第幾個scene會出現(0~179)
	void set_end_scene_down(int);			//設定俯視最後一個出現的scene(0~179)
	void set_obj_corner(Vector<Point3f>);
	void set_2D_coordinate(Vector<Point2i>);

	int current_state();		//return _state_array(_current_state)
	void next_state(int);		//assign _current_state
	void add_state(int);		//加上一個新的state，輸入一個state代號，他會加在目前的state vector的最後面

	void set_cluebox_img(string);	//放在clue box的2D圖片路徑
	Mat get_cluebox_img();
	int current_2Dimg();			//return _current_2Dimg
	void next_2Dimg(int);  			//assign _current_2Dimg
	void add_2Dimg_path(string);	//add一個image(2D)路徑
	string get_2Dimg(int);

	int current_3Dobj();			//return _current_3Dobj
	void next_3Dobj(int);  			//assign _current_3Dobj
	void add_3Dobj_path(string);	//add一個obj(3D)路徑
	string get_3Dobj(int);

	int current_dialog();		//return _current_dialog
	void next_dialog();			//assign _current_dialog
	void add_dialog(string);	//add一個對話  內容
	string get_dialog(int); 	//取得第幾個對話

	Vector<Point2i> get_2D_coordinate();

	
	
	/* Get Clue basic information */
	string room_name();
	int position_num();
	string clue_name();

	float trans_x();
	float trans_y();
	float trans_z();
	float rot_x();
	float rot_y();
	float rot_z();
	float scale();

	int start_scene_up();
	int end_scene_up();
	int start_scene_down();
	int end_scene_down();
	Vector<Point3f> obj_corner();

	int show_to_scene(int, int);	//check if the clue is in the current scene



	int write_initial_file();	//write the basic information of the clue to a file
	friend ostream& operator<<(ostream& , const Clue& );

private:
	string _room_name;			//密室名稱
	int _position_num;			//position編號
	string _clue_name;			//線索名稱

	//線索所在視角，position可以藉由這個知道他在哪張圖裡
	int _start_scene_up;		
	int _end_scene_up;
	int _start_scene_down;
	int _end_scene_down;

	//3D 座標
	float _trans_x;
	float _trans_y;
	float _trans_z;
	float _rot_x;
	float _rot_y;
	float _rot_z;
	float _scale;




	//線索所在位置   某個視角的圖  還沒有轉角度時的位置
	//左上角的座標
	vector<Point3f> _obj_corner;
	vector<Point2i> _2DCoordinate;


	int _current_dialog; 		//目前使用到哪一個對話
	vector<string>_dialog;		//線索文字內容
	int _current_2Dimg; 		//目前使用到哪一個3D image
	vector<string>_2Dimg_path;		//線索2D image內容
	int _current_3Dobj; 		//目前使用到哪一個3D obj
	vector<string>_3Dobj_path;		//線索3D obj內容

	string _cluebox_img;

	vector<int> _state;	//紀錄每個state是什麼代號
	int _current_state;	//線索狀態
	void _show_animation();  	//顯示動畫
};

#endif