#include "D:\RoomEscape\h\gameRun.h"

int width = 1080;      //Width of the background in pixels.
int height = 720;     //Height of the background in pixels.		

int scene_num = 0;
int scene_temp = 0;

Mat background;

GLMmodel *glm_model;
vector<GLuint>list_id;
vector<int>list_id_show;

float theta = -1.0792;
float phi = 1.5292;

ClueBox clueBox(0, width, 100, 100, 100);


//int gameState = STATE1;


vector<Clue> ClueOnScreen;

vector<Clue> ClueInStory;
vector<Clue> ClueInRoom;
vector<Clue> ClueInCloset;
vector<Clue> ClueInClosetClosed;
vector<Clue> ClueInClosetOpen;
vector<Clue> ClueInPillow;
vector<Clue> ClueInCurtainClosed;
vector<Clue> ClueInCurtainOpened;
vector<Clue> ClueInClosetInside;

vector<Clue> ClueInDrawer1;
vector<Clue> ClueInDrawer2;
vector<Clue> ClueInDrawer3;

vector<Clue> ClueBookInside;
vector<Clue> ClueInBlueShelfMid;
vector<Clue> ClueInBlueShelfBtm;

vector<Clue> ClueInOrangeShelfTop;
vector<Clue> ClueInOrangeShelfMid;
vector<Clue> ClueInOrangeShelfBtm;

vector<Clue> ClueInGreenShelfTop;
vector<Clue> ClueInGreenShelfMid;
vector<Clue> ClueInGreenShelfBtm;

vector<Clue> ClueInWoodShelf;
vector<Clue> ClueInWoodShelfTop;
vector<Clue> ClueInWoodShelfMid;
vector<Clue> ClueInWoodShelfBtm;

vector<Clue> ClueInPaint;
vector<Clue> ClueInBoat;

vector<Clue> ClueSafeOpen1;
vector<Clue> ClueSafeTypeCode1;

//vector<Clue> AllClue;

Mat clueBox_texture;


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

int sight = VERTICAL_CENTRAL;

int mouseState = NEARSCENE;
int Ismove = 0;

void display();


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
			if (selected <= clueBox.get_clue_number()){
				clueBox.set_item_selected(selected - 1);
				cout << "selected = " << selected - 1 << endl;
			}
		}
	}
	glutPostRedisplay();

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
	glmVertexNormals(model, 90);

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
		//if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
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
	else if (button == 0&& state == GLUT_UP)	// normal button event
	{  
		if (Ismove == 0)
		{
			printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
			//glutPostRedisplay();
			GLdouble posX, posY, posZ;
			GLdouble  winX, winY, winZ = 0.994;
			winX = (float)x;
			winY = (float)viewport[3] - (float)y;
			//glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
			cout << "x = " << posX << endl << "y = " << posY << endl<<"z = " << posZ << endl;


			if (y > height - (SPACE + ITEM_WIDTH)*height&&y < height - SPACE*height)
				clueBoxController(x);
			else
			{
				switch (mouseState)
				{
				case ROOM:
					ClueHit(x, y, ClueOnScreen);
					break;
				case NEARSCENE:
				case TYPECODE:
				case BOOKINSIDE:
					ClueHitNearScence(x, y, ClueOnScreen);
					break;
				}
			}
		}
	}
	else if (button == 2 && state == GLUT_UP){
		if (Ismove == 0 && mouseState==ROOM){
			if (sight == VERTICAL_CENTRAL)
				sight = VERTICAL_DOWN_20;
			else
				sight = VERTICAL_CENTRAL;
			glutPostRedisplay();
		}
	}

	Ismove = 0;
	if (mouseState == ROOM)
	{
		if (state == GLUT_UP)
		{
			rot_x = 0;   //沒有歸零會有不理想的結果 
			rot_y = 0;
			scene_temp = scene_num;
		}
		else if (state == GLUT_DOWN)
		{
			old_rot_x = x;
			old_rot_y = y;
			scene_temp = scene_num;
		}
	}
	//glutPostRedisplay();
}


