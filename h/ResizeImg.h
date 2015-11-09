#ifndef RESIZEIMG_H
#define RESIZEIMG_H

#include <iostream> 
#include <string> 

using namespace std;

extern void image_resize(string& room_name, int position_number,  int vertical_angle, int img_number, int percent);
extern void resize_all(string& room_name, int position_number,  int vertical_angle,int percent);

#endif