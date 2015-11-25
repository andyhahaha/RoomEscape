#include "D:\RoomEscape\h\gameRun.h"
vector<Clue> ClueSafeOpen1;
vector<Clue> ClueSafeTypeCode1;
int gameState;


int typeCode(Clue clue){

	return 0;
}


void safeAction(Clue clue)
{
	if (!clue.clue_name().compare("safe1"))
	{
		mouseState = NEARSCENE;
		background = imread(ClueInRoom[0].current_2Dimg());
		ClueInRoom[0].next_state(SHOW_NEAR_SCENE);		//safe next state = show near scene

		if (gameState == STATE1)
		{
			ClueOnScreen.assign(ClueSafeTypeCode1.begin(), ClueSafeTypeCode1.end());
		}
		else
		{
			if (ClueInRoom[1].current_state() == SHOW_IN_CLUEBOX || ClueInRoom[1].current_state() == NOT_SHOW)	//check key state
			{
				ClueOnScreen.clear();
				ClueOnScreen.push_back(ClueSafeOpen1[0]);	//只剩下back
			}
			else
			{
				ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());
			}
		}
	}
	else if (!clue.clue_name().compare("safe1_nearscene_back"))
	{
		mouseState = ROOM;
		ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
	}
	else if (!clue.clue_name().compare("safe1_key"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[0].next_2Dimg(2);	//near scene change to opened safe1 (empty)
		background = imread(ClueInRoom[0].current_2Dimg());	//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open_empty.jpg"
		ClueOnScreen.clear();
		ClueOnScreen.push_back(ClueSafeOpen1[0]);	//只剩下back
	}
	else	//點到safe的數字區
	{
		if (typeCode(clue))
		{
			mouseState = NEARSCENE;
			ClueInRoom[0].next_2Dimg(1);	//near scene change to opened safe1 with a key inside
			ClueInRoom[0].next_3Dobj(1);	//opened safe1 3D object
			background = imread(ClueInRoom[0].current_2Dimg());		//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open.jpg"
			
			ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());		//只剩下back和key
		}
	}
	

}


void keyAction(){


}
void cardDAction(){


}
void cardSAction(){


}
void cardPAction(){


}
void card_num1Action(){


}
void card_num2Action(){


}
void card_num3Action(){


}
void curtainAction(){


}
void pillowAction(){


}
void Blue_shelf_TopAction()
{
	//nearScence("D:\\resource\\2D\\teddy.png");
	mouseState = NEARSCENE;
	background = imread("D:\\resource\\2D\\teddy.png");
	ClueOnScreen.assign(ClueInBlueShelfTop.begin(),ClueInBlueShelfTop.end());

}

void Blue_shelf_MidAction(){


}
void Blue_shelf_buttonAction(){


}
void Orange_shelf_TopAction(){


}
void Orange_shelf_MidAction(){


}
void Orange_shelf_buttonAction(){


}
void Green_shelf_TopAction(){


}
void Green_shelf_MidAction(){


}
void Green_shelf_buttonAction(){


}
void Wood_shelf_TopAction(){


}
void Wood_shelf_MidAction(){


}
void Wood_shelf_buttonAction(){


}



/*void nearScence(string path, int scence)
{
	background = imread(path);
	mouseState = scence;

}*/


void showInCluebox(Clue clue)
{
	clueBox.InsertItem(clue);
}



void changeState(Clue clue){

	//if (clue.clue_name() = "")

	cout << "clue = " << clue.clue_name() << endl;

	if (!clue.clue_name().compare("safe") || !clue.clue_name().compare("1"))
		safeAction(clue);
	else if (!clue.clue_name().compare("key"))
		keyAction();
	else if (!clue.clue_name().compare("cardD"))
		cardDAction();
	else if (!clue.clue_name().compare("cardS"))
		cardSAction();
	else if (!clue.clue_name().compare("cardP"))
		cardPAction();
	else if (!clue.clue_name().compare("card_num1"))
		card_num1Action();
	else if (!clue.clue_name().compare("card_num2"))
		card_num2Action();
	else if (!clue.clue_name().compare("card_num3"))
		card_num3Action();
	else if (!clue.clue_name().compare("curtain"))
		curtainAction();
	else if (!clue.clue_name().compare("pillow"))
		pillowAction();
	else if (!clue.clue_name().compare("Blue_shelf_Top"))
		Blue_shelf_TopAction();
	else if (!clue.clue_name().compare("Blue_shelf_Mid"))
		Blue_shelf_MidAction();
	else if (!clue.clue_name().compare("Blue_shelf_button"))
		Blue_shelf_buttonAction();
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
	else if (!clue.clue_name().compare("Wood_shelf_Top"))
		Wood_shelf_TopAction();
	else if (!clue.clue_name().compare("Wood_shelf_Mid"))
		Wood_shelf_MidAction();
	else if (!clue.clue_name().compare("Wood_shelf_button"))
		Wood_shelf_buttonAction();



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
		if (x > it_clue->get_2D_coordinate()[0].x&&x<it_clue->get_2D_coordinate()[1].x&&y>it_clue->get_2D_coordinate()[0].y&&y < it_clue->get_2D_coordinate()[1].y)
			changeState(*it_clue);
	}
}