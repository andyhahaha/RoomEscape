#include "D:\RoomEscape\h\gameRun.h"

int width = 1080;      //Width of the background in pixels.
int height = 720;     //Height of the background in pixels.		

int scence_num = 0;
Mat background;

GLMmodel *glm_model;
vector<GLuint>list_id;


float theta = -1.0792;
float phi = 1.5292;

ClueBox clueBox(0, width, 100, 100, 100);


int gameState;

vector<Clue> ClueOnScreen;
vector<Clue> ClueInRoom;
vector<Clue> ClueInCloset;
vector<Clue> ClueInDrawer1;
vector<Clue> ClueInDrawer2;
vector<Clue> ClueInDrawer3;
vector<Clue> ClueInBlueShelfTop;
vector<Clue> ClueInBlueShelfMid;
vector<Clue> ClueInBlueShelfBtn;
vector<Clue> ClueInWoodShelf;

vector<Clue> ClueInPillow;
vector<Clue> ClueInCurtain;
vector<Clue> ClueSafeOpen1;
vector<Clue> ClueSafeTypeCode1;

//vector<Clue> AllClue;

Mat clueBox_texture;


int record_x = 0;
int record_y = 0;
int rot_x = 0;
int rot_y = 0;
int rot_z = 0;
int old_rot_x = 0;
int old_rot_y = 0;
int old_rot_z = 0;

float cam_z = 0;

GLint    viewport[4];
GLdouble modelview[16];
GLdouble projection[16];

int mouseState = ROOM;



void clueBoxController(int x)
{
	float horizon_space = SPACE*height ;
	float item_w = ITEM_WIDTH*height ;
	if (x < ARROW_WIDTH*width)
	{
		clueBox.set_item_show_first(0);
		cout << "-" << endl;
	}
	else if (x >width - ARROW_WIDTH*width)
	{
		clueBox.set_item_show_first(1);
		cout << "+" << endl;
	}
	else
	{
		int click = x - (int)(ARROW_WIDTH*width + horizon_space);
		int selected;
		for (selected = 0; click  > 0; selected++)
			click = click - (int)((item_w + horizon_space));

		if (click - (int)(item_w) < 0)
		{
			clueBox.set_item_selected(selected);
			cout << "selected = " << selected << endl;
		}
	}
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

GLuint drawObject(GLMmodel *model, Clue &clue, int obj_num)
{
	char *path = new char[clue.get_3Dobj(obj_num).length() + 1];
	strcpy(path, clue.get_3Dobj(obj_num).c_str());

	model = glmReadOBJ(path);		//read obj file

	glmUnitize(model);				//unitize object to origin and umit cube

	glmScale(model, clue.scale());
	glmTranslate(model, clue.trans_x(), clue.trans_y(), clue.trans_z());
	glmRotation(model, 0, clue.rot_x());
	glmRotation(model, 1, clue.rot_y());
	glmRotation(model, 2, clue.rot_z());
	clue.set_obj_corner(glmPoint(model));

	glmFacetNormals(model);
	//glmVertexNormals(model, 90);

	return glmList(model, GLM_MATERIAL | GLM_SMOOTH);
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
		GLdouble posX, posY, posZ;
		GLdouble  winX, winY, winZ = 0.994;
		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		//glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		cout << "x = " << posX << endl << "y = " << posY << "z = " << posZ << endl;
		

		if (y > height - (SPACE+ITEM_WIDTH)*height&&y < height - SPACE*height)
			clueBoxController(x);
		else
		{
			switch (mouseState)
			{
				case ROOM:
					ClueHit(x, y, ClueOnScreen);
					break;
				case NEARSCENE:
					ClueHitNearScence(x, y, ClueOnScreen);
					break;
			
			}
		}
		
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

	float mat_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
	float light_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
	float ambientLight[4] = { 0.1, 0.1, 0.1, 1.0 };
	float specularLight[4] = { 0.33, 0.33, 0.33, 1.0 };
	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 1 };


	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
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
	
	string finalroom_1_path = "D:\\image\\finalroom\\position1\\stitch\\1_final\\stitch" + to_string(scence_num) + ".jpg";
	string finalroom_2_path = "D:\\image\\finalroom\\position1\\stitch\\2_final\\stitch" + to_string(scence_num) + ".jpg";


	/* draw background*/
	if (mouseState == ROOM)
		background = imread(finalroom_1_path);
	
	renderBackgroundGL(background, 0, 0.2, 1, 1); //左下做標(x1,y1)，又上座標(x2,y2)


	/* perspective mode*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(111, 1, 0.1, 200);	//sight angle, view rate width/height, nearest side, far side
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* set camera sight*/
	gluLookAt(
		2, 0, 0,
		sinf(float(scence_num * 2) / 180 * G_PI)+2, 0, -cosf(float(scence_num * 2) / 180 * G_PI),
		0, 1, 0);


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
	//ClueInRoom.clear();
	vector<Clue>::iterator it_clue;
	/*for (it_clue = ClueInRoom.begin(); it_clue != ClueInRoom.end(); ++it_clue)
	{
		if (it_clue->show_to_scene(VERTICAL_CENTRAL,scence_num))
			ClueOnScreen.push_back(*it_clue);
	}*/

		
	int i;
	if (mouseState == ROOM)
	{
		ClueOnScreen.clear();
		for (it_clue = ClueInRoom.begin(); it_clue != ClueInRoom.end(); ++it_clue)
		{
			if (it_clue->show_to_scene(VERTICAL_CENTRAL, scence_num))
				ClueOnScreen.push_back(*it_clue);
		}

		//ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
		for (i = 0; i < list_id.size(); i++)
		{
			glCallList(list_id[i]);
		}
	}
	cout <<"scence = "<< scence_num << endl;

	/*draw other game interface view*/
	//DrawClueHit();
	//DrawWall();
	string text = "andyha yoyoyo";
	drawDialog(text.data(), text.size(),width,height);
	clueBox.show_clue_box(clueBox_texture);
	clueBox.show_clue(width, height);

	glFlush();
	glutSwapBuffers();
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

	// Load clue box background image
	clueBox_texture = imread("D:\\resource\\paper_texture2.png");

	// Set light
	prepare_lighting();

	//clue setting
	clueSetting();
}

void initializeGLUT(int argc, char** argv)
{
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