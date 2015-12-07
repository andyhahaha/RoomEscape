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
extern int scene_num;
extern Mat background;

/*3D object*/
extern GLMmodel *glm_model;
extern vector<GLuint>list_id;
extern vector<int>list_id_show;

/*clue box*/
extern ClueBox clueBox;


/* game state */
//extern int gameState;

/*Clue vector*/
extern vector<Clue> ClueOnScreen;
extern vector<Clue> ClueInRoom;
extern vector<Clue> ClueInCloset;
extern vector<Clue> ClueInPillow;
extern vector<Clue> ClueInCurtain;

extern vector<Clue> ClueInDrawer1;
extern vector<Clue> ClueInDrawer2;
extern vector<Clue> ClueInDrawer3;

extern vector<Clue> ClueBookInside;
extern vector<Clue> ClueInBlueShelfTop;
extern vector<Clue> ClueInBlueShelfMid;
extern vector<Clue> ClueInBlueShelfBtn;

extern vector<Clue> ClueInOrangeShelfTop;
extern vector<Clue> ClueInOrangeShelfMid;
extern vector<Clue> ClueInOrangeShelfBtn;

extern vector<Clue> ClueInGreenShelfTop;
extern vector<Clue> ClueInGreenShelfMid;
extern vector<Clue> ClueInGreenShelfBtn;

extern vector<Clue> ClueInWoodShelf;
extern vector<Clue> ClueInWoodShelfTop;
extern vector<Clue> ClueInWoodShelfMid;
extern vector<Clue> ClueInWoodShelfBtn;

extern vector<Clue> ClueInPaint;
extern vector<Clue> ClueInBoat;

extern vector<Clue> ClueSafeTypeCode1;
extern vector<Clue> ClueSafeOpen1;

extern Clue back;


/*mouse*/
extern int mouseState;

/*mouse roatation event*/
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


extern int sight;

void  gameRun(int argc, char** argv);
void  display();


/*clue action*/
void nearScence(string, int);

extern char code[4];	//code of the safe
int typeCode(Clue clue,char *code);
void drawCode(char *code);

extern char bookpage[4];	//correct page of DSP
int bookInside(Clue clue, char *bookpage);

void showInCluebox(Clue);
void changeState(Clue);
void ClueHit(int, int, vector<Clue>);
void ClueHitNearScence(int , int , vector<Clue> );


GLuint drawObject(GLMmodel *model, Clue &clue, int obj_num);
void clueSetting();


#endif