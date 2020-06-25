#include "stdafx.h"
#include "Game.hpp"
#include <sstream>

Game::Game(sf::Window &window)
	:
	m_view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize())),
	m_shape(sf::Vector2f(20, 20))
{
	m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	m_shape.setFillColor(sf::Color::Red);
	m_player.setPosition(0, -m_player.getSize().y);
	m_player.setFillColor(sf::Color::Green);

	m_platforms.emplace_back(0, 0, m_platformSize);
	for (unsigned int i = 1; i < 100; i++)
	{
		const sf::Vector2f &prevPos = m_platforms[i - 1].getPosition();
		m_platforms.emplace_back(prevPos.x + m_platformSize.x + 200, prevPos.y, m_platformSize);
	}


	m_font.loadFromFile("data/fonts/Georgia.ttf");

	m_text.setFont(m_font);
	m_text.setPosition(-400, -350);
	m_text.setString("");
}

Game::~Game()
{
}

void Game::updateModel(sf::RenderWindow &window)
{
	m_dt = m_gameClock.restart();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_dir = Dir::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_dir = Dir::Right;
	else
		m_dir = Dir::None;

	//////////////////////////////////////////////////

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_jumpable)
	{
		m_jumpable = false;
		m_jumping = true;
		m_jumpOrigin = m_player.getPosition().y;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_grounded)
		m_jumpable = true;

	//////////////////////////////////////////////////

	if (m_player.insideOffsetYBounds(m_platforms[0], m_gravity) &&
		m_player.insideXBounds(m_platforms[0]))
	{
		m_falling = false;
		m_grounded = true;
	}
	else
	{
		m_falling = true;
		m_grounded = false;
	}

	if (m_jumping)
	{
		if (m_player.getPosition().y > m_jumpOrigin - 100)
			m_player.move(0, -0.5);
		else
		{
			m_jumping = false;
			m_falling = true;
		}
	}
	else if (m_falling)
		m_player.move(0, m_gravity);


	//////////////////////////////////////////////////

	if (m_dir == Dir::Left &&
		m_player.insideOffsetXBounds(m_platforms[0], -m_speed) &&
		m_player.insideYBounds(m_platforms[0]))
	{
		m_dir = Dir::None;
	}
	// Might be of use later
	else
	{
	}

	if (m_dir == Dir::Right &&
		m_player.insideOffsetXBounds(m_platforms[0], m_speed) &&
		m_player.insideYBounds(m_platforms[0]))
	{
		m_dir = Dir::None;
	}
	// Might be of use later
	else
	{
	}

	//////////////////////////////////////////////////

	switch (m_dir)
	{
	case Dir::None:
		break;
	case Dir::Left:
		m_player.move(-m_speed, 0);
		break;
	case Dir::Right:
		m_player.move(m_speed, 0);
		break;
	}

	/*if (m_player.getWindowedPosition(window).x + m_player.getSize().x > window.getSize().x / 2 + m_player.getSize().x + 100 &&
		m_player.getVelocity().x > 0)
	{
		m_view.move(m_player.getVelocity().x, 0);
	}
	if (m_player.getWindowedPosition(window).x < static_cast<signed int>(window.getSize().x) / 2 - 100 &&
		m_player.getVelocity().x < 0)
	{
		m_view.move(m_player.getVelocity().x, 0);
	}

	if (m_player.getWindowedPosition(window).y + m_player.getSize().y > window.getSize().y / 2 + m_player.getSize().y &&
		m_player.getVelocity().y > 0)
	{
		m_view.move(0, m_player.getVelocity().y);
	}
	if (m_player.getWindowedPosition(window).y < static_cast<signed int>(window.getSize().y) / 2 - 100 &&
		m_player.getVelocity().y < 0)
	{
		m_view.move(0, m_player.getVelocity().y);
	}*/
}

void Game::draw(sf::RenderTarget &target)
{
	for (auto &platform : m_platforms)
		platform.draw(target);

	m_player.draw(target);
	target.setView(m_view);
	target.draw(m_shape);

	target.draw(m_text);
}
