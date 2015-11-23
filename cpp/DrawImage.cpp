#include "glut.h"
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "../h/DrawImage.h"

#include <iostream>
using namespace cv;
using namespace std;


GLuint matToTexture(Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter)
{
	// Generate a number for our textureID's unique handle
	GLuint textureID;
	glGenTextures(1, &textureID);

	// Bind to our texture handle
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Catch silly-mistake texture interpolation method for magnification
	if (magFilter == GL_LINEAR_MIPMAP_LINEAR ||
		magFilter == GL_LINEAR_MIPMAP_NEAREST ||
		magFilter == GL_NEAREST_MIPMAP_LINEAR ||
		magFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << endl;
		magFilter = GL_LINEAR;
	}

	// Set texture interpolation methods for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	// Set texture clamping method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

	// Set incoming texture format to:
	// GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
	// GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
	// Work out other mappings as required ( there's a list in comments in main() )
	GLenum inputColourFormat = GL_BGR_EXT;
	if (mat.channels() == 1)
	{
		inputColourFormat = GL_LUMINANCE;
	}

	// Create the texture
	glTexImage2D(GL_TEXTURE_2D,     // Type of texture
		0,                 // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB,            // Internal colour format to convert to
		mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
		mat.rows,          // Image height i.e. 480 for Kinect in standard mode
		0,                 // Border width in pixels (can either be 1 or 0)
		inputColourFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE,  // Image data type
		mat.ptr());        // The actual image data itself

	// If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
	/*if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
	minFilter == GL_LINEAR_MIPMAP_NEAREST ||
	minFilter == GL_NEAREST_MIPMAP_LINEAR ||
	minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
	glGenerateMipmap(GL_TEXTURE_2D);
	}*/

	return textureID;
}



/**
*@ Draws the basic image background image.
*/

void renderBackgroundGL(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	// Make sure that the polygon mode is set so we draw the polygons filled
	// (save the state first so we can restore it).
	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	
	// Set up the virtual camera, projecting using simple ortho so we can draw the background image.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Create a texture (on the first pass only, we will reuse it later) to hold the image we captured.
	static bool textureGenerated = false;
	static GLuint textureId;
	if (!textureGenerated)
	{
		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		textureGenerated = true;
	}

	// Copy the image to the texture.
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size().width, image.size().height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image.data);

	// Draw the image.
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);

	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1, y1, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2, y2, 0.0);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Clear the depth buffer so the texture forms the background.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Restore the polygon mode state.
	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);
}



void CoverObject(const Mat& image, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){//左下座標  右上座標

	// Make sure that the polygon mode is set so we draw the polygons filled
	// (save the state first so we can restore it).
	GLfloat backgroundHeight = 0.8;
	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// Set up the virtual camera, projecting using simple ortho so we can draw the background image.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Create a texture (on the first pass only, we will reuse it later) to hold the image we captured.
	static bool textureGenerated = false;
	static GLuint textureId;
	if (!textureGenerated)
	{
		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		textureGenerated = true;
	}

	// Copy the image to the texture.
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size().width, image.size().height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image.data);

	// Draw the image.
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1, y1, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2, y1, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1, y2, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2, y2, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Clear the depth buffer so the texture forms the background.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Restore the polygon mode state.
	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);
}

/* showDialog: Show dialog box and dialog content.
*
* text - text
* length - length of text string
*/
void drawDialog(const char *text, int length,int width,int height){

	//draw text
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION);					// change the current matrix to PROJECTION
	double matrix[16];								// 16 doubles in stack memory
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);		// get the values from PROJECTION matrix to local variable
	glLoadIdentity();								// reset PROJECTION matrix to identity matrix
	glOrtho(0, width, 0, height, -5, 5);			// orthographic perspective
	glMatrixMode(GL_MODELVIEW);						// change current matrix to MODELVIEW matrix again
	glLoadIdentity();								// reset it to identity matrix
	glPushMatrix();									// push current state of MODELVIEW matrix to stack
	glLoadIdentity();								// reset it again. (may not be required, but it my convention)
	glRasterPos2i(width*0.065, height*0.29);		// raster position in 2D

	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
	}



	// Make sure that the polygon mode is set so we draw the polygons filled
	// (save the state first so we can restore it).

	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);

	// Set up the virtual camera, projecting using simple ortho so we can draw the background image.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw the image.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);								//Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

	glBegin(GL_QUADS);
	glColor4f(0.62, 0.6, 0.55, 0.7);
	glVertex3f(0.05, 0.25, 0.0);
	glVertex3f(0.05 + (length + 2)*(12.0 / width), 0.25, 0.0);
	glVertex3f(0.05 + (length + 2)*(12.0 / width), 0.25 + (75.0 / height), 0.0);
	glVertex3f(0.05, 0.25 + (75.0 / height), 0.0);
	glEnd();

	// Clear the depth buffer so the texture forms the background.
	glClear(GL_DEPTH_BUFFER_BIT);

	// Restore the polygon mode state.
	glPolygonMode(GL_FRONT, polygonMode[0]);
	glPolygonMode(GL_BACK, polygonMode[1]);






}


/* DrawWall: Draw four virtual wall to pretend room wall.
*
*/

void DrawWall(){
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

	//front red wall
	glBegin(GL_QUADS);
	glColor4f(0.9, 0.0, 0.0, 0.5);
	glVertex3f(-2.2 * DIST, 4 * DIST + OFFSET, -3 * DIST);
	glVertex3f(2.2 * DIST, 4 * DIST + OFFSET, -3 * DIST);
	glVertex3f(2.2 * DIST, -2 * DIST + OFFSET, -3 * DIST);
	glVertex3f(-2.2 * DIST, -2 * DIST + OFFSET, -3 * DIST);
	glEnd();

	//back  green wall
	glBegin(GL_QUADS);
	glColor4f(0.0, 0.9, 0.0, 0.5);
	glVertex3f(-2.2 * DIST, 4 * DIST + OFFSET, 3 * DIST);
	glVertex3f(2.2 * DIST, 4 * DIST + OFFSET, 3 * DIST);
	glVertex3f(2.2 * DIST, -2 * DIST + OFFSET, 3 * DIST);
	glVertex3f(-2.2 * DIST, -2 * DIST + OFFSET, 3 * DIST);
	glEnd();

	//right  blue wall
	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.9, 0.5);
	glVertex3f(2.2 * DIST, 4 * DIST + OFFSET, -3 * DIST);
	glVertex3f(2.2 * DIST, 4 * DIST + OFFSET, 3 * DIST);
	glVertex3f(2.2 * DIST, -2 * DIST + OFFSET, 3 * DIST);
	glVertex3f(2.2 * DIST, -2 * DIST + OFFSET, -3 * DIST);
	glEnd();

	//left  yellow wall
	glBegin(GL_QUADS);
	glColor4f(0.9, 0.9, 0.0, 0.5);
	glVertex3f(-2.2 * DIST, 4 * DIST + OFFSET, -3 * DIST);
	glVertex3f(-2.2 * DIST, 4 * DIST + OFFSET, 3 * DIST);
	glVertex3f(-2.2 * DIST, -2 * DIST + OFFSET, 3 * DIST);
	glVertex3f(-2.2 * DIST, -2 * DIST + OFFSET, -3 * DIST);
	glEnd();


}