#ifndef _DRAWIMAGE_H_
#define _DRAWIMAGE_H_

#include "glut.h"
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/highgui/highgui.hpp"

#include <string>
#include <iostream>
using namespace cv;


extern GLuint matToTexture(Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);
extern void renderBackgroundGL(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
//void drawObject(GLMmodel *glm_model, string path, GLfloat trans_x, GLfloat trans_y, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale);
extern void CoverObject(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

#endif