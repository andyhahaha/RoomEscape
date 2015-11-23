#ifndef _GAMERUN_H
#define _GAMERUN_H
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <cstring>
#include "glut.h"

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

#include "D:\RoomEscape\h\glm.h"
#include "D:\RoomEscape\h\ClueBox.h"
#include "D:\RoomEscape\h\DrawImage.h"
#include "D:\RoomEscape\h\Define.h"

using namespace cv;
using namespace std;

#define G_PI 3.14159265358979323846f
#define RADPERDEG 0.0174533


/*window*/
extern int width;      //Width of the background in pixels.
extern int height;     //Height of the background in pixels.		


/*scence*/
extern int scence_num;
extern Mat background;

/*3D object*/
extern GLMmodel *glm_model;
extern vector<GLuint>list_id;

/*clue box*/
extern ClueBox clueBox;

/*Clue vector*/
extern vector<Clue> ClueOnScreen;
extern vector<Clue> ClueOnRoom;
extern vector<Clue> ClueInCloset;
extern vector<Clue> ClueInDrawer1;
extern vector<Clue> ClueInDrawer2;
extern vector<Clue> ClueInDrawer3;
extern vector<Clue> ClueInBlueShelfTop;
extern vector<Clue> ClueInBlueShelfMid;
extern vector<Clue> ClueInBlueShelfBtn;

extern vector<Clue> ClueInPillow;
extern vector<Clue> ClueInCurtain;
extern vector<Clue> AllClue;


/*mouse*/
extern int mouseState;

/*mouse roatation event*/
extern int record_x;
extern int record_y;
extern int rot_x;
extern int rot_y;
extern int rot_z;
extern int old_rot_x;
extern int old_rot_y;
extern int old_rot_z;

/*look at*/
extern float cam_z;

/*mode matrix*/
extern GLint    viewport[4];
extern GLdouble modelview[16];
extern GLdouble projection[16];


void  gameRun(int argc, char** argv);

/*clue action*/
void nearScence(string, int);
string typeCode();
void showInCluebox(Clue);
void changeState(Clue);
void ClueHit(int, int, vector<Clue>);
void ClueHitNearScence(int , int , vector<Clue> );


GLuint drawObject(GLMmodel *model, Clue &clue, int obj_num);
void clueSetting();


#endif