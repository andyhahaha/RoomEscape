#include <string>
#include <opencv2/contrib/contrib.hpp> 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>
#include <stdio.h>
#include "../h/Clue.h"

using namespace cv;
using namespace std;

Clue::Clue()
{
	_room_name = "no name";			//密室名稱
	_position_num = -1;			//position編號
	_clue_name = "no name";			//線索名稱

	_start_scene_up = -1;
	_end_scene_up = -1;
	_start_scene_down = -1;
	_end_scene_down = -1;

	//change scene 時座標移動多少
	_row_shift = 0.4;
	_col_shift = 0.05;

	//線索所在位置   某個視角的圖  還沒有轉角度時的位置
	//左上角的座標
	_location_row = -2.0;
	_location_col = -2.0;
	_width = 0;		//寬
	_height = 0;	//長

	_current_dialog = 0; 		//目前使用到哪一個對話
	_dialog.clear();		//線索文字內容
	_current_img = 0; 		//目前使用到哪一個3D image
	_img_path.clear();		//線索3D image內容

	_cluebox_img = "no path";

	_state.clear();	//紀錄每個state是什麼代號
	_current_state = 0;	//線索狀態
};

Clue::Clue(string room_name, int position_num, string clue_name, int start_scene_up, int start_scene_down, int row, int column, int width, int height)
{
	//(room name, position number, clue name, start_scene_up, start_scene_down,  左上角的座標row,左上角的座標column,寬,長
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	_row_shift = 0.4;
	_col_shift = 0.05;

	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	set_end_scene_up();
	set_end_scene_down();
	_location_row=row;	
	_location_col=column;
	_width=width;		
	_height=height;

	_current_dialog = 0; 		//目前使用到哪一個對話
	_dialog.clear();		//線索文字內容
	_current_img = 0; 		//目前使用到哪一個3D image
	_img_path.clear();		//線索3D image內容

	_cluebox_img = "no path";

	_state.clear();	//紀錄每個state是什麼代號
	_current_state = 0;	//線索狀態
}

void Clue::set_room_name(string s)
{
	_room_name=s;
}

void Clue::set_position_num(int n)
{
	_position_num = n;
}

void Clue::set_clue_name(string s)
{
	_clue_name = s;
}

void Clue::set_location_row(int row)
{
	_location_row=row;
}
void Clue::set_location_col(int column)
{
	_location_col=column;
}

void Clue::set_width(int w)
{
	_width = w;
}

void Clue::set_height(int h)
{
	_height = h;
}

void Clue::set_start_scene_up(int i)
{
	_start_scene_up = i;
}

int Clue::set_end_scene_up()
{
	if (_start_scene_up == -1)
	{
		cout << "ERROR: Start_scene_up not define yet!" << endl;
		_end_scene_up = -1;
		return -1;
	}

	int scene = _start_scene_up - 1;
	int x = _location_col;

	while (x < 1)
	{
		scene++;
		if (scene == 180) scene = 0;
		x += _col_shift;
	}
	_end_scene_up = scene;
	return 1;
}

void Clue::set_start_scene_down(int i)
{
	_start_scene_down = i;
}

int Clue::set_end_scene_down()
{
	if (_start_scene_down == -1)
	{
		cout << "ERROR: Start_scene_down not define yet!" << endl;
		_end_scene_down = -1;
		return -1;
	}

	int scene = _start_scene_down - 1;
	int x = _location_col;

	while (x < 1)
	{
		scene++;
		if (scene == 180) scene = 0;
		x += _col_shift;
	}
	_end_scene_down = scene;
	return 1;
}


int Clue::current_state()
{
	return _current_state;
}

void Clue::next_state()
{
	_current_state -= 1;
}

void Clue::add_state(int state_code)
{
	_state.push_back(state_code);
}

void Clue::set_cluebox_img(string path)
{
	_cluebox_img = path;
}

Mat Clue::get_cluebox_img()
{
	Mat img = imread(_cluebox_img);

	if (!img.data)
	{
		cout << "ERROR: Read clue box image failed!" << endl;
		img.create(1, 1, CV_32F);
	}
	return img;
}

int Clue::current_img()
{
	return _current_img;
}

void Clue::next_img()
{
	_current_img += 1;
}

void Clue::add_img_path(string path)
{
	_img_path.push_back(path);
}

string Clue::get_img(int number)
{  	
	if (_img_path[number][0] == NULL)
	{
		cout << "ERROR: Image" << number << " undefined!" << endl;
		return NULL;
	}
	return _img_path[number];
}

int Clue::current_dialog()
{
	return _current_dialog;
}

void Clue::next_dialog()
{
	_current_dialog += 1;
}

void Clue::add_dialog(string d)
{
	_dialog.push_back(d);
}

string Clue::get_dialog(int index)
{ 
	if (_dialog[index][0] == NULL)
	{
		cout << "ERROR: Dialog" << index << " undefined!" << endl;
		return NULL;
	}
	return _dialog[index];
}


