#include <iostream>
#include "Source.h"
#include <conio.h>
#include <thread>
#include <Windows.h>

int main()
{
	options make;
	make =menu();
	Sleep(2000);
	Game* game1 = new Game(make);
	
	std::thread first(&Game::game_based_movement,game1);
	std::thread second(&Game::player_based_movement,game1);
	//game1.player_based_movement();
	//game1.game_based_movement();
	//game1.game();
	first.join();
	second.join();
	delete game1;
	return 0;
}