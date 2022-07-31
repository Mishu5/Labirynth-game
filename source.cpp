#include "Source.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <windows.h>
#include <time.h>



options menu() {
	char difficulty;
	char choice;
	options give;
	//difficulty layout
	{
		std::cout << "Welcome to the maze\n\n";
		std::cout << "Select your difficulty:\n";
		std::cout << " 1.Easy\n";
		std::cout << " 2.Medium\n";
		std::cout << " 3.Hard\n";
	}
	//choosing the difficulty
	{
		bool ok = 0;
		
		do {
			difficulty = _getche();

			switch (difficulty) {
			case '1': {give.difficulty = 1; ok = 1; }; break;
			case '2': {give.difficulty = 2; ok = 1; }; break;
			case '3': {give.difficulty = 3; ok = 1; }; break;
			default: {std::cout << "Wrong option!\n"; }; break;
			}
		} while (ok == 0);
	}
	std::cout << std::endl;
	//level layout
	{
		std::cout << "Now choose level:\n";
		std::cout << "1. Level 1\n";
		std::cout << "2. Level 2\n";
	}
	//chooging level
	{
		bool ok = 0;

		do {
			choice = _getche();
			switch (choice) {
			case '1': {give.map = 1; ok = 1; }; break;
			case '2': {give.map = 2; ok = 1; }; break;
			default: {std::cout << "Wrong option!\n"; }; break;
			}
		} while (ok == 0);
	}


	return give;
}

Game::Game(options x) {
	switch (x.difficulty) {
	case 1: {
		Game::health = 5;
		Game::difficulty = 1;
		if (x.map == 1)Game::make_map(2, 1, 1); else Game::make_map(2, 1, 2);
	}; break;
	case 2: {
		Game::health = 4;
		Game::difficulty = 2;
		if (x.map == 1)Game::make_map(2, 2, 1); else Game::make_map(2, 2, 2);
	}; break;
	case 3: {
		Game::health = 3;
		Game::difficulty = 3;
		if (x.map == 1)Game::make_map(2, 3, 1); else Game::make_map(2, 3, 2);
	}; break;
	default: {
	
	}; break;
	}

}

