#include "D:/RoomEscape/h/ResizeImg.h"
#include "D:/RoomEscape/h/PositionImgSetting.h"
#include "D:/RoomEscape/h/ChooseImageSSIM.h"
#include "D:/RoomEscape/h/Clue.h"
#include <iostream> 
#include <string> 

#include <opencv2/contrib/contrib.hpp>	//要用timer就需要
#include "opencv2/highgui/highgui.hpp"


string room_final = "finalroom";
PositionImgSetting PosSet1(room_final, 1);

vector<Clue> clue_1;


void SetResourceImg()
{
	int position_num = 1;

	int findH_from = 0;
	int findH_to = 22;
	//choose_image(room_final, position_num, VERTICAL_CENTRAL, findH_from, findH_to);
	

	string path = "D:\\image\\" + room_final + "\\position1" + "\\";
	resize_all(room_final, position_num, VERTICAL_DOWN_20, 58);

	//resize_all(room_final, position_num, VERTICAL_UP_20, 50);
	//resize_all(room_final, position_num, VERTICAL_CENTRAL, 50);
	//resize_all(room_final, position_num, VERTICAL_DOWN_20, 50);
	//resize_all(room_final, position_num, VERTICAL_DOWN_40, 50);
}


void SetAllSceneImg()
{
	TickMeter  tm;
	int position_num = 1;

	tm.reset();
	tm.start();

	string path = "D:\\image\\" + room_final + "\\position1" + "\\";
	//PosSet1.StitchSceneRange(VERTICAL_CENTRAL, 11, 179, METHOD1);
	PosSet1.StitchSceneRange(VERTICAL_DOWN_20, 75, 179, METHOD1);
	//PosSet1.StitchSceneAll(METHOD2);

	tm.stop();
	cout << "process time = " << tm.getTimeSec() << " sec." << endl;
}

void gameBuild()
{
	SetResourceImg();
	//SetAllSceneImg();
}