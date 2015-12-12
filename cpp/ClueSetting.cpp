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
vector<Point2f> set_coordinate(float x1, float y1, float x2, float y2)
{
	vector<Point2f> coordinate;
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
	vector<Point2f> coordinate;


	Clue start;

	coordinate = set_coordinate(0.888888889, 0.701388889, 0.949074074, 0.763888889);
	start.set_clue(room_name, position_num, "start", coordinate);
	ClueInStory.push_back(start);

	ClueOnScreen.assign(ClueInStory.begin(), ClueInStory.end());


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
	coordinate = set_coordinate(0.888888889, 0.701388889, 0.949074074, 0.763888889);
	back.set_clue(room_name, position_num, "back", coordinate);
	ClueSafeTypeCode1.push_back(back);

	coordinate = set_coordinate(0.442592593, 0.3375, 0.47962963, 0.393055556);
	safe1_OK.set_clue(room_name, position_num, "OK", coordinate);
	ClueSafeTypeCode1.push_back(safe1_OK);

	coordinate = set_coordinate(0.535185185, 0.343055556, 0.571296296, 0.397222222);
	safe1_clear.set_clue(room_name, position_num, "clear", coordinate);
	ClueSafeTypeCode1.push_back(safe1_clear);

	coordinate = set_coordinate(0.442592593, 0.438888889, 0.477777778, 0.486111111);
	safe1_1.set_clue(room_name, position_num, "1", coordinate);
	ClueSafeTypeCode1.push_back(safe1_1);

	coordinate = set_coordinate(0.488888889, 0.440277778, 0.523148148, 0.488888889);
	safe1_2.set_clue(room_name, position_num, "2", coordinate);
	ClueSafeTypeCode1.push_back(safe1_2);

	coordinate = set_coordinate(0.535185185, 0.438888889, 0.57037037, 0.4875);
	safe1_3.set_clue(room_name, position_num, "3", coordinate);
	ClueSafeTypeCode1.push_back(safe1_3);

	coordinate = set_coordinate(0.439814815, 0.505555556, 0.475925926, 0.555555556);
	safe1_4.set_clue(room_name, position_num, "4", coordinate);
	ClueSafeTypeCode1.push_back(safe1_4);

	coordinate = set_coordinate(0.487037037, 0.505555556, 0.521296296, 0.554166667);
	safe1_5.set_clue(room_name, position_num, "5", coordinate);
	ClueSafeTypeCode1.push_back(safe1_5);

	coordinate = set_coordinate(0.535185185, 0.504166667, 0.57037037, 0.554166667);
	safe1_6.set_clue(room_name, position_num, "6", coordinate);
	ClueSafeTypeCode1.push_back(safe1_6);

	coordinate = set_coordinate(0.439814815, 0.576388889, 0.475, 0.626388889);
	safe1_7.set_clue(room_name, position_num, "7", coordinate);
	ClueSafeTypeCode1.push_back(safe1_7);

	coordinate = set_coordinate(0.487037037, 0.573611111, 0.523148148, 0.625);
	safe1_8.set_clue(room_name, position_num, "8", coordinate);
	ClueSafeTypeCode1.push_back(safe1_8);

	coordinate = set_coordinate(0.535185185, 0.572222222, 0.569444444, 0.623611111);
	safe1_9.set_clue(room_name, position_num, "9", coordinate);
	ClueSafeTypeCode1.push_back(safe1_9);


	/* ClueSafeOpen1 */
	ClueSafeOpen1.push_back(back);


	/* key */
	key.set_clue(room_name, position_num, "key", 133, 14, 133, 14, -2 * DIST, 3 * DIST, -3 * DIST, 0, 0, 0, 1.0);
	key.next_state(NOT_SHOW);
	key.add_3Dobj_path("D:\\resource\\3D\\key.obj");
	//list_id.push_back(drawObject(glm_model, key, 0));
	//list_id_show.push_back(key.current_state());
	//ClueInRoom.push_back(key);


	/* card D		ClueInRoom[1] */	
	cardD.set_clue(room_name, position_num, "cardD", 82, 136, 80, 140, -9.73474, -8.14931, 11.924, 0, 180, 0, 1.0);
	cardD.add_3Dobj_path("D:\\resource\\3D\\cardD.obj");
	cardD.set_cluebox_img("D:\\resource\\2D\\D_small.PNG");
	list_id.push_back(drawObject(glm_model, cardD, 0));
	list_id_show.push_back(cardD.current_state());
	ClueInRoom.push_back(cardD);


	/* card 7		ClueInRoom[2] */
	card_num1.set_clue(room_name, position_num, "card_num1", 156, 37, 156, 37, 1.32711, -8.77139, -15.3917, 0, 0, 0, 0.7);
	card_num1.add_3Dobj_path("D:\\resource\\3D\\7.obj");
	card_num1.set_cluebox_img("D:\\resource\\2D\\7_small.png");
	list_id.push_back(drawObject(glm_model, card_num1, 0));
	list_id_show.push_back(card_num1.current_state());
	ClueInRoom.push_back(card_num1);

	/* card 2		ClueInRoom[3] */
	card_num2.set_clue(room_name, position_num, "card_num2", -1, -1, 112, 155, -8.93859, -16.0023, 0.53914, 0, 270, 0, 2.0);
	card_num2.add_3Dobj_path("D:\\resource\\3D\\2.obj");
	card_num2.set_cluebox_img("D:\\resource\\2D\\2_small.png");
	list_id.push_back(drawObject(glm_model, card_num2, 0));
	list_id_show.push_back(card_num2.current_state());
	ClueInRoom.push_back(card_num2);

	

	/*near scene*/
	Clue curtain1,curtain2,curtain3, curtain_down, curtain_up,memo;
	Clue pillow, pillow_papper, pillow_nearscene_back;
	Clue guitar;
	Clue lamp;
	Clue closet, open_closet, inside_closet;
	Clue boat;
	Clue paint;
	Clue Blue_shelf_Top, Blue_shelf_Mid, Blue_shelf_bottom;
	Clue BlueShelf_back;
	Clue DSP, Computer_Networks, probability, calculus, math;
	Clue Orange_shelf_Top, Orange_shelf_Mid, Orange_shelf_bottom;
	Clue Green_shelf_Top, Green_shelf_Mid, Green_shelf_bottom;
	Clue Wood_shelf;
	Clue Wood_shelf_Top, Wood_shelf_Mid, Wood_shelf_bottom;
	Clue book_0, book_1, book_2, book_3, book_4, book_5, book_6, book_7, book_8, book_9, book_OK, book_clear;


	/* curtain		ClueInRoom[4] */
	corner = set_corner(-5.59876, 15.801, -15.3917
		, -2.06429, 15.801, -15.9317
		, -2.10576, -0.933127, -15.3917
		, -5.80612, -1.11975, -15.3917);
	curtain1.set_clue(room_name, position_num, "curtain1", 143, 23, 148, 19, corner);
	curtain1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_closed.JPG");
	curtain1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open_P.JPG");
	curtain1.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open.JPG");
	ClueInRoom.push_back(curtain1);

	ClueInCurtainClosed.push_back(back);

	coordinate = set_coordinate(0.456481481, 0.434722222, 0.559259259, 0.622222222);
	memo.set_clue(room_name, position_num, "memo", coordinate);
	ClueInCurtainClosed.push_back(memo);

	coordinate = set_coordinate(0.219444444, 0.0125, 0.787037037, 0.840277778);
	curtain_down.set_clue(room_name, position_num, "curtain_down", coordinate);
	ClueInCurtainClosed.push_back(curtain_down);

	ClueInCurtainOpened.push_back(back);

	coordinate = set_coordinate(0.22037037, 0.0125, 7.663888889, 0.195833333);
	curtain_up.set_clue(room_name, position_num, "curtain_up", coordinate);
	ClueInCurtainOpened.push_back(curtain_up);

	coordinate = set_coordinate(0.22037037, 0.672222222, 0.705555556, 0.736111111);
	cardP.set_clue(room_name, position_num, "cardP", coordinate);
	cardP.set_cluebox_img("D:\\resource\\2D\\P.png");
	ClueInCurtainOpened.push_back(cardP);



	/* pillow		ClueInRoom[5] */
	corner = set_corner(-12.5246, -12.1307, -15.3917
		, -7.21618, -12.6905, -15.3917
		, -15.2618, -18.201, -7.77332
		, -9.49716, -17.9261, -7.91897);
	pillow.set_clue(room_name, position_num, "pillow", 143, 0, 143, 0, corner);
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\pillow.jpg");
	pillow.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\PillowPaper.jpg");
	ClueInRoom.push_back(pillow);

	coordinate = set_coordinate(0.871296, 0.4125, 0.939814, 0.68472222);
	pillow_papper.set_clue(room_name, position_num, "pillow_paper", coordinate);
	ClueInPillow.push_back(pillow_papper);

	coordinate = set_coordinate(0.888888889, 0.701388889, 0.949074074, 0.763888889);
	pillow_nearscene_back.set_clue(room_name, position_num, "pillow_nearscene_back", coordinate);
	ClueInPillow.push_back(pillow_nearscene_back);



	/*closet		ClueInRoom[6] */
	corner = set_corner(-3.60809, 8.58477, 15.3917
		, -9.746, 8.52256, 15.3917
		, -9.58011, -2.9861, 15.3917
		, -3.64957, 8.64698, 15.3917);
	closet.set_clue(room_name, position_num, "closet", 70, 132, 69, 130, corner);
	ClueInRoom.push_back(closet);

	coordinate = set_coordinate(0.400925926, 0.002777778, 0.912037037, 0.548611111);
	open_closet.set_clue(room_name, position_num, "open_closet", coordinate);
	ClueInClosetClosed.push_back(open_closet);
	ClueInClosetClosed.push_back(back);

	coordinate = set_coordinate(0.437962963, 0.476388889, 0.564814815, 0.581944444);
	inside_closet.set_clue(room_name, position_num, "inside_closet", coordinate);
	ClueInClosetOpen.push_back(inside_closet);
	ClueInClosetOpen.push_back(back);


	/*guitar		ClueInRoom[7] */
	corner = set_corner(8.12857, 3.60809, -15.3917
		, 10.534, 3.60809, -15.3917
		, 11.7781, -10.2022, -15.3917
		, 7.63091, -9.5179, -15.3917);
	guitar.set_clue(room_name, position_num, "guitar", 166, 44, 164, 45, corner);
	ClueInRoom.push_back(guitar);
	


	/*book shelf*/

	/*Blue*/
	/*BlueShelfTop		ClueInRoom[8] */
	corner = set_corner(15.3917, -6.5941, -10.4096
		, 15.3917, -6.34526, -5.47434
		, 15.3917, -10.451, -5.51582
		, 15.3917, -10.5754, -10.3681);
	Blue_shelf_Top.set_clue(room_name, position_num, "Blue_shelf_Top", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Top);

	//************************************************************
	/*BlueShelfMid		ClueInRoom[9] */
	corner = set_corner(15.3917, -11.633, -10.534
		, 15.3917, -11.5086, -5.51582
		, 15.3917, -15.4899, -5.51582
		, 15.3917, -15.4899, -10.534);
	Blue_shelf_Mid.set_clue(room_name, position_num, "Blue_shelf_Mid", 179, 62, 179, 62, corner);
	Blue_shelf_Mid.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Mid.JPG");
	ClueInRoom.push_back(Blue_shelf_Mid);

	ClueInBlueShelfMid.push_back(back);

	coordinate = set_coordinate(0.531481481, 0.261111111, 0.611111111, 0.688888889);
	DSP.set_clue(room_name, position_num, "DSP", coordinate);
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_cover.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_1.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_2.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_3.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_4.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_5.JPG");
	DSP.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\DSP_code.JPG");
	ClueInBlueShelfMid.push_back(DSP);
	
	coordinate = set_coordinate(0.615740741, 0.279166667, 0.687962963, 0.6875);
	Computer_Networks.set_clue(room_name, position_num, "Computer_Networks", coordinate);
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_cover.JPG");
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_1.JPG");
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_2.JPG");
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_3.JPG");
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_4.JPG");
	Computer_Networks.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\computer_5.JPG");
	ClueInBlueShelfMid.push_back(Computer_Networks);

	//************************************************************
	/*BlueShelfBottom		ClueInRoom[10] */
	corner = set_corner(10.4534, -13.1441, -8.66771
		, 10.5117, -13.0342, -4.68637
		, 8.55987, -16.7169, -4.1887
		, 8.38508, -17.0467, -8.12857);
	Blue_shelf_bottom.set_clue(room_name, position_num, "Blue_shelf_bottom", -1, -1, 4, 61, corner);
	Blue_shelf_bottom.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Blue_Shelf_Button.JPG");
	ClueInRoom.push_back(Blue_shelf_bottom);

	ClueInBlueShelfBtm.push_back(back);

	coordinate = set_coordinate(0.507407407, 0.231944444, 0.590740741, 0.716666667);
	math.set_clue(room_name, position_num, "math", coordinate);
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_cover.JPG");
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_1.JPG");
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_2.JPG");
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_3.JPG");
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_4.JPG");
	math.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\math_5.JPG");
	ClueInBlueShelfBtm.push_back(math);

	coordinate = set_coordinate(0.683333333, 0.188888889, 0.769444444, 0.729166667);
	calculus.set_clue(room_name, position_num, "calculus", coordinate);
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_cover.JPG");
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_1.JPG");
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_2.JPG");
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_3.JPG");
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_4.JPG");
	calculus.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\calculus_5.JPG");
	ClueInBlueShelfBtm.push_back(calculus);

	coordinate = set_coordinate(0.305555556, 0.280555556, 0.360185185, 0.681944444);
	probability.set_clue(room_name, position_num, "probability", coordinate);
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_cover.JPG");
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_1.JPG");
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_2.JPG");
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_3.JPG");
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_4.JPG");
	probability.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\probability_5.JPG");
	ClueInBlueShelfBtm.push_back(probability);
	


	/* type book page */
	coordinate = set_coordinate(0.888888889, 0.701388889, 0.949074074, 0.763888889);
	BlueShelf_back.set_clue(room_name, position_num, "BlueShelf_back", coordinate);
	ClueBookInside.push_back(BlueShelf_back);

	coordinate = set_coordinate(0.702, 0.68, 0.743, 0.757142);
	book_OK.set_clue(room_name, position_num, "OK_book", coordinate);
	ClueBookInside.push_back(book_OK);

	coordinate = set_coordinate(0.702, 0.571428, 0.743, 0.647142);
	book_clear.set_clue(room_name, position_num, "clear_book", coordinate);
	ClueBookInside.push_back(book_clear);

	coordinate = set_coordinate(0.702, 0.46, 0.743, 0.535714);
	book_0.set_clue(room_name, position_num, "0_book", coordinate);
	ClueBookInside.push_back(book_0);

	coordinate = set_coordinate(0.536, 0.46, 0.577, 0.535714);
	book_1.set_clue(room_name, position_num, "1_book", coordinate);
	ClueBookInside.push_back(book_1);

	coordinate = set_coordinate(0.593, 0.46, 0.634, 0.535714);
	book_2.set_clue(room_name, position_num, "2_book", coordinate);
	ClueBookInside.push_back(book_2);

	coordinate = set_coordinate(0.648, 0.46, 0.687, 0.535714);
	book_3.set_clue(room_name, position_num, "3_book", coordinate);
	ClueBookInside.push_back(book_3);

	coordinate = set_coordinate(0.536, 0.571428, 0.577, 0.647142);
	book_4.set_clue(room_name, position_num, "4_book", coordinate);
	ClueBookInside.push_back(book_4);

	coordinate = set_coordinate(0.593, 0.571428, 0.634, 0.647142);
	book_5.set_clue(room_name, position_num, "5_book", coordinate);
	ClueBookInside.push_back(book_5);

	coordinate = set_coordinate(0.648, 0.571428, 0.687, 0.647142);
	book_6.set_clue(room_name, position_num, "6_book", coordinate);
	ClueBookInside.push_back(book_6);

	coordinate = set_coordinate(0.536, 0.68, 0.577, 0.757142);
	book_7.set_clue(room_name, position_num, "7_book", coordinate);
	ClueBookInside.push_back(book_7);

	coordinate = set_coordinate(0.593, 0.68, 0.634, 0.757142);
	book_8.set_clue(room_name, position_num, "8_book", coordinate);
	ClueBookInside.push_back(book_8);

	coordinate = set_coordinate(0.648, 0.68, 0.687, 0.757142);
	book_9.set_clue(room_name, position_num, "9_book", coordinate);
	ClueBookInside.push_back(book_9);

	//************************************************************
	/*Orange*/

	/*OrangeShelfTop		ClueInRoom[11] */
	corner = set_corner(15.3917, -6.5941, 2.2098
		, 15.3917, -6.53189, 6.71852
		, 15.3917, -9.95336, 6.71852
		, 15.3917, -10.3888, 2.28098);
	Orange_shelf_Top.set_clue(room_name, position_num, "Orange_shelf_Top", 27, 81, 27, 81, corner);
	ClueInRoom.push_back(Orange_shelf_Top);
	ClueInOrangeShelfTop.push_back(back);

	//************************************************************
	/*OrangeShelfMid		ClueInRoom[12] */
	corner = set_corner(15.3917, -11.1975, 2.23951
		, 15.3917, -11.0109, 6.67704
		, 15.3917, -15.4277, 6.67704
		, 15.3917, -15.4277, 2.19803);
	Orange_shelf_Mid.set_clue(room_name, position_num, "Orange_shelf_Mid", 33, 75, 33, 75, corner);
	ClueInRoom.push_back(Orange_shelf_Mid);
	ClueInOrangeShelfMid.push_back(back);
	//************************************************************
	/*OrangeShelfBottom		ClueInRoom[13] */
	corner = set_corner(10.3078, -13.419, 1.70037
		, 10.366, -13.309, 5.3914
		, 8.96772, -15.9474, 5.18404
		, 8.88032, -16.1123, 1.78331);
	Orange_shelf_bottom.set_clue(room_name, position_num, "Orange_shelf_bottom", -1, -1, 30, 83, corner);
	ClueInRoom.push_back(Orange_shelf_bottom);

	ClueInOrangeShelfBtm.push_back(back);
	//************************************************************

	/*Green*/
	/*GreenShelfTop		ClueInRoom[14] */
	corner = set_corner(15.3917, -6.22085, 10.2851
		, 15.3917, -6.34526, 14.1835
		, 15.3917, -10.6999, 14.1835
		, 15.3917, -10.8243, 10.2851);
	Green_shelf_Top.set_clue(room_name, position_num, "Green_shelf_Top", 36, 95, 33, 97, corner);
	ClueInRoom.push_back(Green_shelf_Top);
	ClueInGreenShelfTop.push_back(back);
	//************************************************************
	/*GreenShelfMid		ClueInRoom[15] */
	corner = set_corner(15.3917, -11.7574, 10.2022
		, 15.3917, -11.4464, 14.2665
		, 15.3917, -15.4277, 14.1006
		, 15.3917, -15.4277, 10.2022);
	Green_shelf_Mid.set_clue(room_name, position_num, "Green_shelf_Mid", 40, 91, 40, 91, corner);
	ClueInRoom.push_back(Green_shelf_Mid);
	ClueInGreenShelfMid.push_back(back);
	//************************************************************
	/*GreenShelfBottom		ClueInRoom[16] */
	/*corner = set_corner(10.5117, -13.0342, 8.46035
		, 10.5117, -13.0342, 11.7367
		, 9.14251, -15.6176, 11.1561
		, 9.05512, -15.7825, 804563);*/

	corner = set_corner(9.77971, -10.5165, 6.77422
		, 9.06837, -9.51389, 8.44867
		, 9.075, -12.7223, 8.65759
		, 9.07612, -13.5244, 6.60855);
	Green_shelf_bottom.set_clue(room_name, position_num, "Green_shelf_bottom", -1, -1, 35, 98, corner);
	ClueInRoom.push_back(Green_shelf_bottom);
	ClueInGreenShelfBtm.push_back(back);
	//************************************************************

	/*Wood*/
	/*WoodShelf		ClueInRoom[17] */
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


	/*boat		ClueInRoom[18] */
	corner = set_corner(-15.3917, -0.870919, 13.2297
		, -15.3917, -0.684293, 10.8243
		, -15.3917, -4.47901, 10.9487
		, -15.3917, -4.72784, 13.2297);
	boat.set_clue(room_name, position_num, "boat", 87, 145,87 , 145, corner);
	boat.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\boat_3.JPG");
	boat.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\boat.JPG");
	ClueInRoom.push_back(boat);

	ClueInBoat.push_back(back);

	coordinate = set_coordinate(0.348148148, 0.290277778, 0.439814815, 0.473611111);
	card_num3.set_clue(room_name, position_num, "card_num3", coordinate);
	card_num3.set_cluebox_img("D:\\resource\\2D\\3.png");
	ClueInBoat.push_back(card_num3);


	/*paint		ClueInRoom[19] */
	corner = set_corner(-15.3917, 1.11975, -0.331779
		, -15.3917, 1.43079, -2.98601
		, -15.3917, -1.30638, -2.98601
		, -15.3917, -1.43079, -0.497668);
	paint.set_clue(room_name, position_num, "paint", 109, 168, 109, 168, corner);
	paint.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\paint_S.JPG");
	paint.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\paint.JPG");
	ClueInRoom.push_back(paint);

	ClueInPaint.push_back(back);

	coordinate = set_coordinate(0.42129629, 0.18472222, 0.487037037, 0.3513888);
	cardS.set_clue(room_name, position_num, "cardS", coordinate);
	cardS.set_cluebox_img("D:\\resource\\2D\\S_small.png");
	ClueInPaint.push_back(cardS);


	/* curtain2		ClueInRoom[20] */
	corner = set_corner(-2.06429, 15.801, -15.3917
		, 1.06429, 15.801, -15.9317
		, 1.10576, -0.933127, -15.3917
		, -2.10576, -1.11975, -15.3917);
	curtain2.set_clue(room_name, position_num, "curtain2", 149, 29, 153, 24, corner);
	curtain2.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_closed.JPG");
	curtain2.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open_P.JPG");
	curtain2.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open.JPG");
	ClueInRoom.push_back(curtain2);


	/* curtain3		ClueInRoom[20] */
	corner = set_corner(1.06429, 15.801, -15.3917
		, 4.06429, 15.801, -15.9317
		, 4.10576, -0.933127, -15.3917
		, 1.10576, -1.11975, -15.3917);
	curtain3.set_clue(room_name, position_num, "curtain3", 155, 35, 158, 30, corner);
	curtain3.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_closed.JPG");
	curtain3.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open_P.JPG");
	curtain3.add_2Dimg_path("D:\\image\\finalroom\\position1\\near_scene\\Curtain_open.JPG");
	ClueInRoom.push_back(curtain3);

	/*lamp		ClueInRoom[21] */
	corner = set_corner(13.3429, 1.55521, -8.34299
		,14.8181, 1.67963, -4.28999
		,14.8039, -4.29238, -4.32896
		,13.3854, -3.91913, -8.22608);
	lamp.set_clue(room_name, position_num, "lamp", 2, 61, 4, 61, corner);
	ClueInRoom.push_back(lamp);
	
}
