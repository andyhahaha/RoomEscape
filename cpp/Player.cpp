#include <string>
#include "../h/Player.h"
using namespace std;

// 預設建構函式
Player::Player() {
	_name="noname"; // 名字
	_sex=0;
	_state=0;
	_position = 0;
}

Player::Player(int sex, const char* name) {
	_name = name; // 名字
	_sex = sex;
	_state = 0;
	_position = 0;
}

Player::Player(int sex, string& name) {
	_name = name; // 名字
	_sex = sex;
	_state = 0;
	_position = 0;
}

int Player::get_player_state() {
	return _state;
}

int Player::get_player_position() {
	return _position;
}

string& Player::get_player_name() {
	return _name;
}

string& Player::get_player_sex() {
	string boy("boy"), girl("girl");

	if (_sex == 0)
		return boy;
	else
		return girl;

}


void Player::set_player_name(string &name) {
	_name = name;
}

void Player::set_player_name(const char *name) {
	_name = name;
}

void Player::set_player_sex(string &sex) {
	if (sex == "boy")
		_sex = 0;
	else
		_sex = 1;
}

void Player::player_position() {
	
}

void Player::player_state() {
	
}