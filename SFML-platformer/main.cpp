#include "stdafx.h"
#include "Game.hpp"
//#include <Windows.h>

int main()
{
#ifdef DEBUG
	//ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif // DEBUG

	sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "SFML-platformer");

	Game game(window);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		game.updateModel(window);
		window.clear();
		game.draw(window);
		window.display();
	}

	return 0;
}
