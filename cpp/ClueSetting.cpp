#include "D:\RoomEscape\h\gameRun.h"

/* Set the 4 corner of the near scene in room 
*  The coordinate is 3D coordinate.
*/
vector<Point3f> set_corner(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
	vector<Point3f> obj_corner;
	Point3f point;
	point.x = x1;
	point.y = y1;
	point.z = z1;
	obj_corner.push_back(point);
	point.x = x2;
	point.y = y2;
	point.z = z2;
	obj_corner.push_back(point);
	point.x = x3;
	point.y = y3;
	point.z = z3;
	obj_corner.push_back(point);
	point.x = x4;
	point.y = y4;
	point.z = z4;
	obj_corner.push_back(point);
	return obj_corner;
}


/* Set the 2 corner of the clue in near scene. 
*  The coordinate is screen coordinate.
*/
vector<Point2i> set_coordinate(int x1, int y1, int x2, int y2)
{
	vector<Point2i> coordinate;
	Point2d point;
	point.x = x1;
	point.y = y1;
	coordinate.push_back(point);
	point.x = x2;
	point.y = y2;
	coordinate.push_back(point);

	return coordinate;
}




/*set clue */
void clueSetting()
{
	string room_name = "room";
	int position_num = 0;
	vector<Point3f> corner;
	vector<Point2i> coordinate;

	/*3D OBJ*/
	Clue safe1, key;
	Clue safe1_1, safe1_2, safe1_3, safe1_4, safe1_5, safe1_6, safe1_7, safe1_8, safe1_9, safe1_OK, safe1_clear;
	Clue cardD, cardS, cardP;
	Clue card_num1, card_num2, card_num3;
	Clue back;
	
	
	/* safe		ClueInRoom[0] */
	safe1.set_clue(room_name, position_num, "safe1", 22, 73, 22, 73, 15.3917, -0.746502, 1.45153, 0, 180, 0, 2.0);
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_closed.obj");
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_open.obj");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_typecode.jpg");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_open_key.jpg");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_open.jpg");
	list_id.push_back(drawObject(glm_model, safe1, 0));
	ClueInRoom.push_back(safe1);


	coordinate = set_coordinate(960, 505, 1025, 550);
	back.set_clue(room_name, position_num, "back", coordinate);
	ClueSafeTypeCode1.push_back(back);

	coordinate = set_coordinate(470, 275, 510, 310);
	safe1_OK.set_clue(room_name, position_num, "OK", coordinate);
	ClueSafeTypeCode1.push_back(safe1_OK);

	coordinate = set_coordinate(470, 275, 510, 310);
	safe1_clear.set_clue(room_name, position_num, "clear", coordinate);
	ClueSafeTypeCode1.push_back(safe1_clear);

	coordinate = set_coordinate(470, 275, 510, 310);
	safe1_1.set_clue(room_name, position_num, "1", coordinate);
	ClueSafeTypeCode1.push_back(safe1_1);

	coordinate = set_coordinate(525, 275, 565, 310);
	safe1_2.set_clue(room_name, position_num, "2", coordinate);
	ClueSafeTypeCode1.push_back(safe1_2);

	coordinate = set_coordinate(580, 275, 620, 310);
	safe1_3.set_clue(room_name, position_num, "3", coordinate);
	ClueSafeTypeCode1.push_back(safe1_3);

	coordinate = set_coordinate(300, 0, 100, 100);
	safe1_4.set_clue(room_name, position_num, "4", coordinate);
	ClueSafeTypeCode1.push_back(safe1_4);

	coordinate = set_coordinate(400, 0, 100, 100);
	safe1_5.set_clue(room_name, position_num, "5", coordinate);
	ClueSafeTypeCode1.push_back(safe1_5);

	coordinate = set_coordinate(500, 0, 100, 100);
	safe1_6.set_clue(room_name, position_num, "6", coordinate);
	ClueSafeTypeCode1.push_back(safe1_6);

	coordinate = set_coordinate(600, 0, 100, 100);
	safe1_7.set_clue(room_name, position_num, "7", coordinate);
	ClueSafeTypeCode1.push_back(safe1_7);

	coordinate = set_coordinate(700, 0, 100, 100);
	safe1_8.set_clue(room_name, position_num, "8", coordinate);
	ClueSafeTypeCode1.push_back(safe1_8);

	coordinate = set_coordinate(800, 0, 100, 100);
	safe1_9.set_clue(room_name, position_num, "9", coordinate);
	ClueSafeTypeCode1.push_back(safe1_9);


	/* key		ClueInRoom[1] */
	/*key.set_clue(room_name, position_num, "key", 133, 14, 133, 14, -2 * DIST, 3 * DIST, -3 * DIST, 0, 0, 0, 1.0);
	key.next_state(NOT_SHOW);
	key.add_3Dobj_path("D:\\resource\\3D\\key.obj");
	list_id.push_back(drawObject(glm_model, key, 0));
	ClueInRoom.push_back(key);*/

	/* card			ClueInRoom[2~7] */
	cardD.set_clue(room_name, position_num, "cardD", 82, 136, 80, 140, -12.2961, -9.70452, 16.0501, 0, 180, 0, 1.0);
	cardD.add_3Dobj_path("D:\\resource\\3D\\cardD.obj");
	cardD.set_cluebox_img("D:\\resource\\2D\\D.PNG");
	list_id.push_back(drawObject(glm_model, cardD, 0));
	ClueInRoom.push_back(cardD);

	/*cardS.set_clue(room_name, position_num, "cardS", 139, 21, 139, 21, -1.1*DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	cardS.add_3Dobj_path("D:\\resource\\3D\\cardS.obj");
	cardS.set_cluebox_img("D:\\resource\\2D\\S.png");
	list_id.push_back(drawObject(glm_model, cardS, 0));
	ClueInRoom.push_back(cardS);*/

	/*cardP.set_clue(room_name, position_num, "cardP", 147, 29, 147, 29, -0.2*DIST, -0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	cardP.add_3Dobj_path("D:\\resource\\3D\\cardP.obj");
	cardP.set_cluebox_img("D:\\resource\\2D\\P.png");
	list_id.push_back(drawObject(glm_model, cardP, 0));
	ClueInRoom.push_back(cardP);*/

	card_num1.set_clue(room_name, position_num, "card_num1", 156, 37, 156, 37, 8.84962, -11.6952, -13.1585, 270, 0, 0, 0.7);
	card_num1.add_3Dobj_path("D:\\resource\\3D\\7.obj");
	card_num1.set_cluebox_img("D:\\resource\\2D\\7.png");
	list_id.push_back(drawObject(glm_model, card_num1, 0));
	ClueInRoom.push_back(card_num1);

	card_num2.set_clue(room_name, position_num, "card_num2", -1, -1, 112, 155, -9.38933, -16.8268, 0.622, 0, 270, 0, 2.0);
	card_num2.add_3Dobj_path("D:\\resource\\3D\\2.obj");
	card_num2.set_cluebox_img("D:\\resource\\2D\\2.png");
	list_id.push_back(drawObject(glm_model, card_num2, 0));
	ClueInRoom.push_back(card_num2);

	/*card_num3.set_clue(room_name, position_num, "card_num3", -1, -1, 108, 157, -9.38933, -16.8268, 0.622, 0, 270, 0, 2.0);
	card_num3.add_3Dobj_path("D:\\resource\\3D\\3.obj");
	card_num3.set_cluebox_img("D:\\resource\\2D\\3.png");
	list_id.push_back(drawObject(glm_model, card_num3, 0));
	ClueInRoom.push_back(card_num3);*/


	/*near scene*/
	Clue curtain;
	Clue pillow;
	Clue boat;
	Clue paint;
	Clue Blue_shelf_Top, Blue_shelf_Mid, Blue_shelf_bottom;
	Clue textbook;
	Clue Orange_shelf_Top, Orange_shelf_Mid, Orange_shelf_bottom;
	Clue Green_shelf_Top, Green_shelf_Mid, Green_shelf_bottom;
	Clue Wood_shelf;
	Clue Wood_shelf_Top, Wood_shelf_Mid, Wood_shelf_bottom;


	/* curtain		ClueInRoom[8] */
	corner = set_corner(-3.19343, 15.5143, -15.0661, 5.64898, 16.1634, -15.6844, 5.84995, 0.778958, -15.6985, -3.52837, 0.649132, -15.0427);
	curtain.set_clue(room_name, position_num, "curtain", 147, 32, 147, 32, corner);
	ClueInRoom.push_back(curtain);


	/* pillow		ClueInRoom[9] */
	corner = set_corner(-12.2539, -12.2539, -9.95853, -9.57411, -8.58477, -12.0522, -7.74, -9.76673, -13.4821, -10.097, -13.6859, -11.6437);
	pillow.set_clue(room_name, position_num, "pillow", 143, 0, 143, 0, corner);
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\pillow0_2.jpg");
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\pillow1_2.jpg");
	ClueInRoom.push_back(pillow);

	
	/*book shelf*/

	/*Blue*/
	corner = set_corner(14.9873, -3.9595, -11.8497, 15.1778, -3.75, -6.39466, 15.1778, -8.65738, -6.3946, 14.9888, -8.7244, -11.805);
	Blue_shelf_Top.set_clue(room_name, position_num, "Blue_shelf_Top", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Top);

	coordinate = set_coordinate(0, 0, 100, 100);
	textbook.set_clue(room_name, position_num, "textbook", coordinate);
	ClueInBlueShelfTop.push_back(textbook);

	ClueInBlueShelfTop.push_back(back);

	//************************************************************
	corner = set_corner(15.3917, -10.0156, -10.3266
		,15.3917, -9.89115, -5.64023
		,15.3917, -13.3126, -10.4925
		,15.3917, -13.3126, -5.22551);
	Blue_shelf_Mid.set_clue(room_name, position_num, "Blue_shelf_Mid", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Mid);


	ClueInBlueShelfMid.push_back(back);
	//************************************************************

	Blue_shelf_bottom.set_clue(room_name, position_num, "Blue_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Blue_shelf_bottom);

	ClueInBlueShelfBtn.push_back(back);
	//************************************************************


	/*Orange*/
	corner = set_corner(15.3917, -5.1633, 2.32245
		,15.3917, -4.85226, 6.46968
		,15.3917, -8.29393, 2.252981
		,15.3917, -7.71385, 6.30379);
	Orange_shelf_Top.set_clue(room_name, position_num, "Orange_shelf_Top", 27, 81, 27, 81, corner);
	ClueInRoom.push_back(Orange_shelf_Top);
	ClueInOrangeShelfTop.push_back(back);
	//************************************************************

	corner = set_corner(15.3917, -9.33127, 2.28098
		,15.3917, -9.02023, 6.46948
		,15.3917, -13.1882, 2.15656
		,15.3917, -13.0638, 6.34526);
	Orange_shelf_Mid.set_clue(room_name, position_num, "Orange_shelf_Mid", 33, 75, 33, 75, corner);
	ClueInRoom.push_back(Orange_shelf_Mid);
	ClueInOrangeShelfMid.push_back(back);
	//************************************************************

	Orange_shelf_bottom.set_clue(room_name, position_num, "Orange_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Orange_shelf_bottom);

	ClueInOrangeShelfBtn.push_back(back);
	//************************************************************

	/*Green*/
	corner = set_corner(15.3917, -5.03889, 10.534
		,15.3917, -5.03889, 13.8932
		,15.3917, -839814, 10.5754
		,15.3917, -8.3359, 13.8518);
	Green_shelf_Top.set_clue(room_name, position_num, "Green_shelf_Top", 36, 95, 33, 97, corner);
	ClueInRoom.push_back(Green_shelf_Top);
	ClueInGreenShelfTop.push_back(back);
	//************************************************************
	corner = set_corner(15.3917, -10.0156, 10.4096
		,15.3917, -10.0156, 13.6859
		,15.3917, -13.126, 10.2851
		,15.3917, -13.126, 13.6444);
	Green_shelf_Mid.set_clue(room_name, position_num, "Green_shelf_Mid", 40, 91, 179, 62, corner);
	ClueInRoom.push_back(Green_shelf_Mid);
	ClueInGreenShelfMid.push_back(back);
	//************************************************************
	Green_shelf_bottom.set_clue(room_name, position_num, "Green_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Green_shelf_bottom);
	ClueInGreenShelfBtn.push_back(back);
	//************************************************************

	/*Wood*/
	corner = set_corner(-15.3917, -5.66097, 14.93
		,-15.3917, -5.59876, 10.534
		,-15.3917, -10.3888, 15.0545
		,-15.3917, -10.451, 14.9715);
	Wood_shelf.set_clue(room_name, position_num, "Wood_shelf", 86, 146, 86, 146, corner);
	ClueInRoom.push_back(Wood_shelf);
	ClueInWoodShelf.push_back(back);
	
	//************************************************************
	Wood_shelf_Top.set_clue(room_name, position_num, "Wood_shelf_Top", 0, 180, 0, 180, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	//ClueInWoodShelf.push_back(Wood_shelf_Top);
	//************************************************************
	Wood_shelf_Mid.set_clue(room_name, position_num, "Wood_shelf_Mid", 0, 180, 0, 180, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	//ClueInWoodShelf.push_back(Wood_shelf_Mid);
	//************************************************************
	Wood_shelf_bottom.set_clue(room_name, position_num, "Wood_shelf_bottom", 0, 180, 0, 180, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	//ClueInWoodShelf.push_back(Wood_shelf_bottom);
	//************************************************************


	/*boat*/
	corner = set_corner(-15.3917, 0.31104, 13.1467
		,-15.3917, 0.559876, 10.7828
		,-15.3917, -3.04822, 10.7413
		,-15.3917, -3.2975, 13.1882);
	boat.set_clue(room_name, position_num, "boat", 87, 145,87 , 145, corner);
	ClueInRoom.push_back(boat);
	ClueInBoat.push_back(back);


	/*paint*/
	corner = set_corner(-15.3917, 2.1773, -0.290306
		,-15.3917, 2.30171, -3.02748
		,-15.3917, 0.311042, -2.94453
		,-15.3917, 0.0622085, -0.497668);
	paint.set_clue(room_name, position_num, "paint", 109, 168, 109, 168, corner);
	ClueInRoom.push_back(paint);
	ClueInPaint.push_back(back);




}
