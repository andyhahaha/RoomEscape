#include <stdio.h>
#include <math.h>
#include <iostream>
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
float theta = -1.0792;
float phi = 1.5292;
float OBJ_x = 0, OBJ_y = 0;
ClueBox clueBox(0, width, 100, 100, 100);
vector<Clue>ClueOnScreen;
vector<Clue>AllClue;
int q = 0;
int scence_num = 0;
float OBJx = 0;

Mat clueBox_text;
#define RADPERDEG 0.0174533

int record_x = 0;
int record_y = 0;

int rot_x = 0;
int rot_y = 0;
int rot_z = 0;
int old_rot_x = 0;
int old_rot_y = 0;
int old_rot_z = 0;
#define dist 5
#define offset 1.5
float cam_z = 0;

GLint    viewport[4];
GLdouble modelview[16];
GLdouble projection[16];










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
	glVertex3f(-2.2 * dist, 4 * dist + offset, -3 * dist);
	glVertex3f(2.2 * dist, 4 * dist + offset, -3 * dist);
	glVertex3f(2.2 * dist, -2 * dist + offset, -3 * dist);
	glVertex3f(-2.2 * dist, -2 * dist + offset, -3 * dist);
	glEnd();

	//back  green wall
	glBegin(GL_QUADS);
	glColor4f(0.0, 0.9, 0.0, 0.5);
	glVertex3f(-2.2 * dist, 4 * dist + offset, 3 * dist);
	glVertex3f(2.2 * dist, 4 * dist + offset, 3 * dist);
	glVertex3f(2.2 * dist, -2 * dist + offset, 3 * dist);
	glVertex3f(-2.2 * dist, -2 * dist + offset, 3 * dist);
	glEnd();

	//right  blue wall
	glBegin(GL_QUADS);
	glColor4f(0.0, 0.0, 0.9, 0.5);
	glVertex3f(2.2 * dist, 4 * dist + offset, -3 * dist);
	glVertex3f(2.2 * dist, 4 * dist + offset, 3 * dist);
	glVertex3f(2.2 * dist, -2 * dist + offset, 3 * dist);
	glVertex3f(2.2 * dist, -2 * dist + offset, -3 * dist);
	glEnd();

	//left  yellow wall
	glBegin(GL_QUADS);
	glColor4f(0.9, 0.9, 0.0, 0.5);
	glVertex3f(-2.2 * dist, 4 * dist + offset, -3 * dist);
	glVertex3f(-2.2 * dist, 4 * dist + offset, 3 * dist);
	glVertex3f(-2.2 * dist, -2 * dist + offset, 3 * dist);
	glVertex3f(-2.2 * dist, -2 * dist + offset, -3 * dist);
	glEnd();


}



/* drawObject: Return 3D object in glmLIst.
*
* glm_model - 3D object model.
* path - path of obj file.
* trans_x - translation in x axis way.
* trans_y - translation in y axis way.
* trans_z - translation in z axis way.
* rot_x - rotate object along x axis by a given amount.
* rot_y - rotate object along y axis by a given amount.
* rot_z - rotate object along z axis by a given amount.
* scale - scalefactor.
*
*/

GLuint drawObject(GLMmodel *model, Clue &clue, char *path, GLfloat trans_x, GLfloat trans_y, GLfloat trans_z, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z, GLfloat scale){

	model = glmReadOBJ(path);				//read obj file

	glmUnitize(model);						//unitize object to origin and umit cube

	glmScale(model, scale);
	glmTranslate(model, trans_x, trans_y, trans_z);
	glmRotation(model, 0, rot_x);
	glmRotation(model, 1, rot_y);
	glmRotation(model, 2, rot_z);
	clue.set_obj_corner(glmPoint(model));

		
	glmFacetNormals(model);
	glmVertexNormals(model, 90);

	return glmList(model, GLM_MATERIAL | GLM_SMOOTH);

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


void ClueHit(int x, int y){
	vector<Clue>::iterator it_clue;

	
	GLdouble  winX, winY, winZ;
	GLdouble posX, posY, posZ;
	int screenX, screenY;
	int maxX=-10000, minX=10000, maxY=-10000, minY=10000;
	int i;
	//glGetIntegerv(GL_VIEWPORT, viewport);
	//glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	//glGetDoublev(GL_PROJECTION_MATRIX, projection);


	for (it_clue = ClueOnScreen.begin(); it_clue != ClueOnScreen.end(); ++it_clue) {
		maxX = -10000;
		minX = 10000;
		maxY = -10000;
		minY = 10000;
		for (i = 0; i < 8; i++){
			posX = it_clue->obj_corner()[i].x;
			posY = it_clue->obj_corner()[i].y;
			posZ = it_clue->obj_corner()[i].z;
			gluProject(posX, posY, posZ, modelview, projection, viewport, &winX, &winY, &winZ);
			screenX = winX;
			screenY = viewport[3] - (float)winY;
			if (maxX < screenX)
				maxX = screenX;
			if (maxY < screenY)
				maxY = screenY;
			if (minX > screenX)
				minX = screenX;
			if (minY > screenY)
				minY = screenY;
		}
		if (minX < 0)
			minX = width + 1;
		if (minY < 0)
			minY = height + 1;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "clue = " << it_clue->clue_name() << endl;
		cout << "maxX = " << maxX << endl;
		cout << "minX = " << minX << endl;
		cout << "maxY = " << maxY << endl;
		cout << "minY = " << minY << endl;
		

		if (x <= maxX && x >= minX && y <= maxY && y >=minY){

			clueBox.InsertItem(*it_clue);
			cout << "~~~~~~~~~~~~~~~~~~Insert clue = " << it_clue->clue_name() << endl;
		}
	}
}



/* WindowSize: Drawback function return winndow size.
*
* w - window width.
* h - window height.
*/

void WindowSize(int w, int h)
{
	printf("目前視窗大小為%dX%d\n", w, h);
	width = w;
	height = h;
	glViewport(0, 0, w, h);            //當視窗長寬改變時，畫面也跟著變
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -10, 10);      //正交投影
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/* mouse: Process mouse event.
*
* button - button pressed
* state - press state
* x - click coordinate x.
* y - click coordinate y.
*/

void mouse(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if ((button == 3) || (button == 4)) // It's a wheel event
	{
		// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
		if (button == 3)
		{
			printf("Scroll %s At %d %d\n", "Up", x, y);
			cam_z -= 0.5;
			glutPostRedisplay();
		}
		else if (button == 4)
		{
			printf("Scroll %s At %d %d\n", "Down", x, y);			
			cam_z += 0.5;
			glutPostRedisplay();
		}
	}
	else if (state == GLUT_DOWN)	// normal button event
	{  
		printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
		glutPostRedisplay();
		ClueHit(x,y);
	}

	if (state)
	{
		record_x += x - old_rot_x;
		record_y += y - old_rot_y;

		rot_x = 0;   //沒有歸零會有不理想的結果 
		rot_y = 0;
	}
	else
	{
		old_rot_x = x;
		old_rot_y = y;
	}

	glutPostRedisplay();
}


/* MotionMouse: Processed mouse motion.
*
* x - click coordinate x.
* y - click coordinate y.
*/

void MotionMouse(int x, int y)
{
	rot_x = x - old_rot_x;
	rot_y = y - old_rot_y;

	glutPostRedisplay();
}


/* prepare_lighting: Processed mouse motion.
*
*/

void prepare_lighting()
{
	theta = fmodf(theta, 2 * G_PI);
	phi = fmodf(phi, 2 * G_PI);
	//cout << "theta = " << theta << endl;
	//cout << "phi = " << phi << endl;
	//GLenum lightSource = GL_LIGHT0;

	//glEnable(lightSource);

	float mat_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float light_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float ambientLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	float specularLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 1 };


	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);
}

