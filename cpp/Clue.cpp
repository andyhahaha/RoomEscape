#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <stdio.h>
#include "../h/Clue.h"

using namespace cv;
using namespace std;



/* Clue: Initialization 
*/

Clue::Clue()
{
	_room_name = "no name";		//密室名稱
	_position_num = -1;			//position編號
	_clue_name = "no name";		//線索名稱

	_start_scene_up = -1;
	_end_scene_up = -1;
	_start_scene_down = -1;
	_end_scene_down = -1;


	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();	
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();		
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();		

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態
};


/* Clue: Initial 3D clue by giving some parameters. 
*/

Clue::Clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down, float trans_x, float trans_y, float trans_z, float rot_x, float rot_y, float rot_z, float scale)
{
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;


	_trans_x = trans_x;
	_trans_y = trans_y; 
	_trans_z = trans_z;
	_rot_x = rot_x;
	_rot_y = rot_y;
	_rot_z = rot_z;
	_scale = scale;
	

	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	_end_scene_up = end_scene_up;
	_end_scene_down = end_scene_down;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();		
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();		
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態
}



/* Clue: Initial 2D clue by giving some parameters.
*/

Clue::Clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down, vector<Point3f> obj_corner)
{
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	_end_scene_up = end_scene_up;
	_end_scene_down = end_scene_down;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態

	_obj_corner.assign(obj_corner.begin(), obj_corner.end());
}

/*near scence clue*/
Clue::Clue(string room_name, int position_num, string clue_name, vector<Point2i> coordinate){
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態

	_2DCoordinate.assign(coordinate.begin(), coordinate.end());
}



/* Clue: Initial clue by giving a path of a clue file. 
*/

Clue::Clue(string clue_path)
{
	char path[1000];
	sprintf(path, "%s", clue_path);
	int length = 0, size = 0, end;

	FILE *fp = fopen(path, "rb");
	if (!fp)
	{
		cout << "ERROR: Unable to read the clue file!" << endl;
	}
	else
	{
		fread(&length, sizeof(int), 1, fp);
		fread(&_room_name, length, 1, fp);

		fread(&_position_num, sizeof(int), 1, fp);

		fread(&length, sizeof(int), 1, fp);
		fread(&_clue_name, length, 1, fp);

		fread(&_start_scene_up, sizeof(int), 1, fp);
		fread(&_end_scene_up, sizeof(int), 1, fp);
		fread(&_start_scene_down, sizeof(int), 1, fp);
		fread(&_end_scene_down, sizeof(int), 1, fp);

		/*fread(&_location_row, sizeof(float), 1, fp);
		fread(&_location_col, sizeof(float), 1, fp);
		fread(&_width, sizeof(float), 1, fp);
		fread(&_location_row, sizeof(float), 1, fp);*/

		fread(&length, sizeof(int), 1, fp);
		fread(&_cluebox_img, length, 1, fp);

		fread(&size, sizeof(int), 1, fp);
		_state.resize(size);
		for (int i = 0; i < size; i++)
		{
			fread(&_state[i], sizeof(int), 1, fp);
		}

		fread(&size, sizeof(int), 1, fp);
		_dialog.resize(size);
		for (int i = 0; i < size; i++)
		{
			fread(&length, sizeof(int), 1, fp);
			fread(&_dialog[i], length, 1, fp);
		}

		fread(&size, sizeof(int), 1, fp);
		_2Dimg_path.resize(size);
		for (int i = 0; i < size; i++)
		{
			fread(&length, sizeof(int), 1, fp);
			fread(&_2Dimg_path[i], length, 1, fp);
		}

		fread(&size, sizeof(int), 1, fp);
		_3Dobj_path.resize(size);
		for (int i = 0; i < size; i++)
		{
			fread(&length, sizeof(int), 1, fp);
			fread(&_3Dobj_path[i], length, 1, fp);
		}

		fread(&end, sizeof(int), 1, fp);
		fclose(fp);
		if (end == CLUE_FILE_END)
			cout << "Read clue file " << _clue_name << " succeed!" << endl;
		else
			cout << "ERROR: Read clue file failed!" << endl;
	}
}


/* set_clue: Initial 3D clue by giving some parameters. 
*/