/* MotionMouse: Processed mouse motion.
*
* x - click coordinate x.
* y - click coordinate y.
*/

void MotionMouse(int x, int y)
{

	Ismove = 1;
	if (mouseState == ROOM)
	{
		rot_x = x - old_rot_x;
		rot_y = y - old_rot_y;

		scene_num = -rot_x / (width*0.01) + scene_temp;

		if (scene_num >= 180)
		{
			scene_num %= 180;
		}
		else if (scene_num < 0)
		{
			while (scene_num < 0)
				scene_num += 180;
		}
		//glutPostRedisplay();
		display();
	}
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

	//float mat_diffuse[4] = { 1, 1, 1, 1.0 };
	float light_diffuse[4] = { 1, 1, 1, 1.0 };
	float ambientLight[4] = { 1, 1, 1, 1.0 };
	float specularLight[4] = { 1, 1, 1, 1.0 };
	//	float light_position[4] = { sinf(theta) * cosf(phi), cosf(theta), -sinf(theta) * sinf(phi), 1 };
	float light_position[4] = { 0,0,1,1 };


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
			sight = VERTICAL_CENTRAL;
			break;

		case 'j':
			scene_num--;
			if (scene_num < 0)
				scene_num = 179;
		
			break;

		case 'k':
			sight = VERTICAL_DOWN_20;
			break;

		case 'l':
			scene_num++;
			if (scene_num > 179)
				scene_num = 0;
		
			break;

		case 'z':
			break;

		case 'x':
			break;

		case 'c':
			glmRotation(glm_model, 1, 1);
			list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			break;

		case 'v':
			glmRotation(glm_model, 1, -1);
			list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			break;

		case 'b':
			glmRotation(glm_model, 2, 1);
			list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			break;

		case 'n':
			glmRotation(glm_model, 2, -1);
			list_id[2] = glmList(glm_model, GLM_MATERIAL | GLM_SMOOTH);
			break;

		case 'w':
			theta -= .05;
			prepare_lighting();
			break;

		case 's':
			theta += .05;
			prepare_lighting();
			break;

		case 'a':
			phi -= .05;
			prepare_lighting();
			break;

		case 'd':
			phi += .05;
			prepare_lighting();
			break;
		
	};
	glutPostRedisplay();
}



/* display: display all views on screen.
*
*/

/* display time 2015/12/4 by cindy
*  
*  Room: 
*  display() time: 0.155s
*  draw background time: 0.12s
*  set camera time: 0s
*  draw clue time: 0.003s
*  draw dialog time: 0.001s
*  clue box time: 0.011s
*  
*/

