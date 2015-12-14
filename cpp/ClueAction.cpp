#include "D:\RoomEscape\h\gameRun.h"

char code[4];
char bookpage[3];
int current_book;		//The current book that is chosen (DSP, computer network, math, calculus, probability)
int book_current_num;	//The current place of the book page number which is going to be filled.(0 or 1 or 2)
char lastpage[3];

void backAction()
{
	mouseState = ROOM;
	ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
}


void safeAction(Clue clue)
{
	if (!clue.clue_name().compare("safe1"))
	{
		background = imread(ClueInRoom[INROOM_SAFE].current_2Dimg_path());
		ClueInRoom[INROOM_SAFE].next_state(SHOW_NEAR_SCENE);		//safe next state = show near scene

		if (ClueInRoom[INROOM_SAFE].current_2Dimg() == 0)		//current 2D img of safe1 is typecode img
		{
			mouseState = TYPECODE;
			code[0] = '0';
			code[1] = '0';
			code[2] = '0';
			code[3] = '0';
			ClueOnScreen.assign(ClueSafeTypeCode1.begin(), ClueSafeTypeCode1.end());
		}
		else if (ClueInRoom[INROOM_SAFE].current_2Dimg() == 2)	//safe1 is opened and empty
		{
			mouseState = NEARSCENE;
			ClueOnScreen.clear();
			ClueOnScreen.push_back(back);	//只剩下back
		}
		else	//safe1 is opened and with key inside
		{
			mouseState = NEARSCENE;
			ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());
		}
	}
	else if (!clue.clue_name().compare("key"))
	{
		mouseState = NEARSCENE;
		showInCluebox(clue);
		ClueInRoom[INROOM_SAFE].next_2Dimg(2);	//near scene change to opened safe1 (empty)
		background = imread(ClueInRoom[INROOM_SAFE].current_2Dimg_path());	//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open_empty.jpg"
		ClueOnScreen.clear();
		ClueOnScreen.push_back(back);	//只剩下back
	}
	else	//點到safe的數字區, including "clear" and "OK"
	{
		if (typeCode(clue,code))
		{
			mouseState = NEARSCENE;
			ClueInRoom[INROOM_SAFE].next_2Dimg(1);	//near scene change to opened safe1 with a key inside
			//ClueInRoom[INROOM_SAFE].next_3Dobj(1);	//opened safe1 3D object
			background = imread(ClueInRoom[INROOM_SAFE].current_2Dimg_path());		//"D:\\image\\finalroom\\position1\\near_scene\\safe1_open.jpg"
			ClueOnScreen.assign(ClueSafeOpen1.begin(), ClueSafeOpen1.end());		//只剩下back和key

			//change key state
			//ClueInRoom[1].next_state(SHOW_ON_SCENE);
		}
	}
}




/* the key of the safe1 */
void keyAction(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		//ClueInRoom[1].next_state(SHOW_IN_CLUEBOX);
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
		ClueInRoom[INROOM_CARDD].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
		list_id_show[INROOM_CARDD] = SHOW_IN_CLUEBOX;
	}
}


/* card 7 */
void card_num1Action(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[INROOM_CARD7].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
		list_id_show[2] = SHOW_IN_CLUEBOX;
	}
}

/* card 2 */
void card_num2Action(Clue clue)
{
	if (clue.current_state() == SHOW_ON_SCENE)
	{
		ClueInRoom[INROOM_CARD2].next_state(SHOW_IN_CLUEBOX);
		showInCluebox(clue);
		list_id_show[3] = SHOW_IN_CLUEBOX;
	}
}


