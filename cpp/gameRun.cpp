#include <stdio.h>
#include <math.h>

#include "glut.h"
#include "..\..\..\..\RoomEscape\h\glm.h"

#include <opencv2/contrib/contrib.hpp> 
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include "..\..\..\..\RoomEscape\h\ClueBox.h"
#include "..\..\..\..\RoomEscape\h\DrawImage.h"

#include <time.h>

using namespace cv;
using namespace std;

#define G_PI 3.14159265358979323846f
int width = 1080;      //Width of the background in pixels.
int height = 720;     //Height of the background in pixels.		
vector<GLuint>list_id;
Mat background;
GLMmodel *glm_model;
float theta = 2.1208;
float phi = 1.5292;
float OBJ_x = 0, OBJ_y = 0;
ClueBox clueBox(0, width, 100, 100, 100);
vector<Clue>ClueOnScreen;
vector<Clue>AllClue;
int q = 0;


Mat clueBox_text;
#define RADPERDEG 0.0174533



void showDialog(const char *text, int length){
	glColor3f(0, 0, 0);
	glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
	double matrix[16]; // 16 doubles in stack memory
	glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
	glLoadIdentity(); // reset PROJECTION matrix to identity matrix
	glOrtho(0, width, 0, height, -5, 5); // orthographic perspective
	glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
	glLoadIdentity(); // reset it to identity matrix
	glPushMatrix(); // push current state of MODELVIEW matrix to stack
	glLoadIdentity(); // reset it again. (may not be required, but it my convention)
	glRasterPos2i(width*0.065, height*0.29); // raster position in 2D
	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
	}
	glPopMatrix(); // get MODELVIEW matrix value from stack
	glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
	glLoadMatrixd(matrix); // reset
	glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW

	// draw 透明框框
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

	glBegin(GL_QUADS);
	glColor4f(0.62, 0.6, 0.55, 0.7);
	glVertex3f(-0.9, -0.5, 0.0);
	glVertex3f(-0.9, -0.5+(150.0/height), 0.0);
	glVertex3f(-0.9 + (length + 2)*(24.0 / width), -0.5 + (150.0 / height), 0.0);
	glVertex3f(-0.9 + (length + 2)*(24.0 / width), -0.5, 0.0);
	glEnd();
	//Printw

}





GLuint drawObject(GLMmodel *glm_model, char *path, GLfloat trans_x, GLfloat trans_y, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale){

	glm_model = glmReadOBJ(path);

	glmUnitize(glm_model);

	glmScale(glm_model, .1);
	glmTranslate(glm_model, trans_x, trans_y, 0);
	glmRotation(glm_model, 0, rot_x);
	glmRotation(glm_model, 1, rot_y);
	glmRotation(glm_model, 2, rot_z);

	clock_t drawObj_start, drawObj_end;
	drawObj_start = clock();
	glmFacetNormals(glm_model);
	glmVertexNormals(glm_model, 90);
	drawObj_end = clock();

	cout << "draw obj time = " << ((double)(drawObj_end - drawObj_start) / CLOCKS_PER_SEC) << "s" << endl;

	return glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);

}


void DrawClueHit(){

	vector<Clue>::iterator it_clue;


	int clue_col, clue_row, clue_width, clue_height;
	for (it_clue = ClueOnScreen.begin(); it_clue != ClueOnScreen.end(); ++it_clue) {

		clue_col = (it_clue->location_col() + 1) / 2 * width;
		clue_row = height - (it_clue->location_row() + 1) / 2 * height;
		clue_width = it_clue->width() / 2 * width;
		clue_height = it_clue->height() / 2 * height;
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND); //Enable blending.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	
		glBegin(GL_QUADS);
		glColor4f(0.5, 0.5, 0.5, 0.5);
		glVertex3f(it_clue->location_col(), it_clue->location_row(), 0.0);
		glColor4f(0.5, 0.5, 0.5, 0.5);
		glVertex3f(it_clue->location_col(), it_clue->location_row() - it_clue->height(), 0.0);
		glColor4f(0.5, 0.5, 0.5, 0.5);
		glVertex3f(it_clue->location_col() + it_clue->width(), it_clue->location_row() - it_clue->height(), 0.0);
		glColor4f(0.5, 0.5, 0.5, 0.5);
		glVertex3f(it_clue->location_col() + it_clue->width(), it_clue->location_row(), 0.0);
		
		glEnd();
	
	}

	



}





void WindowSize(int w, int h)
{
	printf("目前視窗大小為%dX%d\n", w, h);
	width = w;
	height = h;
	glViewport(0, 0, w, h);            //當視窗長寬改變時，畫面也跟著變
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);      //正交投影
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void mouse(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if ((button == 3) || (button == 4)) // It's a wheel event
	{
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
		if (button == 3){

			printf("Scroll %s At %d %d\n", "Up", x, y);
			glmScale(glm_model, 1.5);
			list_id[1] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			glutPostRedisplay();
		}

		else if (button == 4){

			printf("Scroll %s At %d %d\n", "Down", x, y);
			glmScale(glm_model, 1 / 1.5);
			list_id[1] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			glutPostRedisplay();
		}
	}
	else if (state == GLUT_DOWN){  // normal button event
		//printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);


		vector<Clue>::iterator it_clue;

		int clue_col, clue_row, clue_width, clue_height;

		for (it_clue = ClueOnScreen.begin(); it_clue != ClueOnScreen.end(); ++it_clue) {
			clue_col = (it_clue->location_col() + 1) / 2 * width;
			clue_row = height - (it_clue->location_row() + 1) / 2 * height;
			clue_width = it_clue->width() / 2 * width;
			clue_height = it_clue->height() / 2 * height;
			if (x <= clue_col + clue_width && x >= clue_col && y <= clue_row + clue_height && y >= clue_row){

				clueBox.InsertItem(*it_clue);
			}

		}


	}








	glutPostRedisplay();
}






