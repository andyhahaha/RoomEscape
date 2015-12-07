#include "D:\RoomEscape\h\gameRun.h"

Clue back;


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
	
	
	/* safe		ClueInRoom[0] */
	safe1.set_clue(room_name, position_num, "safe1", 22, 73, 22, 73, 15.3917, -3.00133, 2.017423, 0, 180, 0, 2.0);
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_closed.obj");
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_open.obj");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_typecode_small.jpg");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_open_key.jpg");
	safe1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\safe1_open.jpg");
	list_id.push_back(drawObject(glm_model, safe1, 0));
	list_id_show.push_back(safe1.current_state());
	ClueInRoom.push_back(safe1);


	/* ClueSafeTypeCode1 */
	coordinate = set_coordinate(0.888888889*width, 0.701388889*height, 0.949074074*width, 0.763888889*height);
	back.set_clue(room_name, position_num, "back", coordinate);
	ClueSafeTypeCode1.push_back(back);

	coordinate = set_coordinate(0.442592593*width, 0.3375*height, 0.47962963*width, 0.393055556*height);
	safe1_OK.set_clue(room_name, position_num, "OK", coordinate);
	ClueSafeTypeCode1.push_back(safe1_OK);

	coordinate = set_coordinate(0.535185185*width, 0.343055556*height, 0.571296296*width, 0.397222222*height);
	safe1_clear.set_clue(room_name, position_num, "clear", coordinate);
	ClueSafeTypeCode1.push_back(safe1_clear);

	coordinate = set_coordinate(0.442592593*width, 0.438888889*height, 0.477777778*width, 0.486111111*height);
	safe1_1.set_clue(room_name, position_num, "1", coordinate);
	ClueSafeTypeCode1.push_back(safe1_1);

	coordinate = set_coordinate(0.488888889*width, 0.440277778*height, 0.523148148*width, 0.488888889*height);
	safe1_2.set_clue(room_name, position_num, "2", coordinate);
	ClueSafeTypeCode1.push_back(safe1_2);

	coordinate = set_coordinate(0.535185185*width, 0.438888889*height, 0.57037037*width, 0.4875*height);
	safe1_3.set_clue(room_name, position_num, "3", coordinate);
	ClueSafeTypeCode1.push_back(safe1_3);

	coordinate = set_coordinate(0.439814815*width, 0.505555556*height, 0.475925926*width, 0.555555556*height);
	safe1_4.set_clue(room_name, position_num, "4", coordinate);
	ClueSafeTypeCode1.push_back(safe1_4);

	coordinate = set_coordinate(0.487037037*width, 0.505555556*height, 0.521296296*width, 0.554166667*height);
	safe1_5.set_clue(room_name, position_num, "5", coordinate);
	ClueSafeTypeCode1.push_back(safe1_5);

	coordinate = set_coordinate(0.535185185*width, 0.504166667*height, 0.57037037*width, 0.554166667*height);
	safe1_6.set_clue(room_name, position_num, "6", coordinate);
	ClueSafeTypeCode1.push_back(safe1_6);

	coordinate = set_coordinate(0.439814815*width, 0.576388889*height, 0.475*width, 0.626388889*height);
	safe1_7.set_clue(room_name, position_num, "7", coordinate);
	ClueSafeTypeCode1.push_back(safe1_7);

	coordinate = set_coordinate(0.487037037*width, 0.573611111*height, 0.523148148*width, 0.625*height);
	safe1_8.set_clue(room_name, position_num, "8", coordinate);
	ClueSafeTypeCode1.push_back(safe1_8);

	coordinate = set_coordinate(0.535185185*width, 0.572222222*height, 0.569444444*width, 0.623611111*height);
	safe1_9.set_clue(room_name, position_num, "9", coordinate);
	ClueSafeTypeCode1.push_back(safe1_9);


	/* ClueSafeOpen1 */
	ClueSafeOpen1.push_back(back);
	//ClueSafeOpen1.push_back(back);


	/* key		ClueInRoom[1] */
	key.set_clue(room_name, position_num, "key", 133, 14, 133, 14, -2 * DIST, 3 * DIST, -3 * DIST, 0, 0, 0, 1.0);
	key.next_state(NOT_SHOW);
	key.add_3Dobj_path("D:\\resource\\3D\\key.obj");
	list_id.push_back(drawObject(glm_model, key, 0));
	list_id_show.push_back(key.current_state());
	ClueInRoom.push_back(key);

	/* card			ClueInRoom[2~7] */
	cardD.set_clue(room_name, position_num, "cardD", 82, 136, 80, 140, -9.73474, -8.14931, 11.924, 0, 180, 0, 1.0);
	cardD.add_3Dobj_path("D:\\resource\\3D\\cardD.obj");
	cardD.set_cluebox_img("D:\\resource\\2D\\D_small.PNG");
	list_id.push_back(drawObject(glm_model, cardD, 0));
	list_id_show.push_back(cardD.current_state());
	ClueInRoom.push_back(cardD);


	coordinate = set_coordinate(0.426851852*width, 0.302777778*height, 0.487037037*width, 0.4125*height);
	cardS.set_clue(room_name, position_num, "cardS", coordinate);
	cardS.set_cluebox_img("D:\\resource\\2D\\S_small.png");
	ClueInPaint.push_back(cardS);



	coordinate = set_coordinate(0.677777778*width, 0.575*height, 0.703703704*width, 0.620833333*height);
	cardP.set_clue(room_name, position_num, "cardP", coordinate);
	cardP.set_cluebox_img("D:\\resource\\2D\\P.png");
	ClueInCurtain.push_back(cardP);


	card_num1.set_clue(room_name, position_num, "card_num1", 156, 37, 156, 37, 1.32711, -8.77139, -15.3917, 0, 0, 0, 0.7);
	card_num1.add_3Dobj_path("D:\\resource\\3D\\7.obj");
	card_num1.set_cluebox_img("D:\\resource\\2D\\7_small.png");
	list_id.push_back(drawObject(glm_model, card_num1, 0));
	list_id_show.push_back(card_num1.current_state());
	ClueInRoom.push_back(card_num1);

	card_num2.set_clue(room_name, position_num, "card_num2", -1, -1, 112, 155, -8.93859, -16.0023, 0.53914, 0, 270, 0, 2.0);
	card_num2.add_3Dobj_path("D:\\resource\\3D\\2.obj");
	card_num2.set_cluebox_img("D:\\resource\\2D\\2_small.png");
	list_id.push_back(drawObject(glm_model, card_num2, 0));
	list_id_show.push_back(card_num2.current_state());
	ClueInRoom.push_back(card_num2);

	coordinate = set_coordinate(0.348148148*width, 0.290277778*height, 0.439814815*width, 0.473611111*height);
	card_num3.set_clue(room_name, position_num, "card_num3", coordinate);
	card_num3.set_cluebox_img("D:\\resource\\2D\\3.png");
	ClueInBoat.push_back(card_num3);

	/*near scene*/
	Clue curtain;
	Clue pillow, pillow_papper, pillow_nearscene_back;
	Clue guitar;
	Clue closet;
	Clue boat;
	Clue paint;
	Clue Blue_shelf_Top, Blue_shelf_Mid, Blue_shelf_bottom;
	Clue DSP, Computer_Networks, probability, calculus, math;
	Clue textbook;
	Clue Orange_shelf_Top, Orange_shelf_Mid, Orange_shelf_bottom;
	Clue Green_shelf_Top, Green_shelf_Mid, Green_shelf_bottom;
	Clue Wood_shelf;
	Clue Wood_shelf_Top, Wood_shelf_Mid, Wood_shelf_bottom;


	/* curtain		ClueInRoom[8] */
	corner = set_corner(-5.59876, 15.801, -15.3917
		, 4.06429, 15.6143, -15.9317
		, 4.10576, -0.933127, -15.3917
		, 5.80612, -1.11975, -15.3917);
	curtain.set_clue(room_name, position_num, "curtain", 147, 32, 147, 32, corner);
	ClueInRoom.push_back(curtain);


	/* pillow		ClueInRoom[9] */
	corner = set_corner(-12.5246, -12.1307, -15.3917
		, -7.21618, -12.6905, -15.3917
		, -15.2618, -18.201, -7.77332
		, -9.49716, -17.9261, -7.91897);
	pillow.set_clue(room_name, position_num, "pillow", 143, 0, 143, 0, corner);
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\pillow0_2.jpg");
	//pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\pillow1_2.jpg");
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\PillowWithPaper.jpg");
	ClueInRoom.push_back(pillow);

	coordinate = set_coordinate(0.871296*width, 0.4125*height, 0.939814*width, 0.68472222*height);
	pillow_papper.set_clue(room_name, position_num, "pillow_paper", coordinate);
	ClueInPillow.push_back(pillow_papper);

	coordinate = set_coordinate(0.888888889*width, 0.701388889*height, 0.949074074*width, 0.763888889*height);
	pillow_nearscene_back.set_clue(room_name, position_num, "pillow_nearscene_back", coordinate);
	ClueInPillow.push_back(pillow_nearscene_back);

	/*closet*/
	corner = set_corner(2.82012, 8.7099, 15.3917
		, -9.746, 8.52256, 15.3917
		, -9.58011, -10.5132, 15.3917
		, 2.32245, -10.5132, 15.3917);
	closet.set_clue(room_name, position_num, "closet", 70, 135, 69, 133, corner);
	ClueInRoom.push_back(closet);

	/*guitar*/
	corner = set_corner(8.12857, 3.60809, -15.3917
		, 10.534, 3.60809, -15.3917
		, 11.7781, -10.2022, -15.3917
		, 7.63091, -9.5179, -15.3917);
	guitar.set_clue(room_name, position_num, "guitar", 166, 44, 164, 45, corner);
	ClueInRoom.push_back(guitar);
	
	/*book shelf*/

	/*Blue*/
	corner = set_corner(15.3917, -6.5941, -10.4096
		, 15.3917, -6.34526, -5.47434
		, 15.3917, -10.451, -5.51582
		, 15.3917, -10.5754, -10.3681);
	Blue_shelf_Top.set_clue(room_name, position_num, "Blue_shelf_Top", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Top);

	coordinate = set_coordinate(0, 0, 100, 100);
	textbook.set_clue(room_name, position_num, "textbook", coordinate);
	ClueInBlueShelfTop.push_back(textbook);
	ClueInBlueShelfTop.push_back(back);

	//************************************************************
	corner = set_corner(15.3917, -11.633, -10.534
		, 15.3917, -11.5086, -5.51582
		, 15.3917, -15.4899, -5.51582
		, 15.3917, -15.4899, -10.534);
	Blue_shelf_Mid.set_clue(room_name, position_num, "Blue_shelf_Mid", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Mid);


	ClueInBlueShelfMid.push_back(back);
	coordinate = set_coordinate(0.531481481*width, 0.261111111*height, 0.611111111*width, 0.688888889*height);
	DSP.set_clue(room_name, position_num, "DSP", coordinate);
	ClueInBlueShelfMid.push_back(DSP);
	
	coordinate = set_coordinate(0.615740741*width, 0.279166667*height, 0.687962963*width, 0.6875*height);
	Computer_Networks.set_clue(room_name, position_num, "Computer_Networks", coordinate);
	ClueInBlueShelfMid.push_back(Computer_Networks);

	//************************************************************

	corner = set_corner(10.4534, -13.1441, -8.66771
		, 10.5117, -13.0342, -4.68637
		, 8.55987, -16.7169, -4.1887
		, 8.38508, -17.0467, -8.12857);
	Blue_shelf_bottom.set_clue(room_name, position_num, "Blue_shelf_bottom", -1, -1, 4, 61, corner);
	ClueInRoom.push_back(Blue_shelf_bottom);

	ClueInBlueShelfBtn.push_back(back);

	coordinate = set_coordinate(0.507407407*width, 0.231944444*height, 0.590740741*width, 0.716666667*height);
	math.set_clue(room_name, position_num, "math", coordinate);
	ClueInBlueShelfBtn.push_back(math);

	coordinate = set_coordinate(0.683333333*width, 0.188888889*height, 0.769444444*width, 0.729166667*height);
	calculus.set_clue(room_name, position_num, "calculus", coordinate);
	ClueInBlueShelfBtn.push_back(calculus);

	coordinate = set_coordinate(0.305555556*width, 0.280555556*height, 0.360185185*width, 0.681944444*height);
	probability.set_clue(room_name, position_num, "probability", coordinate);
	ClueInBlueShelfBtn.push_back(probability);
	

	//************************************************************


	/*Orange*/
	corner = set_corner(15.3917, -6.5941, 2.2098
		, 15.3917, -6.53189, 6.71852
		, 15.3917, -9.95336, 6.71852
		, 15.3917, -10.3888, 2.28098);
	Orange_shelf_Top.set_clue(room_name, position_num, "Orange_shelf_Top", 27, 81, 27, 81, corner);
	ClueInRoom.push_back(Orange_shelf_Top);
	ClueInOrangeShelfTop.push_back(back);
	//************************************************************

	corner = set_corner(15.3917, -11.1975, 2.23951
		, 15.3917, -11.0109, 6.67704
		, 15.3917, -15.4277, 6.67704
		, 15.3917, -15.4277, 2.19803);
	Orange_shelf_Mid.set_clue(room_name, position_num, "Orange_shelf_Mid", 33, 75, 33, 75, corner);
	ClueInRoom.push_back(Orange_shelf_Mid);
	ClueInOrangeShelfMid.push_back(back);
	//************************************************************
	corner = set_corner(10.3078, -13.419, 1.70037
		, 10.366, -13.309, 5.3914
		, 8.96772, -15.9474, 5.18404
		, 8.88032, -16.1123, 1.78331);
	Orange_shelf_bottom.set_clue(room_name, position_num, "Orange_shelf_bottom", -1, -1, 30, 83, corner);
	ClueInRoom.push_back(Orange_shelf_bottom);

	ClueInOrangeShelfBtn.push_back(back);
	//************************************************************

	/*Green*/
	corner = set_corner(15.3917, -6.22085, 10.2851
		, 15.3917, -6.34526, 14.1835
		, 15.3917, -10.6999, 14.1835
		, 15.3917, -10.8243, 10.2851);
	Green_shelf_Top.set_clue(room_name, position_num, "Green_shelf_Top", 36, 95, 33, 97, corner);
	ClueInRoom.push_back(Green_shelf_Top);
	ClueInGreenShelfTop.push_back(back);
	//************************************************************
	corner = set_corner(15.3917, -11.7574, 10.2022
		, 15.3917, -11.4464, 14.2665
		, 15.3917, -15.4277, 14.1006
		, 15.3917, -15.4277, 10.2022);
	Green_shelf_Mid.set_clue(room_name, position_num, "Green_shelf_Mid", 40, 91, 179, 62, corner);
	ClueInRoom.push_back(Green_shelf_Mid);
	ClueInGreenShelfMid.push_back(back);
	//************************************************************
	corner = set_corner(10.5117, -13.0342, 8.46035
		, 10.5117, -13.0342, 11.7367
		, 9.14251, -15.6176, 11.1561
		, 9.05512, -15.7825, 804563);
	Green_shelf_bottom.set_clue(room_name, position_num, "Green_shelf_bottom", -1, -1, 35, 98, corner);
	ClueInRoom.push_back(Green_shelf_bottom);
	ClueInGreenShelfBtn.push_back(back);
	//************************************************************

	/*Wood*/
	corner = set_corner(-15.3917, -6.90514, 15.2203
		, -15.3917, -6.65631, 10.3266
		, -15.3917, -15.3655, 13.9347
		, -15.3917, -15.4277, 15.2618);
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
	corner = set_corner(-15.3917, -0.870919, 13.2297
		, -15.3917, -0.684293, 10.8243
		, -15.3917, -4.47901, 10.9487
		, -15.3917, -4.72784, 13.2297);
	boat.set_clue(room_name, position_num, "boat", 87, 145,87 , 145, corner);
	ClueInRoom.push_back(boat);
	ClueInBoat.push_back(back);


	/*paint*/
	corner = set_corner(-15.3917, 1.11975, -0.331779
		, -15.3917, 1.43079, -2.98601
		, -15.3917, -1.30638, -2.98601
		, -15.3917, -1.43079, -0.497668);
	paint.set_clue(room_name, position_num, "paint", 109, 168, 109, 168, corner);
	ClueInRoom.push_back(paint);
	ClueInPaint.push_back(back);




}