void Clue::set_clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down, float trans_x, float trans_y, float trans_z, float rot_x, float rot_y, float rot_z, float scale)
{
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;


	_trans_x = trans_x;
	_trans_y = trans_y;
	_trans_z = trans_z;
	_rot_x = rot_x;
	_rot_y = rot_y;
	_rot_z = rot_z;
	_scale = scale;


	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	_end_scene_up = end_scene_up;
	_end_scene_down = end_scene_down;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態
}


/* set_clue: Initial 2D clue by giving some parameters.
*
*  obj_corner - 3D space coordinate (need 4 points)
*/

void Clue::set_clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down, vector<Point3f> obj_corner)
{
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	_end_scene_up = end_scene_up;
	_end_scene_down = end_scene_down;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態

	_obj_corner.assign(obj_corner.begin(), obj_corner.end());
}


/* set_clue: Initial near scene clue by giving some parameters.
*
*  coordinate - screen coordinate
*/
void Clue::set_clue(string room_name, int position_num, string clue_name, vector<Point2i> coordinate){
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = NO_3DOBJ_PATH; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = SHOW_ON_SCENE;		//線索狀態

	_2DCoordinate.assign(coordinate.begin(), coordinate.end());
}



/*void Clue::set_clue(string room_name, int position_num, string clue_name, int start_scene_up, int end_scene_up, int start_scene_down, int end_scene_down)
{
	_room_name = room_name;
	_position_num = position_num;
	_clue_name = clue_name;

	
	//_row_shift = 0.4;
	//_col_shift = 0.05;
	//_location_row = row;
	//_location_col = column;
	//_width = width;
	//_height = height;
	

	_start_scene_up = start_scene_up;
	_start_scene_down = start_scene_down;
	_end_scene_up = end_scene_up;
	_end_scene_down = end_scene_down;

	_current_dialog = 0; 	//目前使用到哪一個對話
	_dialog.clear();
	_current_2Dimg = 0; 	//目前使用到哪一個2D image
	_2Dimg_path.clear();
	_current_3Dobj = 0; 	//目前使用到哪一個3D obj
	_3Dobj_path.clear();

	_cluebox_img = "no path";

	_state.clear();			//紀錄每個state是什麼代號
	_current_state = 0;		//線索狀態
}*/


/* set_clue: Initial clue by giving a path of a clue file. 
*/

int Clue::set_clue(string clue_path)
{
	char path[1000] = {0};
	sprintf(path, "%s", clue_path);
	int length = 0, size = 0, end;

	FILE *fp = fopen(path, "rb");
	if (!fp)
	{
		cout << "ERROR: Unable to read the clue file!" << endl;
		return -1;
	}
	
	fread(&length, sizeof(int), 1, fp);
	fread(&_room_name, length, 1, fp);

	fread(&_position_num, sizeof(int), 1, fp);

	fread(&length, sizeof(int), 1, fp);
	fread(&_clue_name, length, 1, fp);

	fread(&_start_scene_up, sizeof(int), 1, fp);
	fread(&_end_scene_up, sizeof(int), 1, fp);
	fread(&_start_scene_down, sizeof(int), 1, fp);
	fread(&_end_scene_down, sizeof(int), 1, fp);

	/*fread(&_location_row, sizeof(float), 1, fp);
	fread(&_location_col, sizeof(float), 1, fp);
	fread(&_width, sizeof(float), 1, fp);
	fread(&_height, sizeof(float), 1, fp);*/

	fread(&length, sizeof(int), 1, fp);
	fread(&_cluebox_img, length, 1, fp);

	fread(&size, sizeof(int), 1, fp);
	_state.resize(size);
	for (int i = 0; i < size; i++)
	{
		fread(&_state[i], sizeof(int), 1, fp);
	}

	fread(&size, sizeof(int), 1, fp);
	_dialog.resize(size);
	for (int i = 0; i < size; i++)
	{
		fread(&length, sizeof(int), 1, fp);
		fread(&_dialog[i], length, 1, fp);
	}

	fread(&size, sizeof(int), 1, fp);
	_2Dimg_path.resize(size);
	for (int i = 0; i < size; i++)
	{
		fread(&length, sizeof(int), 1, fp);
		fread(&_2Dimg_path[i], length, 1, fp);
	}

	fread(&size, sizeof(int), 1, fp);
	_3Dobj_path.resize(size);
	for (int i = 0; i < size; i++)
	{
		fread(&length, sizeof(int), 1, fp);
		fread(&_3Dobj_path[i], length, 1, fp);
	}

	fread(&end, sizeof(int), 1, fp);
	fclose(fp);
	if (end == CLUE_FILE_END)
	{
		cout << "Read clue file " << _clue_name << " succeed!" << endl;
		return 1;
	}
	else
	{
		cout << "ERROR: Read clue file failed!" << endl;
		return -1;
	}
}