string Clue::room_name()
{
	return _room_name;
}

int Clue::position_num()
{
	return _position_num;
}

string Clue::clue_name()
{
	return _clue_name;
}

int Clue::show_to_scene(int vertical, int scene_now)
{
	if (vertical == VERTICAL_CENTRAL)
	{
		if (_start_scene_up == -2)
		{
			cout << "ERROR: Start scene up undefined!" << endl;
			return -1;
		}

		if (_start_scene_up < _end_scene_up)
		{
			if (scene_now >= _start_scene_up && scene_now <= _end_scene_up)
				return 1;
		}
		else
		{
			if (scene_now >= _start_scene_up || scene_now <= _end_scene_up)
				return 1;
		}
	}
	else if (vertical == VERTICAL_DOWN_20)
	{
		if (_start_scene_down == -2)
		{
			cout << "ERROR: Start scene down undefined!" << endl;
			return -1;
		}

		if (_start_scene_down < _end_scene_down)
		{
			if (scene_now >= _start_scene_down && scene_now <= _end_scene_down)
				return 1;
		}
		else
		{
			if (scene_now >= _start_scene_down || scene_now <= _end_scene_down)
				return 1;
		}
	}
	return 0;
}

float Clue::location_row_now(int vertical, int scene_now)
{
	if (_location_row == -2.0)
	{
		cout << "ERROR: location row undefined!" << endl;
		return _location_row;
	}

	if (vertical == VERTICAL_CENTRAL)
	{
		return _location_row + _row_shift;
	}
	return _location_row;
}

float Clue::location_col_now(int vertical, int scene_now){
	if (_location_col == -2.0)
	{
		cout << "ERROR: location col undefined!" << endl;
		return _location_col;
	}

	if (vertical == VERTICAL_CENTRAL)
	{
		if (scene_now - _start_scene_up < 0)
			return _location_col + (180 - (scene_now - _start_scene_up))*_col_shift;
		else
			return _location_col + (scene_now - _start_scene_up)*_col_shift;
	}
	else
	{
		if (scene_now - _start_scene_down < 0)
			return _location_col + (180 - (scene_now - _start_scene_down))*_col_shift;
		else
			return _location_col + (scene_now - _start_scene_down)*_col_shift;
	}
}

float Clue::location_row(){
	return _location_row;
}

float Clue::location_col(){
	return _location_col;
}

int Clue::width(){
	return _width;
}

int Clue::height(){
	return _height;
}

int Clue::start_scene_up(){
	return _start_scene_up;
}

int Clue::end_scene_up(){
	return _end_scene_up;
}

int Clue::start_scene_down(){
	return _start_scene_down;
}

int Clue::end_scene_down(){
	return _end_scene_down;
}

void Clue::_show_animation() {

	printf("_show_animation\n");


}

int Clue::write_initial_file(){
	char path[1000];
	int length;
	sprintf(path, "D:\\clue\\%s\\position%d\\%s", _room_name, _position_num, _clue_name);

	FILE *fp = fopen(path, "wb");
	if (!fp)
	{
		cout << "ERROR: Unable to open the clue file!" << endl;
		return -1;
	}

	length = sizeof(_clue_name);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&_clue_name, sizeof(_clue_name), 1,fp);

	fwrite(&_start_scene_up, sizeof(int), 1, fp);
	fwrite(&_end_scene_up, sizeof(int), 1, fp);
	fwrite(&_start_scene_down, sizeof(int), 1, fp);
	fwrite(&_end_scene_down, sizeof(int), 1, fp);

	fwrite(&_location_row, sizeof(int), 1, fp);
	fwrite(&_location_col, sizeof(int), 1, fp);
	fwrite(&_width, sizeof(int), 1, fp);
	fwrite(&_height, sizeof(int), 1, fp);

	fwrite(&_cluebox_img, sizeof(_cluebox_img), 1, fp);

	for (int i = 0; i < _state.size(); i++)
	{
		fwrite(&_state[i], sizeof(int), 1, fp);
	}

	for (int i = 0; i < _dialog.size(); i++)
	{
		length = sizeof(_dialog[i]);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&_dialog[i], sizeof(_dialog[i]), 1, fp);
	}

	for (int i = 0; i < _img_path.size(); i++)
	{
		length = sizeof(_img_path[i]);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&_img_path[i], sizeof(_img_path[i]), 1, fp);
	}
	fclose(fp);
	return 1;
};

ostream& operator<<(ostream& os, const Clue& clue)
{
	
	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
	os << "name = " << clue._clue_name << "\n"\
		"_clue_location_row = " << clue._location_row << "\n"\
		"_clue_location_column = " << clue._location_col << "\n"\
		"_current_state = " << clue._current_state << "\n" << endl;

	return os;
}