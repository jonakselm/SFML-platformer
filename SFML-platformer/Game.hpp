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
	// For use in runtime debugging (showing while in debug)
	sf::Text m_rampUpText, m_jumpHeightText, m_rampableText;

	sf::Clock m_gameClock;
	// Dt: Time per frame, JumpTimer: How long space has been held
	sf::Time m_dt;

	sf::View m_view;

	sf::Vector2f m_platformSize = { 200, 500 };
	std::vector<Platform> m_platforms;

	Player m_player;
	Dir m_dir = Dir::None;
	bool m_jumpable = true, m_grounded = true, m_jumping = false, m_falling = false,
		m_rampable = false;

	const float m_moveSpeed = 1, m_jumpSpeed = 0.5f, m_gravity = 0.5f, m_minJumpHeight = 100;

	float m_jumpOrigin = 0, m_rampUp = 0, m_jumpHeight = 0;

	sf::RectangleShape m_shape;
};