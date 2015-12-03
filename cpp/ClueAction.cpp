#include "D:\RoomEscape\h\gameRun.h"


void safeAction(Clue clue)
{
	if (!clue.clue_name().compare("safe1"))
	{
		background = imread(ClueInRoom[0].current_2Dimg_path());
		ClueInRoom[0].next_state(SHOW_NEAR_SCENE);		//safe next state = show near scene

		if (ClueInRoom[0].current_2Dimg() == 0)		//current 2D img of safe1 is typecode img
		{
			mouseState = TYPECODE;
			code[0] = '0';
			code[1] = '0';
			code[2] = '0';
			code[3] = '0';
			ClueOnScreen.assign(ClueSafeTypeCode1.begin(), ClueSafeTypeCode1.end());
		}
		else if (ClueInRoom[0].current_2Dimg() == 2)	//safe1 is opened and empty
		{
			mouseState = NEARSCENE;
			ClueOnScreen.clear();
			ClueOnScreen.push_back(ClueSafeOpen1[0]);	//只剩下back
		}
		else	//safe1 is opened and with key inside
		{
			mouseState = NEARSCENE;
			ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());
		}
	}
	else if (!clue.clue_name().compare("back"))
	{
		mouseState = ROOM;
		ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
	}
	else if (!clue.clue_name().compare("safe1_key"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[0].next_2Dimg(2);	//near scene change to opened safe1 (empty)
		background = imread(ClueInRoom[0].current_2Dimg_path());	//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open_empty.jpg"
		ClueOnScreen.clear();
		ClueOnScreen.push_back(ClueSafeOpen1[0]);	//只剩下back
	}
	else	//點到safe的數字區, including "clear" and "OK"
	{
		if (typeCode(clue,code))
		{
			mouseState = NEARSCENE;
			ClueInRoom[0].next_2Dimg(1);	//near scene change to opened safe1 with a key inside
			ClueInRoom[0].next_3Dobj(1);	//opened safe1 3D object
			background = imread(ClueInRoom[0].current_2Dimg_path());		//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open.jpg"
			ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());		//只剩下back和key

			//change key state
			ClueInRoom[1].next_state(SHOW_ON_SCENE);
		}
	}
}




/* the key of the safe1 */
void keyAction(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[1].next_state(SHOW_IN_CLUEBOX);
	}
	/*else if (clue.current_state() == SHOW_IN_CLUEBOX)
	{

	}*/
}


/* card D */
void cardDAction(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[2].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
	}
	/*else if (clue.current_state() == SHOW_IN_CLUEBOX)
	{

	}*/
}

/* card S */
void cardSAction(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[3].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
	}
	/*else if (clue.current_state() == SHOW_IN_CLUEBOX)
	{

	}*/

}


/* card P */
void cardPAction(Clue clue)
{
	showInCluebox(clue);

}

/* card 7 */
void card_num1Action(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[3].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
	}
	/*else if (clue.current_state() == SHOW_IN_CLUEBOX)
	{

	}*/
}

/* card 2 */
void card_num2Action(Clue clue)
{
	showInCluebox(clue);

}

/* card 3 */
void card_num3Action(Clue clue)
{
	showInCluebox(clue);
	
}

void curtainAction()
{
	cout << "---------- hit curtain ----------\n" << endl;

}

