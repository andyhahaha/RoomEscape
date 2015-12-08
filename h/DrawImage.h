#ifndef _DRAWIMAGE_H_
#define _DRAWIMAGE_H_

#include "glut.h"
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "D:\RoomEscape\h\Define.h"
#include <string>
#include <iostream>
using namespace cv;


extern GLuint matToTexture(Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);
extern void renderBackgroundGL(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern void CoverObject(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern void drawDialog(const char *text, int length, int width, int height);
extern void DrawWall();
extern void DrawClueHit(vector<Point3f> corner);
#endif