void Game::make_map(int enemy, int difficulty, int map)
{
	//making file name
	std::string file;
	file = "maps/map_";
	switch (difficulty) {
		case 1: {file += "e"; }; break;
		case 2: {file += "m"; }; break;
		case 3: {file += "h"; }; break;
		default:; break;
	}
	switch (map) {
		case 1: {file += "_1.txt"; }; break;
		case 2: {file += "_2.txt"; }; break;
		default:; break;
	}
	
	//opening file
	std::fstream level;
	
	level.open(file.c_str(),std::ios::in);
	if (level.good() == false)
	{
		std::cout << "Couldn't access the file";
		getchar();
        Sleep(2000);
		std::exit(0);
	}
	//making map
	
		std::string* line = new std::string[40];
	{
		int line_number = 0;
		int enemy_id = 0;
		//reading whole file
		while (level.good())
		{
			level >> line[line_number];
			line_number++;
		}
		/*std::cout << "\n" << line_number;*/
		//filling map
		--line_number;
		switch (difficulty) {
			case 1: {
				for (int i = line_number; i >= 0; i--) {
					for (int y = 0; y < 20; y++) {

						switch (line[i][y]) {
						case '.': {
							Game::map_e[i][y] = Game::wall;
							//std::cout << ".";
						}break;
						case '@': {
							Game::map_e[i][y] = Game::enemy;
							Game::cords.enemy_x[enemy_id] = i;
							Game::cords.enemy_y[enemy_id] = y;
							++enemy_id;
							//std::cout << "@";
						}break;
						case ',': {
							Game::map_e[i][y] = Game::path;
							//std::cout << ",";
						}break;
						case 'x': {
							Game::map_e[i][y] = Game::exit;
							Game::cords.exit_x = i;
							Game::cords.exit_y = y;
							//std::cout << "x";
						}break;
						case '*': {
							Game::map_e[i][y] = Game::player;
							Game::cords.player_x = i;
							Game::cords.player_y = y;
							//std::cout << "*";
						}break;
						default: std::cout<< "ERROR!!! BAD CHARACTER IN MAP FILE!!!"; break;
						}


					}
					std::cout << "\n";
				}
				
			}; break;
				
			case 2: {
				for (int i = line_number; i >= 0; i--) {
					for (int y = 0; y < 30; y++) {

						switch (line[i][y]) {
						case '.': {
							Game::map_m[i][y] = Game::wall;
							//std::cout << ".";
						}break;
						case '@': {
							Game::map_m[i][y] = Game::enemy;
							Game::cords.enemy_x[enemy_id] = i;
							Game::cords.enemy_y[enemy_id] = y;
							++enemy_id;
							//std::cout << "@";
						}break;
						case ',': {
							Game::map_m[i][y] = Game::path;
							std::cout << ",";
						}break;
						case 'x': {
							Game::map_m[i][y] = Game::exit;
							Game::cords.exit_x = i;
							Game::cords.exit_y = y;
							//std::cout << "x";
						}break;
						case '*': {
							Game::map_m[i][y] = Game::player;
							Game::cords.player_x = i;
							Game::cords.player_y = y;
							//std::cout << "*";
						}break;
						default: std::cout << "ERROR!!! BAD CHARACTER IN MAP FILE!!!"; break;
						}



					}

				}

			}; break;

			case 3: {
				for (int i = line_number; i >= 0; i--) {
					for (int y = 0; y < 40; y++) {

						switch (line[i][y]) {
						case '.': {
							Game::map_h[i][y] = Game::wall;
							//std::cout << ".";
						}break;
						case '@': {
							Game::map_h[i][y] = Game::enemy;
							Game::cords.enemy_x[enemy_id] = i;
							Game::cords.enemy_y[enemy_id] = y;
							++enemy_id;
							//std::cout << "@";
						}break;
						case ',': {
							Game::map_h[i][y] = Game::path;
							//std::cout << ",";
						}break;
						case 'x': {
							Game::map_h[i][y] = Game::exit;
							Game::cords.exit_x = i;
							Game::cords.exit_y = y;
							//std::cout << "x";
						}break;
						case '*': {
							Game::map_h[i][y] = Game::player;
							Game::cords.player_x = i;
							Game::cords.player_y = y;
							//std::cout << "*";
						}break;
						default: std::cout << "ERROR!!! BAD CHARACTER IN MAP FILE!!!"; break;
						}



					}

				}

			}; break;

		}

		
		Game::enemy_id = enemy_id;
	}
	delete[] line;
	level.close();
}

void Game::show() {
	//showing and refreshing map based on difficulty
	system("cls");

	switch (Game::difficulty) {
	case 1: {
		for (int i = 0; i < 20; i++) {
			for (int y = 0; y < 20; y++) {
				std::cout << Game::map_e[i][y];
			}
			std::cout << "\n";
		}
	}break;
	case 2: {
		for (int i = 0; i < 30; i++) {
			for (int y = 0; y < 30; y++) {
				std::cout << Game::map_m[i][y];
			}
			std::cout << "\n";
		}
	}break;
	case 3: {
		for (int i = 0; i < 40; i++) {
			for (int y = 0; y < 40; y++) {
				std::cout << Game::map_h[i][y];
			}
			std::cout << "\n";
		}
	}break;
	default:; break;

	}
	//showing health
	std::cout << "\n" << "Health: ";
	for (int i = 0; i < Game::health; i++)
		std::cout << " @";
	std::cout << "\n";
}

void Game::health_check() {
	//checking player position according to enemy
	for (int i = 0; i < Game::enemy_id; i++) {
		if (Game::cords.player_x == Game::cords.enemy_x[i] && Game::cords.player_y == Game::cords.enemy_y[i]){
			Game::health--;
		}
		if (Game::health <= 0) {
			system("cls");
			std::cout << "You lost :(\n";
			getchar();
			getchar();
			std::exit(0);
		}
	}
}