void curtainAction(Clue clue)
{
	cout << "---------- hit curtain ----------\n" << endl;
	if (!clue.clue_name().compare("curtain1") || !clue.clue_name().compare("curtain2") || !clue.clue_name().compare("curtain3"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_CURTAIN].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_CURTAIN].current_2Dimg_path());
		ClueOnScreen.assign(ClueInCurtainClosed.begin(), ClueInCurtainClosed.end());
	}
	else if (!clue.clue_name().compare("curtain_down"))
	{
		mouseState = NEARSCENE;

		if (ClueInCurtainOpened[2].current_state() == SHOW_IN_CLUEBOX)	//If card P is in the clue box, show the image with no card P.
		{
			ClueInRoom[INROOM_CURTAIN].next_2Dimg(2);
			background = imread(ClueInRoom[INROOM_CURTAIN].current_2Dimg_path());
			ClueOnScreen.assign(ClueInCurtainOpened.begin(), ClueInCurtainOpened.end() - 1);
		}
		else
		{
			ClueInRoom[INROOM_CURTAIN].next_2Dimg(1);
			background = imread(ClueInRoom[INROOM_CURTAIN].current_2Dimg_path());
			ClueOnScreen.assign(ClueInCurtainOpened.begin(), ClueInCurtainOpened.end());
		}
	}
	else if (!clue.clue_name().compare("curtain_up"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_CURTAIN].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_CURTAIN].current_2Dimg_path());
		ClueOnScreen.assign(ClueInCurtainClosed.begin(), ClueInCurtainClosed.end());
	}
	else if (!clue.clue_name().compare("cardP"))
	{
		ClueInCurtainOpened[2].next_state(SHOW_IN_CLUEBOX);		//card P show in clue box
		showInCluebox(clue);
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_CURTAIN].next_2Dimg(2);
		background = imread(ClueInRoom[INROOM_CURTAIN].current_2Dimg_path());
		ClueOnScreen.assign(ClueInCurtainOpened.begin(), ClueInCurtainOpened.end() - 1);
	}
}

void pillowAction(Clue clue)
{
	cout << "---------- hit pillow -----------\n" << endl;
	if (!clue.clue_name().compare("pillow"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_PILLOW].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_PILLOW].current_2Dimg_path());		//The first 2D img of the pillow (_2Dimg_path[0])
		ClueOnScreen.assign(ClueInPillow.begin(), ClueInPillow.end());
	}
	else if (!clue.clue_name().compare("pillow_nearscene_back"))
	{
		if (ClueInRoom[INROOM_PILLOW].current_2Dimg() == 0)		//pillow with paper
		{
			mouseState = ROOM;
			ClueOnScreen.assign(ClueInRoom.begin(), ClueInRoom.end());
		}
		else	//paper near scene
		{
			mouseState = NEARSCENE;
			ClueInRoom[INROOM_PILLOW].next_2Dimg(0);
			background = imread(ClueInRoom[INROOM_PILLOW].current_2Dimg_path());		//The first 2D img of the pillow (_2Dimg_path[0])
			ClueOnScreen.assign(ClueInPillow.begin(), ClueInPillow.end());
		}
	}
	else if (!clue.clue_name().compare("pillow_paper"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_PILLOW].next_2Dimg(1);		//paper near scene
		background = imread(ClueInRoom[INROOM_PILLOW].current_2Dimg_path());	//show paper near scene
		ClueOnScreen.clear();
		ClueOnScreen.push_back(ClueInPillow[1]);	//only "pillow_nearscene_back"
	}
}

void Blue_shelf_TopAction(Clue clue)
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Top.JPG");
	ClueOnScreen.clear();
	ClueOnScreen.push_back(back);
}

void Blue_shelf_MidAction(Clue clue)
{
	if (!clue.clue_name().compare("Blue_shelf_Mid"))
	{
		mouseState = NEARSCENE;
		background = imread(ClueInRoom[INROOM_BLUESHELF2].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfMid.begin(), ClueInBlueShelfMid.end());
	}
	else if (!clue.clue_name().compare("DSP"))
	{
		mouseState = BOOKINSIDE;
		bookpage[0] = '-';
		bookpage[1] = '-';
		bookpage[2] = '-';

		lastpage[0] = '-';
		lastpage[1] = '-';
		lastpage[2] = '-';
		current_book = ADSP;
		background = imread(ClueInBlueShelfMid[1].current_2Dimg_path());	//DSP cover
		ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
	}
	else if (!clue.clue_name().compare("Computer_Networks"))
	{
		mouseState = BOOKINSIDE;
		bookpage[0] = '-';
		bookpage[1] = '-';
		bookpage[2] = '-';

		lastpage[0] = '-';
		lastpage[1] = '-';
		lastpage[2] = '-';
		current_book = COMPUTER;
		background = imread(ClueInBlueShelfMid[2].current_2Dimg_path());	//computer network cover
		ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
	}
}