void display()
{
	clock_t display_start, display_end;
	clock_t start1, end1;

	display_start = clock();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	string finalroom_1_path = "D:\\image\\finalroom\\position1\\stitch\\1_small\\stitch" + to_string(scene_num) + ".jpg";
	string finalroom_2_path = "D:\\image\\finalroom\\position1\\stitch\\2_small\\stitch" + to_string(scene_num) + ".jpg";

	
	/* draw background*/
	start1 = clock();

	if (mouseState == ROOM)
	{
		if (sight == VERTICAL_CENTRAL)
			background = imread(finalroom_1_path);
		else
			background = imread(finalroom_2_path);
	}
	

	renderBackgroundGL(background, 0, 0.15, 1, 1); //左下做標(x1,y1)，右上座標(x2,y2)
	end1 = clock();
	cout << "background time = " << ((double)(end1 - start1) / CLOCKS_PER_SEC) << "s" << endl;

	start1 = clock();
	
	
	/* set camera sight*/
	float angle_theta = float(scene_num) * 2 / 180 * G_PI;
	float x_Component = sinf(angle_theta);
	float z_Component = -cosf(angle_theta);
	float y_Component = -0.53;	//-0.53
	float angle_phi = atan2f(-y_Component,1);//0.36397023
	/*float x_normal = sinf(angle_theta)*sinf(angle_phi);
	float z_normal = -cosf(angle_theta)*sinf(angle_phi);
	float y_normal = cosf(angle_phi);*/
	float y_offset = 0;
	//cout << "angle_phi = " << angle_phi << endl;
	//cout << "x_Component = " << x_Component << "z_Component = " << z_Component << endl;
	//cout << "x_normal = " << x_normal << "y_normal = " << y_normal << "z_normal = " << z_normal << endl;
	if (sight == VERTICAL_CENTRAL)
	{
		/* perspective mode*/
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(111, 1, 0.1, 200);	//sight angle, view rate width/height, nearest side, far side
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			0, 0, 0,
			x_Component, 0, z_Component,
			0, 1, 0);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(106, 1, 0.1, 200);  //越大越斜
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			0, 0 + y_offset, 0,
			x_Component, y_Component + y_offset, z_Component,
			/*x_normal, y_normal, z_normal*/0,1,0);
	}
	end1 = clock();
	cout << "set camera time = " << ((double)(end1 - start1) / CLOCKS_PER_SEC) << "s" << endl;

	/* rotate all 3D models*/
	//glRotatef((float)rot_y + (float)record_y, 1.0, 0.0, 0.0);//上下滑  以x軸當旋轉軸 
	//glRotatef((float)rot_x + (float)record_x, 0.0, 1.0, 0.0);//左右滑  以y軸當旋轉軸 

	/* convert opengl coordinate to screen coordinate*/
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	
	/*light*/
	//prepare_lighting();

	/*draw 3D models by call list*/
	start1 = clock();
	vector<Clue>::iterator it_clue;

	if (mouseState == ROOM)
	{
		ClueOnScreen.clear();
		for (it_clue = ClueInRoom.begin(); it_clue != ClueInRoom.end(); ++it_clue)
		{
			if (it_clue->show_to_scene(sight, scene_num) && it_clue->current_state() != NOT_SHOW && it_clue->current_state() != SHOW_IN_CLUEBOX)
				ClueOnScreen.push_back(*it_clue);
		}

		for (int i = 0; i < list_id.size(); i++)
		{
			if (list_id_show[i] != NOT_SHOW && list_id_show[i] != SHOW_IN_CLUEBOX)
				glCallList(list_id[i]);
		}
	}
	int i;
	/*for (i = 0; i < ClueInRoom.size();i++){

		DrawClueHit(ClueInRoom[i].obj_corner());
	}*/



	end1 = clock();
	cout << "clue time = " << ((double)(end1 - start1) / CLOCKS_PER_SEC) << "s" << endl;

	/*draw other game interface view*/
	//DrawWall();


	start1 = clock();
	/* Draw dialog */
	string text;
	string back = "back";

	if (mouseState == TYPECODE)
	{
		drawCode(code);
		drawDialog(back.data(), back.size(), width, height);
	}
	else if (mouseState == BOOKINSIDE)
	{
		drawPageNumber(bookpage);
		drawDialog(back.data(), back.size(), width, height);
	}
	else if (mouseState == NEARSCENE)
	{
		drawDialog(back.data(), back.size(), width, height);
	}
	else
	{
		text = "哈囉 yoyoyo";
		//drawDialog(text.data(), text.size(), width, height);
	}
	end1 = clock();
	cout << "draw dialog time = " << ((double)(end1 - start1) / CLOCKS_PER_SEC) << "s" << endl;

	


	start1 = clock();
	clueBox.show_clue_box(clueBox_texture);
	clueBox.show_clue(width, height);
	end1 = clock();
	cout << "cluebox time = " << ((double)(end1 - start1) / CLOCKS_PER_SEC) << "s" << endl;


	display_end = clock();
	cout << "display time = " << ((double)(display_end - display_start) / CLOCKS_PER_SEC) << "s" << endl << endl << endl;
	//glFlush();
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


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load clue box background image
	clueBox_texture = imread("D:\\resource\\paper_texture_small.png");
	//clueBox.show_clue_box(clueBox_texture);
	//clueBox.show_clue(width, height);

	// Set light
	prepare_lighting();


	background = imread("D:\\resource\\2D\\story.jpg");
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