void Game::win_check() {
	if (Game::cords.player_x == Game::cords.exit_x && Game::cords.player_y == Game::cords.exit_y) {
		Game::win=1;
		system("cls");
		std::cout << "\nYou win!!!\n";
		std::cout << "\nThank you for playing!\n";
		getchar();
		getchar();
		std::exit(0);
	}
}

void Game::make_again() {

	switch (Game::difficulty) {
		case 1: {
			for (int i = 0; i < Game::enemy_id; i++) {
				Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::enemy;
			}
			Game::map_e[Game::cords.player_x][Game::cords.player_y] = Game::player;
		}break;
		case 2: {
			for (int i = 0; i < Game::enemy_id; i++) {
				Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::enemy;
			}
			Game::map_m[Game::cords.player_x][Game::cords.player_y] = Game::player;
		}break;
		case 3: {
			for (int i = 0; i < Game::enemy_id; i++) {
				Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::enemy;
			}
			Game::map_h[Game::cords.player_x][Game::cords.player_y] = Game::player;
		}break;

		default:; break;
	}

}

void Game::player_based_movement() {
	char* move = new char;
	Game::show();
	while (Game::cords.player_x != Game::cords.exit_x || Game::cords.player_y != Game::cords.exit_y) {
	
		*move = _getche();

		switch (Game::difficulty) {
		case 1: {
			switch (*move) {
			case 's': { //down
				if (Game::map_e[Game::cords.player_x + 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_e[Game::cords.player_x + 1][Game::cords.player_y] = Game::player;
					Game::map_e[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x++;
				}
			}break;
			case 'w': { //up
				if (Game::map_e[Game::cords.player_x - 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_e[Game::cords.player_x - 1][Game::cords.player_y] = Game::player;
					Game::map_e[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x--;
				}
			}break;
			case 'a': { //left
				if (Game::map_e[Game::cords.player_x][Game::cords.player_y -1] != Game::wall)
				{
					Game::map_e[Game::cords.player_x][Game::cords.player_y -1] = Game::player;
					Game::map_e[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y--;
				}
			}break;
			case 'd': { //right
				if (Game::map_e[Game::cords.player_x][Game::cords.player_y + 1] != Game::wall)
				{
					Game::map_e[Game::cords.player_x][Game::cords.player_y + 1] = Game::player;
					Game::map_e[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y++;
				}
			}break;
				
			default:; break;
			}
		}break;
		case 2: {
			switch (*move) {
			case 's': { //down
				if (Game::map_m[Game::cords.player_x + 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_m[Game::cords.player_x + 1][Game::cords.player_y] = Game::player;
					Game::map_m[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x++;
				}
			}break;
			case 'w': { //up
				if (Game::map_m[Game::cords.player_x - 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_m[Game::cords.player_x - 1][Game::cords.player_y] = Game::player;
					Game::map_m[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x--;
				}
			}break;
			case 'a': { //left
				if (Game::map_m[Game::cords.player_x][Game::cords.player_y - 1] != Game::wall)
				{
					Game::map_m[Game::cords.player_x][Game::cords.player_y - 1] = Game::player;
					Game::map_m[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y--;
				}
			}break;
			case 'd': { //right
				if (Game::map_m[Game::cords.player_x][Game::cords.player_y + 1] != Game::wall)
				{
					Game::map_m[Game::cords.player_x][Game::cords.player_y + 1] = Game::player;
					Game::map_m[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y++;
				}
			}break;

			default:; break;
			}
		}break;
		case 3: {
			switch (*move) {
			case 's': { //down
				if (Game::map_h[Game::cords.player_x + 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_h[Game::cords.player_x + 1][Game::cords.player_y] = Game::player;
					Game::map_h[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x++;
				}
			}break;
			case 'w': { //up
				if (Game::map_h[Game::cords.player_x - 1][Game::cords.player_y] != Game::wall)
				{
					Game::map_h[Game::cords.player_x - 1][Game::cords.player_y] = Game::player;
					Game::map_h[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_x--;
				}
			}break;
			case 'a': { //left
				if (Game::map_h[Game::cords.player_x][Game::cords.player_y - 1] != Game::wall)
				{
					Game::map_h[Game::cords.player_x][Game::cords.player_y - 1] = Game::player;
					Game::map_h[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y--;
				}
			}break;
			case 'd': { //right
				if (Game::map_h[Game::cords.player_x][Game::cords.player_y + 1] != Game::wall)
				{
					Game::map_h[Game::cords.player_x][Game::cords.player_y + 1] = Game::player;
					Game::map_h[Game::cords.player_x][Game::cords.player_y] = Game::path;
					Game::cords.player_y++;
				}
			}break;

			default:; break;
			}
		}break;
		default:; break;
		}
		Game::health_check();
		Game::win_check();
		Game::make_again();
		Game::show();
		Beep(1567, 200);
}
	
}

void Game::game_based_movement() {

	//Game based turns
	//Only once
	Game::show();
	//loop
	//for(;;){
	while (Game::win != 1) {
		
		Sleep(3500);
		//enemy movement based on difficulty

		srand(time(NULL));
		int side;
		bool moved = 0;

		switch (Game::difficulty) {
			case 1: {
				for (int i = 0; i < Game::enemy_id; i++) {
					while (moved == 0) {
						side = rand() % 5;
						switch (side) {
						case 0: {	/*up*/
							if (Game::map_e[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_e[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]--;
								moved = 1;
							}
						}break;
						case 1: {	/*right*/
							if (Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::player) {
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] = Game::enemy;
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]++;
								moved = 1;
							}
						}break;
						case 2: {	/*down*/
							if (Game::map_e[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_e[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]++;
								moved = 1;
							}
						}break;
						case 3: {	/*left*/
							if (Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::player) {
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] = Game::enemy;
								Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]--;
								moved = 1;
							}
						}break;
						case 4:; break;
						default:; break;
						}
					}
					moved = 0;
				}
			}break;

			case 2: {
				for (int i = 0; i < Game::enemy_id; i++) {
					while (moved == 0) {
						side = rand() % 5;
						switch (side) {
						case 0: {	/*up*/
							if (Game::map_m[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_m[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]--;
								moved = 1;
							}
						}break;
						case 1: {	/*right*/
							if (Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::player) {
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] = Game::enemy;
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]++;
								moved = 1;
							}
						}break;
						case 2: {	/*down*/
							if (Game::map_m[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_m[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]++;
								moved = 1;
							}
						}break;
						case 3: {	/*left*/
							if (Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::player) {
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] = Game::enemy;
								Game::map_m[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]--;
								moved = 1;
							}
						}break;
						case 4:; break;
						default:; break;
						}
					}
					moved = 0;
				}
			}break;

			case 3: {
				for (int i = 0; i < Game::enemy_id; i++) {
					while (moved == 0) {
						side = rand() % 5;
						switch (side) {
						case 0: {	/*up*/
							if (Game::map_h[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_h[Game::cords.enemy_x[i] - 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]--;
								moved = 1;
							}
						}break;
						case 1: {	/*right*/
							if (Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] == Game::player) {
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] + 1] = Game::enemy;
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]++;
								moved = 1;
							}
						}break;
						case 2: {	/*down*/
							if (Game::map_h[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::path || Game::map_e[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] == Game::player) {
								Game::map_h[Game::cords.enemy_x[i] + 1][Game::cords.enemy_y[i]] = Game::enemy;
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_x[i]++;
								moved = 1;
							}
						}break;
						case 3: {	/*left*/
							if (Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::path || Game::map_e[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] == Game::player) {
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i] - 1] = Game::enemy;
								Game::map_h[Game::cords.enemy_x[i]][Game::cords.enemy_y[i]] = Game::path;
								Game::cords.enemy_y[i]--;
								moved = 1;
							}
						}break;
						case 4:; break;
						default:; break;
						}
					}
					moved = 0;
				}
			}break;


		default:; break;
		}
		Game::health_check();
		Game::make_again();
		Game::show();
		Game::win_check();
		Beep(1174, 200);
	} 
}