void prepare_lighting()
{
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);

	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };

	float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };

	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 0 };



	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);







}


void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'i':
		q = 1;
		glutPostRedisplay();
		break;

	case 'j':

		glmTranslate(glm_model, -0.02, 0, 0);
		OBJ_x -= 0.02;
		cout << "OBJ_x = " << OBJ_x << endl;
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'k':
		glmTranslate(glm_model, 0, -0.02, 0);
		OBJ_y -= 0.02;
		cout << "OBJ_y = " << OBJ_y << endl;
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'l':
		glmTranslate(glm_model, 0.02, 0, 0);
		OBJ_x += 0.02;
		cout << "OBJ_x = " << OBJ_x << endl;
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'z':
		glmRotation(glm_model, 0, 1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'x':
		glmRotation(glm_model, 0, -1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'c':
		glmRotation(glm_model, 1, 1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'v':
		glmRotation(glm_model, 1, -1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'b':
		glmRotation(glm_model, 2, 1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'n':
		glmRotation(glm_model, 2, -1);
		list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
		glutPostRedisplay();
		break;

	case 'w':
		theta -= .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 's':
		theta += .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 'a':
		phi -= .05;
		prepare_lighting();
		glutPostRedisplay();
		break;

	case 'd':
		phi += .05;
		prepare_lighting();
		glutPostRedisplay();
		break;



	};






}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	clock_t drawObj_start, drawObj_end;
	drawObj_start = clock();
	renderBackgroundGL(background, 0, 0.2, 1, 1); //左下做標(x1,y1)，又上座標(x2,y2)
	drawObj_end = clock();

	cout << "draw back time = " << ((double)(drawObj_end - drawObj_start) / CLOCKS_PER_SEC) << "s" << endl;

	//drawAxes(5);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 0, 1,
		0, 0, 0,
		0, 1, 0);
	GLenum lightSource = GL_LIGHT0;
	float ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	float diffuseLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	const float lightPosition[4] = { 1.0, 0.0, 0.0, 0.0 };

	glEnable(lightSource);
	glLightfv(lightSource, GL_AMBIENT, ambientLight);
	glLightfv(lightSource, GL_DIFFUSE, diffuseLight);
	glLightfv(lightSource, GL_SPECULAR, specularLight);

	/*glPushMatrix();
	glLoadIdentity();
	glLightfv(lightSource, GL_POSITION, lightPosition);
	glPopMatrix();*/
	prepare_lighting();
	glCallList(list_id[0]);
	clock_t drawObj_start1, drawObj_end1;
	drawObj_start1 = clock();
	if (q==0)
	glCallList(list_id[1]);
	drawObj_end1 = clock();
	cout << "call list time = " << ((double)(drawObj_end - drawObj_start) / CLOCKS_PER_SEC) << "s" << endl;

	glCallList(list_id[2]);
	DrawClueHit();
	string text = "andyhahayayaya yoyoyo";
	showDialog(text.data(), text.size());

	clueBox.show_clue_box(clueBox_text);
	clueBox.show_clue(width, height);

	glFlush();

	glutSwapBuffers();






}

void clueSetting(){
	Clue clue1("room", 0, "key", 0, 0, -0.9, 0.9, 0.1, 0.1);//　//room name, position number, clue name, start_scene_up, start_scene_down, 左上角的座標row,左上角的座標column,寬,長
	Clue clue2("room", 0, "bear", 0, 0, -0.5, 0.5, 0.1, 0.1);
	Clue clue3("room", 0, "pillow", 0, 0, 0, 0, 0.1, 0.1);
	clue1.add_img_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\key.obj");
	clue1.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\key1.png");
	clue2.add_img_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\teddy.obj");
	clue2.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\teddy.png");
	clue3.add_img_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\pillow.obj");
	clue3.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\pillow.png");
	AllClue.push_back(clue1);
	AllClue.push_back(clue2);
	AllClue.push_back(clue3);
	ClueOnScreen.push_back(clue1);
	ClueOnScreen.push_back(clue2);
	ClueOnScreen.push_back(clue3);


	list_id.push_back(drawObject(glm_model, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\key.obj", -0.9, 0.9, 0, 0, 0, 1));
	list_id.push_back(drawObject(glm_model, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\teddy.obj", -0.5, 0.5, 0, -90, 0, 1));
	list_id.push_back(drawObject(glm_model, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\pillow.obj", 0, 0, 0, 0, 0, 1));

}

void initializeOpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialise Texture States
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Load background image
	background = imread("D:\\大學\\專題\\RoomEscape\\RoomEscape\\stitch_test4.jpg");
	clueBox_text = imread("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\paper_texture2.png");






	// Set light
	prepare_lighting();

	//clue setting
	clueSetting();



}

void initializeGLUT(int argc, char** argv){

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("RoomEscape");
	initializeOpenGL();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(WindowSize);
	glutMouseFunc(mouse);



}

void gameRun(int argc, char** argv)
{

	initializeGLUT(argc, argv);

	glutMainLoop();




}