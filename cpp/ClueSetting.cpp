#include "D:\RoomEscape\h\gameRun.h"


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
	/*3D OBJ*/
	Clue safe1;
	Clue key;
	Clue cardD;
	Clue cardS;
	Clue cardP;
	Clue card_num1;
	Clue card_num2;
	Clue card_num3;
	
	/*safe*/
	safe1.set_clue("room", 0, "safe1", 0, 45, 0, 45, 2 * DIST, 3 * DIST, -3 * DIST, 0, 90, 0, 2.0);
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_closed.obj");
	safe1.add_3Dobj_path("D:\\resource\\3D\\safe_open.obj");
	list_id.push_back(drawObject(glm_model, safe1, 0));
	ClueInRoom.push_back(safe1);

	/*key*/
	key.set_clue("room", 0, "key", 133, 14, 133, 14, -2 * DIST, 3 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	key.add_3Dobj_path("D:\\resource\\3D\\key.obj");
	list_id.push_back(drawObject(glm_model, key, 0));
	ClueInRoom.push_back(key);

	/*card*/
	cardD.set_clue("room", 0, "cardD", 133, 14, 133, 14, -2 * DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	cardD.add_3Dobj_path("D:\\resource\\3D\\cardD.obj");
	cardD.set_cluebox_img("D:\\resource\\2D\\D.png");
	list_id.push_back(drawObject(glm_model, cardD, 0));
	ClueInRoom.push_back(cardD);

	cardS.set_clue("room", 0, "cardS", 139, 21, 139, 21, -1.1*DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	cardS.add_3Dobj_path("D:\\resource\\3D\\cardS.obj");
	cardS.set_cluebox_img("D:\\resource\\2D\\S.png");
	list_id.push_back(drawObject(glm_model, cardS, 0));
	ClueInRoom.push_back(cardS);

	cardP.set_clue("room", 0, "cardP", 147, 29, 147, 29, 15.7672, -0.435, -1.59514, 0, 90, 0, 1.0);
	cardP.add_3Dobj_path("D:\\resource\\3D\\cardP.obj");
	cardP.set_cluebox_img("D:\\resource\\2D\\P.png");
	list_id.push_back(drawObject(glm_model, cardP, 0));
	ClueInRoom.push_back(cardP);

	card_num1.set_clue("room", 0, "card_num1", 156, 37, 156, 37, 0.7*DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	card_num1.add_3Dobj_path("D:\\resource\\3D\\7.obj");
	card_num1.set_cluebox_img("D:\\resource\\2D\\7.png");
	list_id.push_back(drawObject(glm_model, card_num1, 0));
	ClueInRoom.push_back(card_num1);

	card_num2.set_clue("room", 0, "card_num2", 163, 44, 163, 44, 1.6*DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	card_num2.add_3Dobj_path("D:\\resource\\3D\\2.obj");
	card_num2.set_cluebox_img("D:\\resource\\2D\\2.png");
	list_id.push_back(drawObject(glm_model, card_num2, 0));
	ClueInRoom.push_back(card_num2);

	card_num3.set_clue("room", 0, "card_num3", 170, 50, 170, 50, 2.5*DIST, 0 * DIST, -3 * DIST, 0, 0, 0, 2.0);
	card_num3.add_3Dobj_path("D:\\resource\\3D\\0.obj");
	card_num3.set_cluebox_img("D:\\resource\\2D\\0.png");
	list_id.push_back(drawObject(glm_model, card_num3, 0));
	ClueInRoom.push_back(card_num3);


	vector<Point3f> corner;
	vector<Point2i> coordinate; 

	/*near scene*/
	Clue curtain;
	Clue pillow;
	Clue Blue_shelf_Top;
	Clue Blue_shelf_Mid;
	Clue Blue_shelf_bottom;
	Clue textbook;
	Clue Orange_shelf_Top;
	Clue Orange_shelf_Mid;
	Clue Orange_shelf_bottom;
	Clue Green_shelf_Top;
	Clue Green_shelf_Mid;
	Clue Green_shelf_bottom;
	Clue Wood_shelf;
	Clue Wood_shelf_Top;
	Clue Wood_shelf_Mid;
	Clue Wood_shelf_bottom;

	/*curtain*/
	curtain.set_clue("room", 0, "curtain", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(curtain);


	/*pillow*/
	pillow.set_clue("room", 0, "pillow", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(pillow);

	
	/*book shelf*/

	/*Blue*/
	corner = set_corner(14.9873, -3.9595, -11.8497, 15.1778, -3.75, -6.39466, 15.1778, -8.65738, -6.3946, 14.9888, -8.7244, -11.805);
	Blue_shelf_Top.set_clue("room", 0, "Blue_shelf_Top", 179, 62, 179, 62, corner);
	ClueInRoom.push_back(Blue_shelf_Top);

	coordinate = set_coordinate(0, 0, 100, 100);
	textbook.set_clue("room", 0, "textbook", coordinate);
	ClueInBlueShelfTop.push_back(textbook);

	Blue_shelf_Mid.set_clue("room", 0, "Blue_shelf_Mid", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Blue_shelf_Mid);

	Blue_shelf_bottom.set_clue("room", 0, "Blue_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Blue_shelf_bottom);

	/*Orange*/
	Orange_shelf_Top.set_clue("room", 0, "Orange_shelf_Top", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Orange_shelf_Top);

	Orange_shelf_Mid.set_clue("room", 0, "Orange_shelf_Mid", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Orange_shelf_Mid);

	Orange_shelf_bottom.set_clue("room", 0, "Orange_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Orange_shelf_bottom);

	/*Green*/
	Green_shelf_Top.set_clue("room", 0, "Green_shelf_Top", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Green_shelf_Top);

	Green_shelf_Mid.set_clue("room", 0, "Green_shelf_Mid", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Green_shelf_Mid);

	Green_shelf_bottom.set_clue("room", 0, "Green_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Green_shelf_bottom);

	/*Wood*/
	Wood_shelf.set_clue("room", 0, "Wood_shelf_Top", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInRoom.push_back(Wood_shelf);

	Wood_shelf_Top.set_clue("room", 0, "Wood_shelf_Top", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInWoodShelf.push_back(Wood_shelf_Top);

	Wood_shelf_Mid.set_clue("room", 0, "Wood_shelf_Mid", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInWoodShelf.push_back(Wood_shelf_Mid);

	Wood_shelf_bottom.set_clue("room", 0, "Wood_shelf_bottom", 0, 45, 0, 45, -0.5*DIST, 0.5*DIST, -3 * DIST, 0, 0, 0, 2.0);
	ClueInWoodShelf.push_back(Wood_shelf_bottom);

}