void Blue_shelf_buttonAction(Clue clue)
{
	if (!clue.clue_name().compare("Blue_shelf_bottom"))
	{
		mouseState = NEARSCENE;
		background = imread(ClueInRoom[INROOM_BLUESHELF3].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfBtm.begin(), ClueInBlueShelfBtm.end());
	}
	else if (!clue.clue_name().compare("math"))
	{
		mouseState = BOOKINSIDE;
		bookpage[0] = '-';
		bookpage[1] = '-';
		bookpage[2] = '-';

		lastpage[0] = '-';
		lastpage[1] = '-';
		lastpage[2] = '-';
		current_book = MATH;
		background = imread(ClueInBlueShelfBtm[1].current_2Dimg_path());	//DSP cover
		ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
	}
	else if (!clue.clue_name().compare("calculus"))
	{
		mouseState = BOOKINSIDE;
		bookpage[0] = '-';
		bookpage[1] = '-';
		bookpage[2] = '-';

		lastpage[0] = '-';
		lastpage[1] = '-';
		lastpage[2] = '-';
		current_book = CALCULUS;
		background = imread(ClueInBlueShelfBtm[2].current_2Dimg_path());	//computer network cover
		ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
	}
	else if (!clue.clue_name().compare("probability"))
	{
		mouseState = BOOKINSIDE;
		bookpage[0] = '-';
		bookpage[1] = '-';
		bookpage[2] = '-';

		lastpage[0] = '-';
		lastpage[1] = '-';
		lastpage[2] = '-';
		current_book = PROBABILITY;
		background = imread(ClueInBlueShelfBtm[3].current_2Dimg_path());	//computer network cover
		ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
	}
}

void Orange_shelf_TopAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Top.JPG");
	ClueOnScreen.assign(ClueInOrangeShelfTop.begin(), ClueInOrangeShelfTop.end());
}

void Orange_shelf_MidAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Mid.JPG");
	ClueOnScreen.assign(ClueInOrangeShelfMid.begin(), ClueInOrangeShelfMid.end());
}

void Orange_shelf_buttonAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Orange_Shelf_Button.JPG");
	ClueOnScreen.assign(ClueInOrangeShelfBtm.begin(), ClueInOrangeShelfBtm.end());
}


void Green_shelf_TopAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Top.JPG");
	ClueOnScreen.assign(ClueInGreenShelfTop.begin(), ClueInGreenShelfTop.end());
}

void Green_shelf_MidAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Mid.JPG");
	ClueOnScreen.assign(ClueInGreenShelfMid.begin(), ClueInGreenShelfMid.end());
}

void Green_shelf_buttonAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Green_Shelf_Button.JPG");
	ClueOnScreen.assign(ClueInGreenShelfBtm.begin(), ClueInGreenShelfBtm.end());
}



void Wood_shelfAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Wood_Shelf.JPG");
	ClueOnScreen.assign(ClueInWoodShelf.begin(), ClueInWoodShelf.end());
}

void Wood_shelf_TopAction()
{


}

void Wood_shelf_MidAction()
{


}

void Wood_shelf_buttonAction()
{


}

void BoatAction(Clue clue)
{
	if (!clue.clue_name().compare("boat"))
	{
		mouseState = NEARSCENE;
		background = imread(ClueInRoom[INROOM_BOAT].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBoat.begin(), ClueInBoat.end());
	}
	else if (!clue.clue_name().compare("card_num3"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_BOAT].next_2Dimg(1);
		background = imread(ClueInRoom[INROOM_BOAT].current_2Dimg_path());
		showInCluebox(clue);
		ClueOnScreen.clear();
		ClueOnScreen.push_back(back);
	}
}

