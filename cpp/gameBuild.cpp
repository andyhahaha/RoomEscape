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

void SetAllClue()
{
	Clue clue0(room_final, 1, "teddy", 0, 0, 0, 0), clue1;

	clue0.add_dialog("This is a teddy!");
	clue0.add_state(SHOW_ON_SCENE);
	clue0.add_2Dimg_path("No image~~~");

	clue0.write_initial_file();

	clue1.set_clue("D:\\clue\\AR1\\position1\\teddy");
}


void SetResourceImg()
{
	int position_num = 1;

	int findH_from = 32;
	int findH_to = 33;
	choose_image(room_final, position_num, VERTICAL_UP_20, findH_from, findH_to);

	//resize_all(room_test5, position_num, VERTICAL_CENTRAL, 50);
	//resize_all(room_test5, position_num, VERTICAL_UP_20, 50);
	//resize_all(room_test5, position_num, VERTICAL_DOWN_20, 50);
	//resize_all(room_test5, position_num, VERTICAL_DOWN_40, 50);
}


void SetAllSceneImg()
{
	TickMeter  tm;
	int position_num = 1;

	tm.reset();
	tm.start();

	string path = "D:\\image\\image_use\\" + room_final + "\\position1" + "\\";
	PosSet1.StitchSceneRange(VERTICAL_DOWN_20, 0, 156, METHOD2);
	//PosSet1.StitchSceneAll(METHOD2);

	tm.stop();
	cout << "process time = " << tm.getTimeSec() << " sec." << endl;
}

void gameBuild()
{
	SetResourceImg();
	//SetAllSceneImg();
	//SetAllClue();
}