/* ---------------- Setting basic information of the clue. ----------------*/

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


void Clue::set_start_scene_up(int i)
{
	_start_scene_up = i;
}

void Clue::set_end_scene_up(int i)
{
	_end_scene_up = i;
}

/*int Clue::set_end_scene_up()
{
	if (_start_scene_up == -1)
	{
		cout << "ERROR: Start_scene_up not define yet!" << endl;
		_end_scene_up = -1;
		return -1;
	}

	int scene = _start_scene_up - 1;
	float x = _location_col;

	while (x < 1)
	{
		scene++;
		if (scene == 180) scene = 0;
		x += _col_shift;
	}
	_end_scene_up = scene;
	return 1;
}*/

void Clue::set_start_scene_down(int i)
{
	_start_scene_down = i;
}

void Clue::set_end_scene_down(int i)
{
	_end_scene_down = i;
}

/*int Clue::set_end_scene_down()
{
	if (_start_scene_down == -1)
	{
		cout << "ERROR: Start_scene_down not define yet!" << endl;
		_end_scene_down = -1;
		return -1;
	}

	int scene = _start_scene_down - 1;
	float x = _location_col;

	while (x < 1)
	{
		scene++;
		if (scene == 180) scene = 0;
		x += _col_shift;
	}
	_end_scene_down = scene;
	return 1;
}*/

void Clue::set_obj_corner(Vector<Point3f> obj_corner)
{
	_obj_corner.assign(obj_corner.begin(), obj_corner.end());
}

void Clue::set_2D_coordinate(Vector<Point2i> coordinate){
	_2DCoordinate.assign( coordinate.begin(),coordinate.end());
}



/* ----------------------- Setting clue state. ------------------------*/

int Clue::current_state()
{
	return _current_state;
}

void Clue::next_state(int s)
{
	_current_state = s;
}

/*void Clue::add_state(int state_code)
{
	_state.push_back(state_code);
}*/




/* ---------- Setting image that will be put in the clue box. ------------*/

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




/* ----------------- Setting 2D images of the clue. ---------------------*/

int Clue::current_2Dimg()
{
	return _current_2Dimg;
}

string Clue::current_2Dimg_path()
{
	return _2Dimg_path[_current_2Dimg];
}

void Clue::next_2Dimg(int n)
{
	_current_2Dimg = n;
}

void Clue::add_2Dimg_path(string path)
{
	_2Dimg_path.push_back(path);
}

string Clue::get_2Dimg(int number)
{  	
	if (_2Dimg_path[number][0] == NULL)
	{
		cout << "ERROR: Image" << number << " undefined!" << endl;
		return NULL;
	}
	return _2Dimg_path[number];
}




/* ----------------- Setting 3D objects of the clue. ---------------------*/

int Clue::current_3Dobj()
{
	return _current_3Dobj;
}

string Clue::current_3Dobj_path()
{
	return _3Dobj_path[_current_3Dobj];
}

void Clue::next_3Dobj(int n)
{
	_current_3Dobj = n;
}

void Clue::add_3Dobj_path(string path)
{
	_3Dobj_path.push_back(path);
	_current_3Dobj = 0;
}

string Clue::get_3Dobj(int number)
{
	if (_3Dobj_path[number][0] == NULL)
	{
		cout << "ERROR: Image" << number << " undefined!" << endl;
		return NULL;
	}
	return _3Dobj_path[number];
}




/* ----------------- Setting dialogs of the clue. ---------------------*/

