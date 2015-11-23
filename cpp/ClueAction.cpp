#include "D:\RoomEscape\h\gameRun.h"


void safeAction(){


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
void Blue_shelf_TopAction(){
	//nearScence("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\teddy.png");
	mouseState = NEARSCENCE;
	background = imread("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\teddy.png");
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



/*void nearScence(string path, int scence){

	background = imread(path);
	mouseState = scence;

}*/

void showInCluebox(Clue clue){

	clueBox.InsertItem(clue);

}
void changeState(Clue clue){

	//if (clue.clue_name() = "")

	cout << "clue = " << clue.clue_name() << endl;

	if (!clue.clue_name().compare("safe"))
		safeAction();
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

void ClueHit(int x, int y, vector<Clue> _onScreenClue){
	vector<Clue>::iterator it_clue;


	GLdouble  winX, winY, winZ;
	GLdouble posX, posY, posZ;
	int screenX, screenY;
	int maxX = -10000, minX = 10000, maxY = -10000, minY = 10000;
	int i;

	for (it_clue = _onScreenClue.begin(); it_clue != _onScreenClue.end(); ++it_clue) {
		maxX = -10000;
		minX = 10000;
		maxY = -10000;
		minY = 10000;
		for (i = 0; i < it_clue->obj_corner().size(); i++){
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
		

		if (x <= maxX && x >= minX && y <= maxY && y >= minY){

			changeState(*it_clue);
			//cout << "~~~~~~~~~~~~~~~~~~Insert clue = " << it_clue->clue_name() << endl;
			}

			//clueBox.InsertItem(*it_clue);
			
		}
	}

void ClueHitNearScence(int x, int y, vector<Clue> _onScreenClue){

	vector<Clue>::iterator it_clue;
	for (it_clue = _onScreenClue.begin(); it_clue != _onScreenClue.end(); ++it_clue) {
		
		if (x > it_clue->get_2D_coordinate()[0].x&&x<it_clue->get_2D_coordinate()[1].x&&y>it_clue->get_2D_coordinate()[0].y&&y < it_clue->get_2D_coordinate()[1].y)
			changeState(*it_clue);
	}




}