#include <iostream>

struct options {
	int	difficulty;
	int map;
};


options menu();

class Game {
	const std::string player =		"[*]";
	const std::string wall =		"XXX";
	const std::string enemy =		"[@]";
	const std::string exit =		"{ }";
	const std::string path =		"[ ]";
	int difficulty=0;
	bool win = 0;
	struct coordinates {
		int player_x;
		int player_y;
		int enemy_x[20];
		int enemy_y[20];
		int exit_x;
		int exit_y;
	};
	coordinates cords{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int health=0;
	int enemy_id=0;
public:
	std::string map_e[20][20];
	std::string map_m[30][30];
	std::string map_h[40][40];
	
	//constructor
	void make_map(int enemy, int difficulty, int map);
	Game(options x);
	void show();
	void make_again();
	void health_check();
	void win_check();
	void player_based_movement();
	void game_based_movement();
};