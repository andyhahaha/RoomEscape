#ifndef _DEFINE_H
#define _DEFINE_H

/*Position Setting--------------------------------*/

//stitch direction
#define STITCH2_LEFT 0
#define STITCH2_RIGHT 1
#define STITCH2_UP 2
#define STITCH2_DOWN 3
#define STITCH2_LEFT_UP 4
#define STITCH2_LEFT_DOWN 5
#define STITCH2_RIGHT_UP 6
#define STITCH2_RIGHT_DOWN 7

//match A to B or B to A
#define MATCH_LEFT_TO_RIGHT 0
#define MATCH_RIGHT_TO_LEFT 1

#define METHOD1 1
#define METHOD2 2
#define METHOD3 3
#define METHOD4 4	//stitch by H path
#define BLEND_LEFT 0
#define BLEND_RIGHT 1

//horizontal¡Blook up 20¡Blook down 20¡Blook down 40
#define VERTICAL_UP_20 0
#define VERTICAL_CENTRAL 1
#define VERTICAL_DOWN_20 2
#define VERTICAL_DOWN_40 3

//stitch_part
#define STITCH_SCREEN_TOP 1
#define STITCH_SCREEN_MID 2
#define STITCH_SCREEN_BOTTOM 3

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 625
#define IMG_WIDTH 480
#define IMG_HEIGHT 270

/*#define STITCH_SCREEN_WIDTH 4800
#define STITCH_SCREEN_HEIGHT 2700
#define IMG_REAL_WIDTH 1920
#define IMG_REAL_HEIGHT 1080*/

#define STITCH_SCREEN_WIDTH 2400
#define STITCH_SCREEN_HEIGHT 1250
#define STITCH_IMG_WIDTH 960
#define STITCH_IMG_HEIGHT 540


/*Clue Setting--------------------------------*/

#define NOT_SHOW_CLUE -2	//clue will not be shown in these scenes
#define CLUE_FILE_END 111111	//the end of one clue file

//clue state code
#define SHOW_ON_SCENE 0
#define NOT_SHOW 1
#define SHOW_IN_CLUEBOX 2
#define CHANGE_IMG 3
#define SHOW_ANIMATION 4
#define SHOW_DIALOG 5
#define SHOW_NEAR_SCENCE 6
#define TYPE_CODE 7


//cluebox
#define SPACE 0.03		//clue in the clue box space(horizon and vertical is both 0.03% of the screen height)
#define BOX_HEIGHT 0.2
#define BOX_WIDTH 1
#define ITEM_WIDTH 0.14	//clue in clue box is a square (width is 0.14% of the screen height)
#define ARROW_WIDTH 0.02

//near scence
#define ROOM				0
#define NEARSCENCE			1
/*#define DRAWER_ST			1
#define DRAWER_ED			2
#define DRAWER_RD			3
#define BLUESHELF_TOP		4
#define BLUESHELF_MID		5
#define BLUESHELF_BTN		6
#define ORANGESHELF_TOP		7
#define ORANGESHELF_MID		8
#define ORANGESHELF_BTN		9
#define GREENSHELF_TOP		10	
#define GREENSHELF_MID		11
#define GREENSHELF_BTN		12	
#define WOODSHELF_TOP		13
#define WOODSHELF_MID		14
#define WOODSHELF_BTN		15
#define CLOSET				16
#define PILLOW				17
#define CURTAIN				18*/


#define DIST 5
#define OFFSET -2
#endif