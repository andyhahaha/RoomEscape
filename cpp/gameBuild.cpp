#include "D:/RoomEscape/h/ResizeImg.h"
#include "D:/RoomEscape/h/PositionImgSetting.h"
#include "D:/RoomEscape/h/ChooseImageSSIM.h"
#include "D:/RoomEscape/h/Clue.h"
#include <iostream> 
#include <string> 

#include <opencv2/contrib/contrib.hpp>	//要用timer就需要
#include "opencv2/highgui/highgui.hpp"


string room_test = "test";
string room_test2 = "test2";
string room_test3 = "test3";
string room_test4 = "test4";
string room_test5 = "AR1";
PositionImgSetting pos_set1_1(room_test, 1);
PositionImgSetting pos_set2_1(room_test2, 1);
PositionImgSetting pos_set3_1(room_test3, 1);
PositionImgSetting pos_set4_1(room_test4, 1);
PositionImgSetting pos_set5_1(room_test5, 1);

vector<Clue> clue_1;

void SetAllClue()
{
	Clue clue0(room_test5, 1, "teddy", 0, 0, 0.0, 0.0, 0.1, 0.1), clue1;

	clue0.add_dialog("This is a teddy!");
	clue0.add_state(DRAW_ON_SCENE);
	clue0.add_img_path("No image~~~");

	clue0.write_initial_file();

	clue1.set_clue("D:\\clue\\AR1\\position1\\teddy");

	int i;
}


void SetResourceImg()
{
	int position_num = 1;

	int findH_from = 618;
	int findH_to = 619;
	//choose_image(room_test5, position_num, VERTICAL_DOWN_40, findH_from, findH_to);

	//resize_all(room_test5, position_num, VERTICAL_CENTRAL, 50);
	//resize_all(room_test5, position_num, VERTICAL_UP_20, 50);
	//resize_all(room_test5, position_num, VERTICAL_DOWN_20, 50);
	resize_all(room_test5, position_num, VERTICAL_DOWN_40, 50);
}


void SetAllSceneImg(int argc, char** argv)
{
	TickMeter  tm;
	int position_num = 1;

	tm.reset();
	tm.start();

	string path = "D:\\image\\image_use\\" + room_test3 + "\\position1" + "\\";
	pos_set5_1.StitchSceneRange(VERTICAL_DOWN_20, 160, 181, METHOD2);
	//pos_set5_1.StitchSceneAll(METHOD2);

	tm.stop();
	cout << "process time1=" << tm.getTimeSec() << " sec." << endl;
}

void gameBuild(int argc, char** argv)
{
	//SetResourceImgImg();
	SetAllSceneImg(argc, argv);
	//SetAllClue();
}