#include <string>
using namespace std;

class Player {
public:
	Player();
	Player(int, const char*);
	Player(int, string&);

	int get_player_state();	//查看目前state	
	int get_player_position();	//查看目前在哪一步
	string& get_player_name();	//查看玩家名字
	string& get_player_sex();	//查看玩家性別

	void set_player_name(const char*);		//輸入玩家名字
	void set_player_name(string&);			//輸入玩家名字
	void set_player_sex(string&);	//玩家選 "boy" or "girl"
	void player_position();
	void player_state();

private:
	string _name; // 名字
	int _sex;	//0是男生 1是女生
	int _state;
	int _position;
};