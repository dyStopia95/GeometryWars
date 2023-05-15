#include "pch.h"
#include "Game.h"
#include <iostream>

int main()
{
	std::cout << "Haalo SFML!\n";

	GWar::Game game;

	//GameLoop
	while (game.isRunning())
	{
		while(game._playerAlive && game.isRunning())
		{
			//Update
			game.update();

			//Render
			game.render();
		}
		game.endScreen();
		game.pollEvents();
	}

	//End of app
	return 0;
}