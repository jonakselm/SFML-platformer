#include "stdafx.h"
#include "Game.hpp"
#include <sstream>
#include <cmath>

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

	m_platformYPosText.setFont(m_font);
	m_platformYPosText.setPosition(10, 10);
	m_platformYPosText.setString("");

	m_jumpHeightText.setFont(m_font);
	m_jumpHeightText.setPosition(10, 60);
	m_jumpHeightText.setString("");

	m_rampableText.setFont(m_font);
	m_rampableText.setPosition(10, 110);
	m_rampableText.setString("Rampable");

	m_jumpTimeText.setFont(m_font);
	m_jumpTimeText.setPosition(10, 160);
	m_jumpTimeText.setString("");
}

Game::~Game()
{
}

void Game::updateModel(sf::RenderWindow &window)
{
	//////////////////////////////////////////////////
	// Time

	m_dt = m_gameClock.restart();

	for (auto &platform : m_platforms)
	{
		platform.update(window);
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_rampable = true;
		m_jumpable = false;
		m_jump = true;
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

	if (m_jump)
	{
		m_velocity = m_minJumpVel;
		m_jump = false;
		m_grounded = false;
	}

	m_player.move(0, m_velocity * m_dt.asMilliseconds());
	m_velocity += m_gravity * m_dt.asMilliseconds();

	m_jumpHeight = m_minJumpVel * 2000.f + 0.5f * m_gravity * std::pow(2000.f, 2);

	m_jumpTime = 0 - m_minJumpVel / m_gravity;

	//////////////////////////////////////////////////
	// Blocking movement through obstacles

	for (const auto &platform : m_platforms)
	{
		if (platform.inView())
		{
			if (m_dir == Dir::Left &&
				m_player.insideOffsetXBounds(platform, -m_moveSpeed * m_dt.asMilliseconds()) &&
				m_player.insideYBounds(platform))
			{
				m_dir = Dir::None;
			}
			// Might be of use later
			else
			{
			}
		}
	}

	for (const auto &platform : m_platforms)
	{
		if (platform.inView())
		{
			if (m_dir == Dir::Right &&
				m_player.insideOffsetXBounds(platform, m_moveSpeed * m_dt.asMilliseconds()) &&
				m_player.insideYBounds(platform))
			{
				m_dir = Dir::None;
			}
			// Might be of use later
			else
			{
			}
		}
	}

	//////////////////////////////////////////////////
	// Movement (left, right)

	switch (m_dir)
	{
	case Dir::None:
		break;
	case Dir::Left:
		m_player.move(-m_moveSpeed * m_dt.asMilliseconds(), 0);
		break;
	case Dir::Right:
		m_player.move(m_moveSpeed * m_dt.asMilliseconds(), 0);
		break;
	}

	//////////////////////////////////////////////////
	// Update sf::Text

	std::stringstream ss0, ss1, ss2;

	ss0 << "Platform[0] Y Position: " << std::to_string(m_platforms[0].getWindowedPosition(window).y);
	m_platformYPosText.setString(ss0.str());

	ss1 << "Jump Height: " << std::to_string(m_jumpHeight);
	m_jumpHeightText.setString(ss1.str());

	ss2 << "Estimated Jump Time: " << std::to_string(m_jumpTime);
	m_jumpTimeText.setString(ss2.str());

	//////////////////////////////////////////////////
	// Camera movement

	float windowedPlayerX = static_cast<float>(m_player.getWindowedPosition(window).x);

	if (windowedPlayerX < static_cast<signed int>(window.getSize().x) / 2 - m_player.getSize().x / 2 &&
		m_dir == Dir::Left)
	{
		m_view.move(-m_moveSpeed * m_dt.asMilliseconds(), 0);
	}
	else if (windowedPlayerX + m_player.getSize().x > window.getSize().x / 2 - m_player.getSize().x / 2 &&
		m_dir == Dir::Right)
	{
		m_view.move(m_moveSpeed * m_dt.asMilliseconds(), 0);
	}

	if (m_player.getWindowedPosition(window).y < static_cast<signed int>(window.getSize().y) / 2)
	{
		m_view.move(0, m_minJumpVel * m_dt.asMilliseconds());
	}
	else if (m_player.getWindowedPosition(window).y + m_player.getSize().y > window.getSize().y / 2)
	{
		m_view.move(0, m_velocity * m_dt.asMilliseconds());
	}
}

void Game::draw(sf::RenderTarget &target)
{
	// Draw to the view
	target.setView(m_view);
	for (auto &platform : m_platforms)
	{
		if (platform.inView())
			platform.draw(target);
	}

	m_player.draw(target);
	target.draw(m_shape);

	// Draw to the window
	target.setView(target.getDefaultView());

	// Only show variables while in debug
#ifdef DEBUG
	target.draw(m_platformYPosText);
	target.draw(m_jumpHeightText);
	target.draw(m_jumpTimeText);
	if (m_rampable)
		target.draw(m_rampableText);
#endif // DEBUG

	// Set the view back to the custom view to get right pixel
	// coordinates from sf::RenderWindow/RenderTarget::mapCoordsToPixel();
	target.setView(m_view);
}