void pillowAction(Clue clue)
{
	cout << "---------- hit pillow -----------\n" << endl;
	if (!clue.clue_name().compare("pillow"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[9].next_2Dimg(0);
		background = imread(ClueInRoom[9].current_2Dimg_path());		//The first 2D img of the pillow (_2Dimg_path[0])
		ClueOnScreen.assign(ClueInPillow.begin(), ClueInPillow.end());
	}
	else if (!clue.clue_name().compare("pillow_nearscene_back"))
	{
		if (ClueInRoom[9].current_2Dimg() == 0)		//pillow with paper
		{
			mouseState = ROOM;
			ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
		}
		else	//paper near scene
		{
			mouseState = NEARSCENE;
			ClueInRoom[9].next_2Dimg(0);
			background = imread(ClueInRoom[9].current_2Dimg_path());		//The first 2D img of the pillow (_2Dimg_path[0])
			ClueOnScreen.assign(ClueInPillow.begin(), ClueInPillow.end());
		}
	}
	else if (!clue.clue_name().compare("pillow_paper"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[9].next_2Dimg(1);		//paper near scene
		background = imread(ClueInRoom[9].current_2Dimg_path());	//show paper near scene
		ClueOnScreen.clear();
		ClueOnScreen.push_back(ClueInPillow[0]);	//only "pillow_nearscene_back"
	}
}

void Blue_shelf_TopAction(Clue clue)
{
	
		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Top.JPG");
		ClueOnScreen.assign(ClueInBlueShelfTop.begin(), ClueInBlueShelfTop.end());
	
}

void Blue_shelf_MidAction(Clue clue)
{
	
		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Mid.JPG");
		ClueOnScreen.assign(ClueInBlueShelfMid.begin(), ClueInBlueShelfMid.end());
	
	
}

void Blue_shelf_buttonAction(Clue clue)
{
		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Button.JPG");
		ClueOnScreen.assign(ClueInBlueShelfBtn.begin(), ClueInBlueShelfBtn.end());

}

void Orange_shelf_TopAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Top.JPG");
	ClueOnScreen.assign(ClueInBlueShelfBtn.begin(), ClueInBlueShelfBtn.end());

}

void Orange_shelf_MidAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Mid.JPG");
	ClueOnScreen.assign(ClueInOrangeShelfMid.begin(), ClueInOrangeShelfMid.end());

}

void Orange_shelf_buttonAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Button.JPG");
	ClueOnScreen.assign(ClueInOrangeShelfBtn.begin(), ClueInOrangeShelfBtn.end());

}


void Green_shelf_TopAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Top.JPG");
	ClueOnScreen.assign(ClueInGreenShelfTop.begin(), ClueInGreenShelfTop.end());
}
void Green_shelf_MidAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Mid.JPG");
	ClueOnScreen.assign(ClueInGreenShelfMid.begin(), ClueInGreenShelfMid.end());

}
void Green_shelf_buttonAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Button.JPG");
	ClueOnScreen.assign(ClueInGreenShelfBtn.begin(), ClueInGreenShelfBtn.end());

}



void Wood_shelfAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Wood_Shelf.JPG");
	ClueOnScreen.assign(ClueInWoodShelf.begin(), ClueInWoodShelf.end());

}
void Wood_shelf_TopAction(){


}
void Wood_shelf_MidAction(){


}
void Wood_shelf_buttonAction(){


}

void BoatAction(){
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\boat.JPG");
	ClueOnScreen.assign(ClueInBoat.begin(), ClueInBoat.end());

}

void PaintAction(){
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\paint.JPG");
	ClueOnScreen.assign(ClueInPaint.begin(), ClueInPaint.end());

}




void showInCluebox(Clue clue)
{
	clueBox.InsertItem(clue);
}