string Clue::current_dialog()
{
	return _dialog[_current_dialog];
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




/* ----------------- Get basic information of the clue. ---------------------*/

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

		if (_start_scene_up == -1)
		{
			
			return 0;
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
		if (_start_scene_down == -1)
		{

			return 0;
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

/*float Clue::location_row_now(int vertical, int scene_now)
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

float Clue::location_col_now(int vertical, int scene_now)
{
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
}*/



int Clue::start_scene_up()
{
	return _start_scene_up;
}

int Clue::end_scene_up()
{
	return _end_scene_up;
}

int Clue::start_scene_down()
{
	return _start_scene_down;
}

int Clue::end_scene_down()
{
	return _end_scene_down;
}

float Clue::trans_x()
{
	return _trans_x;
}

float Clue::trans_y()
{
	return _trans_y;
}

float Clue::trans_z()
{
	return _trans_z;
}

float Clue::rot_x()
{
	return _rot_x;
}

float Clue::rot_y()
{
	return _rot_y;
}

float Clue::rot_z()
{
	return _rot_z;
}

float Clue::scale()
{
	return _scale;
}

Vector<Point2i> Clue::get_2D_coordinate()
{
	return _2DCoordinate;
}


Vector<Point3f> Clue::obj_corner()
{
	return _obj_corner;
}


void Clue::_show_animation() 
{
	printf("_show_animation\n");
}




/* ------------ Write the data into a file named by the clue name. ----------------*/

int Clue::write_initial_file()
{
	char path[1000] = {0};
	int length, end = CLUE_FILE_END;
	sprintf(path, "D:\\clue\\%s\\position%d\\%s", &_room_name, _position_num, &_clue_name);
	cout << path << endl;

	FILE *fp = fopen(path, "wb");
	if (!fp)
	{
		cout << "ERROR: Unable to open the clue file!" << endl;
		return -1;
	}

	length = sizeof(_room_name);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&_room_name, sizeof(_room_name), 1, fp);

	fwrite(&_position_num, sizeof(int), 1, fp);

	length = sizeof(_clue_name);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&_clue_name, sizeof(_clue_name), 1,fp);

	fwrite(&_start_scene_up, sizeof(int), 1, fp);
	fwrite(&_end_scene_up, sizeof(int), 1, fp);
	fwrite(&_start_scene_down, sizeof(int), 1, fp);
	fwrite(&_end_scene_down, sizeof(int), 1, fp);

	/*fwrite(&_location_row, sizeof(float), 1, fp);
	fwrite(&_location_col, sizeof(float), 1, fp);
	fwrite(&_width, sizeof(float), 1, fp);
	fwrite(&_height, sizeof(float), 1, fp);*/

	length = sizeof(_cluebox_img);
	fwrite(&length, sizeof(int), 1, fp);
	fwrite(&_cluebox_img, sizeof(_cluebox_img), 1, fp);

	length = _state.size();
	fwrite(&length, sizeof(int), 1, fp);
	for (int i = 0; i < _state.size(); i++)
	{
		fwrite(&_state[i], sizeof(int), 1, fp);
	}

	length = _dialog.size();
	fwrite(&length, sizeof(int), 1, fp);
	for (int i = 0; i < _dialog.size(); i++)
	{
		length = sizeof(_dialog[i]);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&_dialog[i], sizeof(_dialog[i]), 1, fp);
	}

	length = _2Dimg_path.size();
	fwrite(&length, sizeof(int), 1, fp);
	for (int i = 0; i < _2Dimg_path.size(); i++)
	{
		length = sizeof(_2Dimg_path[i]);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&_2Dimg_path[i], sizeof(_2Dimg_path[i]), 1, fp);
	}

	length = _3Dobj_path.size();
	fwrite(&length, sizeof(int), 1, fp);
	for (int i = 0; i < _3Dobj_path.size(); i++)
	{
		length = sizeof(_3Dobj_path[i]);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&_3Dobj_path[i], sizeof(_3Dobj_path[i]), 1, fp);
	}

	fwrite(&end, sizeof(int), 1, fp);
	fclose(fp);
	return 1;
}


ostream& operator<<(ostream& os, const Clue& clue)
{
	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
	os << "name = " << clue._clue_name << "\n"\
		"_current_state = " << clue._current_state << "\n" << endl;

	return os;
}