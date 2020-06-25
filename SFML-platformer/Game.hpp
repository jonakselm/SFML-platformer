#pragma once
#include "Player.hpp"
#include "Platform.hpp"

class Game
{
public:
	enum class Dir { None, Left, Right };
public:
	Game(sf::Window &window);
	~Game();

	void updateModel(sf::RenderWindow &window);
	void draw(sf::RenderTarget &target);

private:
	sf::Font m_font;
	// For use in runtime debugging
	sf::Text m_text;

	sf::Clock m_gameClock, m_jumpClock;
	// Dt: Time per frame, JumpTimer: How long space has been held
	sf::Time m_dt, m_jumpTimer;

	sf::View m_view;

	sf::Vector2f m_platformSize = { 200, 500 };
	std::vector<Platform> m_platforms;

	Player m_player;
	Dir m_dir = Dir::None;
	bool m_jumpable = true, m_grounded = true, m_jumping = false, m_falling = false,
		m_rampable = false;

	const float m_speed = 1, m_gravity = 0.5f, m_minJumpHeight = 100,
		m_maxJumpHeight = m_minJumpHeight * 2;

	float m_jumpOrigin;

	sf::RectangleShape m_shape;
};