void changeState(Clue clue)
{
	vector<Clue>::iterator it_clue;
	//if (clue.clue_name() = "")

	cout << "clue = " << clue.clue_name() << endl;

	if (!clue.clue_name().compare("safe1"))
		safeAction(clue);

	for (it_clue = ClueSafeTypeCode1.begin(); it_clue != ClueSafeTypeCode1.end(); ++it_clue)
	{
		if (!clue.clue_name().compare(it_clue->clue_name()))
			safeAction(clue);
	}

	if (!clue.clue_name().compare("key"))
		keyAction(clue);
	else if (!clue.clue_name().compare("cardD"))
		cardDAction(clue);
	else if (!clue.clue_name().compare("cardS"))
		cardSAction(clue);
	else if (!clue.clue_name().compare("cardP"))
		cardPAction(clue);
	else if (!clue.clue_name().compare("card_num1"))
		card_num1Action(clue);
	else if (!clue.clue_name().compare("card_num2"))
		card_num2Action(clue);
	else if (!clue.clue_name().compare("card_num3"))
		card_num3Action(clue);
	else if (!clue.clue_name().compare("curtain"))
		curtainAction();
	else if (!clue.clue_name().compare("pillow"))
		pillowAction(clue);
	else if (!clue.clue_name().compare("Blue_shelf_Top"))
		Blue_shelf_TopAction(clue);
	else if (!clue.clue_name().compare("Blue_shelf_Mid"))
		Blue_shelf_MidAction(clue);
	else if (!clue.clue_name().compare("Blue_shelf_button"))
		Blue_shelf_buttonAction(clue);
	else if (!clue.clue_name().compare("Orange_shelf_Top"))
		Orange_shelf_TopAction();
	else if (!clue.clue_name().compare("Orange_shelf_Mid"))
		Orange_shelf_MidAction();
	else if (!clue.clue_name().compare("Orange_shelf_button"))
		Orange_shelf_buttonAction();
	else if (!clue.clue_name().compare("Green_shelf_Top"))
		Green_shelf_TopAction();
	else if (!clue.clue_name().compare("Green_shelf_Mid"))
		Green_shelf_MidAction();
	else if (!clue.clue_name().compare("Green_shelf_button"))
		Green_shelf_buttonAction();
	else if (!clue.clue_name().compare("Wood_shelf"))
		Wood_shelfAction();
	else if (!clue.clue_name().compare("Wood_shelf_Top"))
		Wood_shelf_TopAction();
	else if (!clue.clue_name().compare("Wood_shelf_Mid"))
		Wood_shelf_MidAction();
	else if (!clue.clue_name().compare("Wood_shelf_button"))
		Wood_shelf_buttonAction();
	else if (!clue.clue_name().compare("boat"))
		BoatAction();
	else if (!clue.clue_name().compare("paint"))
		PaintAction();

}

void ClueHit(int x, int y, vector<Clue> _onScreenClue)
{
	vector<Clue>::iterator it_clue;

	GLdouble  winX, winY, winZ;
	GLdouble posX, posY, posZ;
	int screenX, screenY;
	int maxX = -10000, minX = 10000, maxY = -10000, minY = 10000;
	int i;

	for (it_clue = _onScreenClue.begin(); it_clue != _onScreenClue.end(); ++it_clue) 
	{
		maxX = -10000;
		minX = 10000;
		maxY = -10000;
		minY = 10000;
		for (i = 0; i < it_clue->obj_corner().size(); i++)
		{
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

		/*cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "clue = " << it_clue->clue_name() << endl;
		cout << "maxX = " << maxX << endl;
		cout << "minX = " << minX << endl;
		cout << "maxY = " << maxY << endl;
		cout << "minY = " << minY << endl;*/
		

		if (x <= maxX && x >= minX && y <= maxY && y >= minY)
		{
			changeState(*it_clue);
			//clueBox.InsertItem(*it_clue);
			//cout << "~~~~~~~~~~~~~~~~~~Insert clue = " << it_clue->clue_name() << endl;
		}
		//clueBox.InsertItem(*it_clue);
	}
}



void ClueHitNearScence(int x, int y, vector<Clue> _onScreenClue)
{
	vector<Clue>::iterator it_clue;
	for (it_clue = _onScreenClue.begin(); it_clue != _onScreenClue.end(); ++it_clue) 
	{
		if (x > it_clue->get_2D_coordinate()[0].x && x<it_clue->get_2D_coordinate()[1].x && y>it_clue->get_2D_coordinate()[0].y && y < it_clue->get_2D_coordinate()[1].y)
			changeState(*it_clue);
	}
}

