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
#define NO_3DOBJ_PATH -1

#define NOT_SHOW_CLUE -2	//clue will not be shown in these scenes
#define CLUE_FILE_END 111111	//the end of one clue file

//clue state code
#define SHOW_ON_SCENE		0
#define NOT_SHOW			1
#define SHOW_IN_CLUEBOX		2
#define CHANGE_IMG			3
#define SHOW_ANIMATION		4
#define SHOW_DIALOG			5
#define SHOW_NEAR_SCENE		6
#define TYPE_CODE			7


//cluebox
#define SPACE 0.03		//clue in the clue box space(horizon and vertical is both 0.03% of the screen height)
#define BOX_HEIGHT 0.2
#define BOX_WIDTH 1
#define ITEM_WIDTH 0.09	//clue in clue box is a square (width is 0.09% of the screen height)
#define ARROW_WIDTH 0.02

//mouse state
#define ROOM				0
#define NEARSCENE			1
#define TYPECODE			2
#define BOOKINSIDE			3
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


/* safe1 code */
#define CODE0	8
#define CODE1	7
#define CODE2	8
#define CODE3	7


#define DIST 5
#define OFFSET -2


/* game state */
#define STATE1	1
#define STATE2	2
#define STATE3	3
#define STATE4	4



/* clue in room */
#define INROOM_SAFE				0
#define INROOM_CARDD			1
#define INROOM_CARD7			2
#define INROOM_CARD2			3
#define INROOM_CURTAIN			4
#define INROOM_PILLOW			5
#define INROOM_CLOSET			6
#define INROOM_GUITAR			7
#define INROOM_BLUESHELF1		8
#define INROOM_BLUESHELF2		9
#define INROOM_BLUESHELF3		10
#define INROOM_ORANGESHELF1		11
#define INROOM_ORANGESHELF2		12
#define INROOM_ORANGESHELF3		13
#define INROOM_GREENSHELF1		14
#define INROOM_GREENSHELF2		15
#define INROOM_GREENSHELF3		16
#define INROOM_WOODSHELF		17
#define INROOM_BOAT				18
#define INROOM_PAINT			19



/* blue sheif book chosen */
#define NOT_CHOOSE		-1
#define ADSP			0
#define COMPUTER		1
#define MATH			2
#define CALCULUS		3
#define PROBABILITY		4

#endif