void PaintAction(Clue clue)
{
	if (!clue.clue_name().compare("paint"))
	{
		mouseState = NEARSCENE;
		background = imread(ClueInRoom[INROOM_PAINT].current_2Dimg_path());
		ClueOnScreen.assign(ClueInPaint.begin(), ClueInPaint.end());
	}
	else if (!clue.clue_name().compare("cardS"))
	{
		mouseState = NEARSCENE;
		ClueInRoom[INROOM_PAINT].next_2Dimg(1);
		background = imread(ClueInRoom[INROOM_PAINT].current_2Dimg_path());
		showInCluebox(clue);
		ClueOnScreen.clear();
		ClueOnScreen.push_back(back);
	}
}

void closetAction(Clue clue)
{
	
	if (!clue.clue_name().compare("closet"))
	{
		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Closet_closed.JPG");
		ClueOnScreen.assign(ClueInClosetClosed.begin(), ClueInClosetClosed.end());
	}
	else if (!clue.clue_name().compare("open_closet"))
	{

		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Closet_open.JPG");
		ClueOnScreen.assign(ClueInClosetOpen.begin(), ClueInClosetOpen.end());
	}
	else if (!clue.clue_name().compare("inside_closet"))
	{

		mouseState = NEARSCENE;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\Closet_inside.JPG");
		ClueOnScreen.assign(ClueInClosetInside.begin(), ClueInClosetInside.end());
	}
	
}

void guitarAction()
{
	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Guitar.JPG");
	ClueOnScreen.clear();
	ClueOnScreen.push_back(back);
}

