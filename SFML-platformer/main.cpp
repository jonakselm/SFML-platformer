#include "stdafx.h"
#include "Game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML-platformer");

	Game game(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
					break;
			}
		}

		game.updateModel(window);
		window.clear();
		game.draw(window);
		window.display();
	}

	return 0;
}