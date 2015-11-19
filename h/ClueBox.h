#ifndef _CLUEBOX_H_
#define _CLUEBOX_H_
#include <string>
#include <opencv2/contrib/contrib.hpp> 
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>
#include "glut.h"
#include "Clue.h"
#include "DrawImage.h"
#include "Define.h"

using namespace cv;
using namespace std;


class ClueBox {
public:
	ClueBox();
	ClueBox(int, int, int, int, int);	//_clue_number,_box_width,_box_height,_item_width,_item_height

	void show_clue_box(Mat);	//用clue array裡面存的clue選圖出來show
	void InsertItem(Clue);
	void DelItem(int);
	void show_clue(int, int);
	void set_box_width(int);
	void set_box_height(int);
	void set_item_width(int);
	void set_item_height(int);
	void set_item_selected(int);
	void set_item_show_first(int);
	void set_item_show_last(int);


	int get_clue_number();
	int get_box_width();
	int get_box_height();
	int get_item_width();
	int get_item_height();
	int get_item_selected();

	friend ostream& operator<<(ostream&, const ClueBox&);

private:
	int _clue_number;
	int _box_width;
	int _box_height;
	int _item_width;
	int _item_height;
	int _item_selected;	//0沒有項目被選	1~n 第n項目被選
	int _item_show_first;
	int _item_show_last;
	//Clue *_clue_array = new Clue[_clue_number];
	vector<Clue>_clue_vector;



};

#endif