void DSPAction(Clue clue)
{
	cout << "DSPAction" << endl;
	int current_page = 0;
	int result;

	if (!clue.clue_name().compare("BlueShelf_back"))
	{
		mouseState = NEARSCENE;
		current_book = NOT_CHOOSE;
		book_current_num = 0;
		ClueInBlueShelfMid[1].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_BLUESHELF2].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfMid.begin(), ClueInBlueShelfMid.end());
	}
	else
	{
		result = bookInside(clue, bookpage, 1);
		if (result == 1)			//press OK and page is right
		{
			mouseState = BOOKINSIDE;
			ClueInBlueShelfMid[1].next_2Dimg(6);
			background = imread(ClueInBlueShelfMid[1].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
		else if (result == -1)	//press OK but page is not right
		{
			mouseState = BOOKINSIDE;
			current_page = ClueInBlueShelfMid[1].current_2Dimg() + 1;
			if (current_page >= 6)
				current_page = 1;

			ClueInBlueShelfMid[1].next_2Dimg(current_page);
			background = imread(ClueInBlueShelfMid[1].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
	}
}

void Computer_NetworksAction(Clue clue)
{
	cout << "Computer_NetworksAction" << endl;
	int current_page = 0;

	if (!clue.clue_name().compare("BlueShelf_back"))
	{
		mouseState = NEARSCENE;
		current_book = NOT_CHOOSE;
		book_current_num = 0;
		ClueInBlueShelfMid[2].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_BLUESHELF2].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfMid.begin(), ClueInBlueShelfMid.end());
	}
	else
	{
		if (bookInside(clue, bookpage, 0) == -1)	//press OK but page is not right
		{
			mouseState = BOOKINSIDE;
			current_page = ClueInBlueShelfMid[2].current_2Dimg() + 1;
			if (current_page >= 6)
				current_page = 1;

			ClueInBlueShelfMid[2].next_2Dimg(current_page);
			background = imread(ClueInBlueShelfMid[2].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
	}
}

void mathAction(Clue clue)
{
	cout << "mathAction" << endl;
	int current_page = 0;

	if (!clue.clue_name().compare("BlueShelf_back"))
	{
		mouseState = NEARSCENE;
		current_book = NOT_CHOOSE;
		book_current_num = 0;
		ClueInBlueShelfBtm[1].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_BLUESHELF3].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfBtm.begin(), ClueInBlueShelfBtm.end());
	}
	else
	{
		if (bookInside(clue, bookpage, 0) == -1)	//press OK but page is not right
		{
			mouseState = BOOKINSIDE;
			current_page = ClueInBlueShelfBtm[1].current_2Dimg() + 1;
			if (current_page >= 6)
				current_page = 1;

			ClueInBlueShelfBtm[1].next_2Dimg(current_page);
			background = imread(ClueInBlueShelfBtm[1].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
	}
}

void calculusAction(Clue clue)
{
	cout << "calculusAction" << endl;
	int current_page = 0;

	if (!clue.clue_name().compare("BlueShelf_back"))
	{
		mouseState = NEARSCENE;
		current_book = NOT_CHOOSE;
		book_current_num = 0;
		ClueInBlueShelfBtm[2].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_BLUESHELF3].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfBtm.begin(), ClueInBlueShelfBtm.end());
	}
	else
	{
		if (bookInside(clue, bookpage, 0) == -1)	//press OK but page is not right
		{
			mouseState = BOOKINSIDE;
			current_page = ClueInBlueShelfBtm[2].current_2Dimg() + 1;
			if (current_page >= 6)
				current_page = 1;

			ClueInBlueShelfBtm[2].next_2Dimg(current_page);
			background = imread(ClueInBlueShelfBtm[2].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
	}
}

void probabilityAction(Clue clue)
{
	cout << "probabilityAction" << endl;
	int current_page = 0;

	if (!clue.clue_name().compare("BlueShelf_back"))
	{
		mouseState = NEARSCENE;
		current_book = NOT_CHOOSE;
		book_current_num = 0;
		ClueInBlueShelfBtm[3].next_2Dimg(0);
		background = imread(ClueInRoom[INROOM_BLUESHELF3].current_2Dimg_path());
		ClueOnScreen.assign(ClueInBlueShelfBtm.begin(), ClueInBlueShelfBtm.end());
	}
	else
	{
		if (bookInside(clue, bookpage, 0) == -1)	//press OK but page is not right
		{
			mouseState = BOOKINSIDE;
			current_page = ClueInBlueShelfBtm[3].current_2Dimg() + 1;
			if (current_page >= 6)
				current_page = 1;

			ClueInBlueShelfBtm[3].next_2Dimg(current_page);
			background = imread(ClueInBlueShelfBtm[3].current_2Dimg_path());
			ClueOnScreen.assign(ClueBookInside.begin(), ClueBookInside.end());
		}
	}
}

void LampAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Lamp.JPG");
	ClueOnScreen.clear();
	ClueOnScreen.push_back(back);

}


void MemoAction(){

	mouseState = NEARSCENE;
	background = imread("D:\\image\\finalroom\\position1\\near_scene\\Memo.JPG");
	ClueOnScreen.clear();
	ClueOnScreen.push_back(back);


}

void StartAction()
{
	mouseState = ROOM;
	ClueOnScreen.clear();
}

void PresentAction()
{
	if (clueBox.get_item_selected() != -1 && !clueBox.get_item_name(clueBox.get_item_selected()).compare("key"))
	{
		cout << "Happy Birthday !!!" << endl;
		mouseState = STORYEND;
		background = imread("D:\\image\\finalroom\\position1\\near_scene\\happybirthday.JPG");
		ClueOnScreen.clear();
	}

	cout << "nothing happend" << endl;
}

void showInCluebox(Clue clue)
{
	clueBox.InsertItem(clue);
}



void changeState(Clue clue)
{
	vector<Clue>::iterator it_clue;
	cout << "clue = " << clue.clue_name() << endl;


	/* ---------------------------------------------------- */
	if (!clue.clue_name().compare("back"))
		backAction();
	else if (!clue.clue_name().compare("safe1") || !clue.clue_name().compare("key"))
		safeAction(clue);
	else if (!clue.clue_name().compare("cardD"))
		cardDAction(clue);
	else if (!clue.clue_name().compare("cardS") || !clue.clue_name().compare("paint"))
		PaintAction(clue);
	else if (!clue.clue_name().compare("cardP") || !clue.clue_name().compare("curtain1") || !clue.clue_name().compare("curtain2") || !clue.clue_name().compare("curtain3") || !clue.clue_name().compare("curtain_down") || !clue.clue_name().compare("curtain_up"))
		curtainAction(clue);
	else if (!clue.clue_name().compare("card_num1"))
		card_num1Action(clue);
	else if (!clue.clue_name().compare("card_num2"))
		card_num2Action(clue);
	else if (!clue.clue_name().compare("card_num3") || !clue.clue_name().compare("boat"))
		BoatAction(clue);
	else if (!clue.clue_name().compare("pillow") || !clue.clue_name().compare("pillow_paper") || !clue.clue_name().compare("pillow_nearscene_back"))
		pillowAction(clue);
	else if (!clue.clue_name().compare("closet") || !clue.clue_name().compare("open_closet") || !clue.clue_name().compare("inside_closet")  )
		closetAction(clue);
	else if (!clue.clue_name().compare("guitar"))
		guitarAction();
	else if (!clue.clue_name().compare("Blue_shelf_Top"))
		Blue_shelf_TopAction(clue);
	else if (!clue.clue_name().compare("Blue_shelf_Mid") || !clue.clue_name().compare("DSP") || !clue.clue_name().compare("Computer_Networks"))
		Blue_shelf_MidAction(clue);
	else if (!clue.clue_name().compare("Blue_shelf_bottom") || !clue.clue_name().compare("math") || !clue.clue_name().compare("calculus") || !clue.clue_name().compare("probability"))
		Blue_shelf_buttonAction(clue);
	else if (!clue.clue_name().compare("Orange_shelf_Top"))
		Orange_shelf_TopAction();
	else if (!clue.clue_name().compare("Orange_shelf_Mid"))
		Orange_shelf_MidAction();
	else if (!clue.clue_name().compare("Orange_shelf_bottom"))
		Orange_shelf_buttonAction();
	else if (!clue.clue_name().compare("Green_shelf_Top"))
		Green_shelf_TopAction();
	else if (!clue.clue_name().compare("Green_shelf_Mid"))
		Green_shelf_MidAction();
	else if (!clue.clue_name().compare("Green_shelf_bottom"))
		Green_shelf_buttonAction();
	else if (!clue.clue_name().compare("Wood_shelf"))
		Wood_shelfAction();
	else if (!clue.clue_name().compare("Wood_shelf_Top"))
		Wood_shelf_TopAction();
	else if (!clue.clue_name().compare("Wood_shelf_Mid"))
		Wood_shelf_MidAction();
	else if (!clue.clue_name().compare("Wood_shelf_button"))
		Wood_shelf_buttonAction();
	else if (!clue.clue_name().compare("lamp"))
		LampAction();
	else if (!clue.clue_name().compare("memo"))
		MemoAction();
	else if (!clue.clue_name().compare("start"))
		StartAction();
	else if (!clue.clue_name().compare("present"))
		PresentAction();

	/* safe type code ---------------------------------------------------------------*/
	for (it_clue = ClueSafeTypeCode1.begin(); it_clue != ClueSafeTypeCode1.end(); ++it_clue)
	{
		if (!clue.clue_name().compare(it_clue->clue_name()))
			safeAction(clue);
	}

	/* book type page ------------------------------------------------------------------*/
	for (it_clue = ClueBookInside.begin(); it_clue != ClueBookInside.end(); ++it_clue)
	{
		if (!clue.clue_name().compare(it_clue->clue_name()) && current_book == ADSP)
			DSPAction(clue);
		else if (!clue.clue_name().compare(it_clue->clue_name()) && current_book == COMPUTER)
			Computer_NetworksAction(clue);
		else if (!clue.clue_name().compare(it_clue->clue_name()) && current_book == MATH)
			mathAction(clue);
		else if (!clue.clue_name().compare(it_clue->clue_name()) && current_book == CALCULUS)
			calculusAction(clue);
		else if (!clue.clue_name().compare(it_clue->clue_name()) && current_book == PROBABILITY)
			probabilityAction(clue);
	}
	
	display();
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
			break;
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
		if (x > it_clue->get_2D_coordinate()[0].x*width && x<it_clue->get_2D_coordinate()[1].x*width && y>it_clue->get_2D_coordinate()[0].y*height && y < it_clue->get_2D_coordinate()[1].y*height){
			changeState(*it_clue);
			break;
		}

	}
}

