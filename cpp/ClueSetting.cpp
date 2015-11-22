#include "D:\RoomEscape\h\gameRun.h"


vector<Point3f> set_corner(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){


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

vector<Point2i> set_coordinate(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	vector<Point2i> coordinate;
	Point2d point;
	point.x = x1;
	point.y = y1;
	coordinate.push_back(point);
	point.x = x2;
	point.y = y2;
	coordinate.push_back(point);
	point.x = x3;
	point.y = y3;
	coordinate.push_back(point);
	point.x = x4;
	point.y = y4;
	coordinate.push_back(point);

	return coordinate;

}




/*set clue */
void clueSetting(){
	
	/*3D OBJ*/

	/*safe*/
	Clue safe("room", 0, "safe", 0, 45, 0, 45, 2*dist, 3*dist, -3 * dist, 0, 90, 0, 2.0);
	safe.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\safe_closed.obj");
	safe.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\safe_open.obj");
	list_id.push_back(drawObject(glm_model, safe, 0));
	AllClue.push_back(safe);

	/*key*/
	Clue key("room", 0, "key", 133, 14, 133, 14, -2*dist, 3*dist, -3 * dist, 0, 0, 0, 2.0);
	key.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\key.obj");
	list_id.push_back(drawObject(glm_model, key, 0));
	AllClue.push_back(key);

	/*card*/
	Clue cardD("room", 0, "cardD", 133, 14, 133, 14, -2 * dist, 0 * dist, -3 * dist, 0, 0, 0, 2.0);
	cardD.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\cardD.obj");
	cardD.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\D.png");
	list_id.push_back(drawObject(glm_model, cardD, 0));
	AllClue.push_back(cardD);

	Clue cardS("room", 0, "cardS", 139, 21, 139, 21, -1.1*dist, 0*dist, -3 * dist, 0, 0, 0, 2.0);
	cardS.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\cardS.obj");
	cardS.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\S.png");
	list_id.push_back(drawObject(glm_model, cardS, 0));
	AllClue.push_back(cardS);

	Clue cardP("room", 0, "cardP", 147, 29, 147, 29, -0.2*dist, 0*dist, -3 * dist, 0, 0, 0, 2.0);
	cardP.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\cardP.obj");
	cardP.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\P.png");
	list_id.push_back(drawObject(glm_model, cardP, 0));
	AllClue.push_back(cardP);

	Clue card_num1("room", 0, "card_num1", 156, 37, 156, 37, 0.7*dist, 0*dist, -3 * dist, 0, 0, 0, 2.0);
	card_num1.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\7.obj");
	card_num1.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\7.png");
	list_id.push_back(drawObject(glm_model, card_num1, 0));
	AllClue.push_back(card_num1);

	Clue card_num2("room", 0, "card_num2", 163, 44, 163, 44, 1.6*dist, 0*dist, -3 * dist, 0, 0, 0, 2.0);
	card_num2.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\2.obj");
	card_num2.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\2.png");
	list_id.push_back(drawObject(glm_model, card_num2, 0));
	AllClue.push_back(card_num2);

	Clue card_num3("room", 0, "card_num3", 170, 50, 170, 50, 2.5*dist, 0*dist, -3 * dist, 0, 0, 0, 2.0);
	card_num3.add_3Dobj_path("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\3D\\0.obj");
	card_num3.set_cluebox_img("D:\\大學\\專題\\RoomEscape\\RoomEscape\\resource\\2D\\0.png");
	list_id.push_back(drawObject(glm_model, card_num3, 0));
	AllClue.push_back(card_num3);


	vector<Point3f> corner;
	vector<Point2i> coordinate; 
	/*near scence*/

	/*curtain*/
	Clue curtain("room", 0, "curtain", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(curtain);



	/*pillow*/
	Clue pillow("room", 0, "pillow", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(pillow);

	
	/*book shelf*/

	/*Blue*/
	corner = set_corner(14.9873, -3.9595, -11.8497, 15.1778, -3.75, -6.39466, 15.1778, -8.65738, -6.3946, 14.9888, -8.7244, -11.805);
	Clue Blue_shelf_Top("room", 0, "Blue_shelf_Top", 179, 62, 179, 62, corner);
	AllClue.push_back(Blue_shelf_Top);

	coordinate = set_coordinate(0, 0, 100, 0, 0, 100, 100, 100);
	Clue textbook("room", 0, "textbook", coordinate);
	ClueInBlueShelfTop.push_back(textbook);

	Clue Blue_shelf_Mid("room", 0, "Blue_shelf_Mid", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Blue_shelf_Mid);

	Clue Blue_shelf_button("room", 0, "Blue_shelf_button", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Blue_shelf_button);

	/*Orange*/
	Clue Orange_shelf_Top("room", 0, "Orange_shelf_Top", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Orange_shelf_Top);

	Clue Orange_shelf_Mid("room", 0, "Orange_shelf_Mid", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Orange_shelf_Mid);

	Clue Orange_shelf_button("room", 0, "Orange_shelf_button", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Orange_shelf_button);

	/*Green*/
	Clue Green_shelf_Top("room", 0, "Green_shelf_Top", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Green_shelf_Top);

	Clue Green_shelf_Mid("room", 0, "Green_shelf_Mid", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Green_shelf_Mid);

	Clue Green_shelf_button("room", 0, "Green_shelf_button", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Green_shelf_button);

	/*Wood*/
	Clue Wood_shelf_Top("room", 0, "Wood_shelf_Top", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Wood_shelf_Top);

	Clue Wood_shelf_Mid("room", 0, "Wood_shelf_Mid", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Wood_shelf_Mid);

	Clue Wood_shelf_button("room", 0, "Wood_shelf_button", 0, 45, 0, 45, -0.5*dist, 0.5*dist, -3 * dist, 0, 0, 0, 2.0);
	AllClue.push_back(Wood_shelf_button);





	








}
