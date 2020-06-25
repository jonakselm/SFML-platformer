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

	m_rampUpText.setFont(m_font);
	m_rampUpText.setPosition(10, 10);
	m_rampUpText.setString("");

	m_jumpHeightText.setFont(m_font);
	m_jumpHeightText.setPosition(10, 60);
	m_jumpHeightText.setString("");

	m_rampableText.setFont(m_font);
	m_rampableText.setPosition(10, 110);
	m_rampableText.setString("Rampable");
}

Game::~Game()
{
}

void Game::updateModel(sf::RenderWindow &window)
{
	//////////////////////////////////////////////////
	// Time (not in use yet)

	m_dt = m_gameClock.restart();

	//////////////////////////////////////////////////
	// Movement controls

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_dir = Dir::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_dir = Dir::Right;
	else
		m_dir = Dir::None;

	//////////////////////////////////////////////////
	// Jumping controls

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_jumpable)
	{
		m_rampable = true;
		m_jumpable = false;
		m_jumping = true;
		m_jumpOrigin = m_player.getPosition().y;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_grounded)
	{
		m_jumpable = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		m_rampable && m_rampUp < 100)
	{
		m_rampUp = std::abs(m_player.getPosition().y - m_jumpOrigin);
	}
	else
		m_jumpable = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_rampable = false;

	//////////////////////////////////////////////////
	// Jumping, falling and grounded logic

	if (m_player.insideOffsetYBounds(m_platforms[0], m_gravity) &&
		m_player.insideXBounds(m_platforms[0]))
	{
		m_grounded = true;
	}
	else
	{
		m_grounded = false;
	}

	if (m_grounded || m_jumping)
		m_falling = false;
	else
		m_falling = true;

	if (m_jumping)
	{
		m_jumpHeight = std::max(100.f, m_rampUp * 2);
		if (m_player.getPosition().y > m_jumpOrigin - m_jumpHeight)
			m_player.move(0, -m_jumpSpeed);
		else
			m_jumping = false;
	}
	else if (m_falling)
	{
		m_player.move(0, m_gravity);
		m_rampUp = 0;
	}

	//////////////////////////////////////////////////
	// Blocking movement through obstacles

	if (m_dir == Dir::Left &&
		m_player.insideOffsetXBounds(m_platforms[0], -m_moveSpeed) &&
		m_player.insideYBounds(m_platforms[0]))
	{
		m_dir = Dir::None;
	}
	// Might be of use later
	else
	{
	}

	if (m_dir == Dir::Right &&
		m_player.insideOffsetXBounds(m_platforms[0], m_moveSpeed) &&
		m_player.insideYBounds(m_platforms[0]))
	{
		m_dir = Dir::None;
	}
	// Might be of use later
	else
	{
	}

	//////////////////////////////////////////////////
	// Movement (left, right)

	switch (m_dir)
	{
	case Dir::None:
		break;
	case Dir::Left:
		m_player.move(-m_moveSpeed, 0);
		break;
	case Dir::Right:
		m_player.move(m_moveSpeed, 0);
		break;
	}

	//////////////////////////////////////////////////
	// Update sf::Text

	std::stringstream ss0, ss1;

	ss0 << "Jump ramp-up: " << std::to_string(m_rampUp);
	m_rampUpText.setString(ss0.str());

	ss1 << "Jump Height: " << std::to_string(m_jumpHeight);
	m_jumpHeightText.setString(ss1.str());

	//////////////////////////////////////////////////
	// Camera movement

	float playerWindowedX = static_cast<float>(m_player.getWindowedPosition(window).x);

	if (playerWindowedX < static_cast<signed int>(window.getSize().x) / 2 - 100 &&
		m_dir == Dir::Left)
	{
		m_view.move(-m_moveSpeed, 0);
	}
	else if (playerWindowedX + m_player.getSize().x > window.getSize().x / 2 + m_player.getSize().x + 100 &&
		m_dir == Dir::Right)
	{
		m_view.move(m_moveSpeed, 0);
	}

	if (m_player.getWindowedPosition(window).y < static_cast<signed int>(window.getSize().y) / 2 - 100)
	{
		m_view.move(0, -m_jumpSpeed);
	}
	else if (m_player.getWindowedPosition(window).y + m_player.getSize().y > window.getSize().y / 2 + m_player.getSize().y)
	{
		m_view.move(0, m_gravity);
	}
}

void Game::draw(sf::RenderTarget &target)
{
	// Draw to the view
	target.setView(m_view);
	for (auto &platform : m_platforms)
		platform.draw(target);

	m_player.draw(target);
	target.draw(m_shape);

	// Draw to the window
	target.setView(target.getDefaultView());

	// Only show variables while in debug
#ifdef DEBUG
	target.draw(m_rampUpText);
	target.draw(m_jumpHeightText);
	if (m_rampable)
		target.draw(m_rampableText);
#endif // DEBUG

	// Set the view back to the custom view to get right pixel
	// coordinates from sf::RenderWindow/RenderTarget::mapCoordsToPixel();
	target.setView(m_view);
}
