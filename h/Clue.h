#ifndef _CLUE_H_
#define _CLUE_H_
#include <string>
#include <opencv2/contrib/contrib.hpp> 
#include <iostream>
#include "Define.h"

using namespace cv;
using namespace std;

class Clue {
public:
	Clue();
	Clue(string, int, string, int, int, int, int, int, int);	//room name, position number, clue name, start_scene_up, start_scene_down, 左上角的座標row,左上角的座標column,寬,長
	
	void set_room_name(string);
	void set_position_num(int);
	void set_clue_name(string);

	void set_location_row(int);		//左上角 row
	void set_location_col(int);		//左上角col
	void set_width(int);			//設定clue觸發width
	void set_height(int);			//設定clue觸發height
	void set_start_scene_up(int);	//設定平視第幾個scene會出現(0~179)
	int set_end_scene_up();			//設定平視最後一個出現的scene(0~179)
	void set_start_scene_down(int);	//設定俯視第幾個scene會出現(0~179)
	int set_end_scene_down();		//設定俯視最後一個出現的scene(0~179)

	int current_state();	//return _state_array(_current_state)
	void next_state();		//_current_state + 1
	void add_state(int);		//加上一個新的state，輸入一個state代號，他會加在目前的state vector的最後面

	void set_cluebox_img(string);	//放在clue box的2D圖片路徑
	int current_img();				//return _current_img
	void next_img();  				//將 _current_img + 1, 下次change image就會秀下一張圖
	void add_img_path(string);		//add一個image(3D)路徑
	Mat get_img(int);

	int current_dialog();		//return _current_dialog
	void next_dialog();			//將 _current_dialog + 1, 下次change dialog就會秀下一個對話
	void add_dialog(string);	//add一個對話  內容
	string get_dialog(int); 	//取得第幾個對話
	
	
	string room_name();
	int position_num();
	string clue_name();
	int location_row();
	int location_col();
	int width();
	int height();
	int start_scene_up();
	int end_scene_up();
	int start_scene_down();
	int end_scene_down();

	int write_initial_file();	//將clue的初始內容寫入initial檔案
	friend ostream& operator<<(ostream& , const Clue& );

private:
	string _room_name;			//密室名稱
	int _position_num;			//position編號
	string _clue_name;			//線索名稱

	//線索所在視角，position可以藉由這個知道他在哪張圖裡
	int _start_scene_up;		//
	int _end_scene_up;
	int _start_scene_down;
	int _end_scene_down;

	//change scene 時座標移動多少
	int _row_shift;
	int _col_shift;

	//線索所在位置   某個視角的圖  還沒有轉角度時的位置
	//左上角的座標
	int _location_row;	
	int _location_col;
	int _width;		//寬
	int _height;	//長

	int _current_dialog; 		//目前使用到哪一個對話
	vector<string>_dialog;		//線索文字內容
	int _current_img; 		//目前使用到哪一個3D image
	vector<string>_img_path;		//線索3D image內容

	string _cluebox_img;

	vector<int> _state;	//紀錄每個state是什麼代號
	int _current_state;	//線索狀態
	void _show_animation();  	//顯示動畫
	
};

#endif