/* keyboard: Processed keyboard signal.
*
* key - key value.
* x - click coordinate x.
* y - click coordinate y.
*/

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'i':
		
		break;

	case 'j':

		scence_num--;
		if (scence_num < 0)
			scence_num = 179;
		
		glutPostRedisplay();
		break;

	case 'k':
		
		break;

	case 'l':
		scence_num++;
		if (scence_num > 179)
			scence_num = 0;
		

		glutPostRedisplay();
		break;

	case 'z':
		
		glutPostRedisplay();
		break;

	case 'x':
		
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

/* display: display all views on screen.
*
*/

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/* draw background*/
	background = imread("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\scence\\final\\stitch" + to_string(scence_num) + ".jpg");
	renderBackgroundGL(background, 0, 0.2, 1, 1); //左下做標(x1,y1)，又上座標(x2,y2)


	/* perspective mode*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(115, 1, 0.1, 200);	//sight angle, view rate width/height, nearest side, far side
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* set camera sight*/
	gluLookAt(
		0, 0, cam_z,
		sinf(float(scence_num * 2) / 180 * G_PI), 0, -cosf(float(scence_num * 2) / 180 * G_PI),
		0, 1, 0);
	//cout << "cam_z = " << cam_z << endl;

	/* rotate all 3D models*/
	//glRotatef((float)rot_y + (float)record_y, 1.0, 0.0, 0.0);//上下滑  以x軸當旋轉軸 
	//glRotatef((float)rot_x + (float)record_x, 0.0, 1.0, 0.0);//左右滑  以y軸當旋轉軸 

	/* convert opengl coordinate to screen coordinate*/

	GLdouble  winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	
	/*light*/
	prepare_lighting();

	/*draw 3D models by call list*/
	glCallList(list_id[0]);
	glCallList(list_id[1]);
	glCallList(list_id[2]);


	/*draw other game interface view*/
	DrawClueHit();
	DrawWall();
	string text = "andyha yoyoyo";
	drawDialog(text.data(), text.size(),width,height);
	clueBox.show_clue_box(clueBox_text);
	clueBox.show_clue(width, height);

	glFlush();
	glutSwapBuffers();
}



/*set clue */
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
	

	list_id.push_back(drawObject(glm_model,clue1, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\key.obj", -2*dist, 1*dist, -3*dist , 0, 0, 0, 1.0));
	list_id.push_back(drawObject(glm_model, clue2, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\teddy.obj", -0.5*dist, 0.5*dist, -3 * dist, 0, 90, 0, 2.0));
	list_id.push_back(drawObject(glm_model, clue3, "D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\pillow.obj", 0, 0, -3 * dist, 0, 0, 0, 10.0));
	ClueOnScreen.push_back(clue1);
	ClueOnScreen.push_back(clue2);
	ClueOnScreen.push_back(clue3);
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
	glutMotionFunc(MotionMouse);

}

void gameRun(int argc, char** argv)
{
	initializeGLUT(argc, argv);
	glutMainLoop();
}


/*clock_t drawObj_start, drawObj_end;
drawObj_start = clock();

drawObj_end = clock();

cout << "draw back time = " << ((double)(drawObj_end - drawObj_start) / CLOCKS_PER_SEC) << "s" << endl;


*/