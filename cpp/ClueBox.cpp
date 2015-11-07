#include <string>
#include <opencv2/contrib/contrib.hpp> 
#include <iostream>
#include "vector"
#include "../h/ClueBox.h"

using namespace cv;
using namespace std;

ClueBox::ClueBox(int number, int width, int height, int item_width, int item_height){	//_clue_number,_box_width,_box_height
	_clue_number = number;
	_box_width = width;
	_box_height = height;
	_item_width = item_width;
	_item_height = item_height;
	_item_selected = 0;
}


void ClueBox::set_box_width(int width){
	_box_width = width;
}
void ClueBox::set_box_height(int height){
	_box_height = height;
}
void ClueBox::set_item_width(int width){
	_item_width = width;
}
void ClueBox::set_item_height(int height){
	_item_height = height;
}
void ClueBox::set_item_selected(int index){
	_item_selected = index;
}


int ClueBox::get_clue_number(){
	_clue_number = _clue_vector.size();
	return _clue_number;
}
int ClueBox::get_box_width(){
	return _box_width;
}
int ClueBox::get_box_height(){
	return _box_height;
}
int ClueBox::get_item_width(){
	return _item_width;
}
int ClueBox::get_item_height(){
	return _item_height;
}
int ClueBox::get_item_selected(){
	return _item_selected;
}


void ClueBox::show_clue_box(Mat image){	//用clue array裡面存的clue選圖出來show
	printf("show_clue_box\n");
	Mat image1 = imread("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\key.png");

	//glEnable(GL_BLEND); //Enable blending.
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	renderBackgroundGL(image,0,0,1,0.2);





}
void ClueBox::InsertItem(Clue clue){

	_clue_vector.push_back(clue);
	_clue_number = sizeof(_clue_vector) / sizeof(_clue_vector[0]);

}
void ClueBox::DelItem(int index){
	vector< Clue >::iterator itor;
	itor = _clue_vector.begin() + index - 1;
	_clue_vector.erase(itor);
	_clue_number = sizeof(_clue_vector) / sizeof(_clue_vector[0]);
}
void ClueBox::show_clue(){
	
	vector<Clue>::iterator it_i;

	int i = 1;
	for (it_i = _clue_vector.begin(); it_i != _clue_vector.end(); ++it_i){
		renderBackgroundGL(it_i->get_cluebox_img(), i*HORIZON_SPACE + (i-1)*ITEM_WIDTH, VERTICAL_SPACE, i*HORIZON_SPACE + i*ITEM_WIDTH, VERTICAL_SPACE + ITEM_HEIGHT);
	}
}



ostream& operator<<(ostream& os, const ClueBox& cluebox)
{
	int _clue_number;
	int _box_width;
	int _box_height;
	int _item_width;
	int _item_height;
	int _item_selected;
	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
	os << "_clue_number = " << cluebox._clue_number << "\n"\
		"_box_width = " << cluebox._box_width << "\n"\
		"_box_height = " << cluebox._box_height << "\n"\
		"_item_width = " << cluebox._item_width << "\n"\
		"_item_height = " << cluebox._item_height << "\n"\
		"_item_selected = " << cluebox._item_selected << "\n" << endl;

	return os;
}
