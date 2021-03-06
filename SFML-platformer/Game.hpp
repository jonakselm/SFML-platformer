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
	sf::Text m_platformYPosText, m_jumpHeightText, m_rampableText, m_jumpTimeText;

	sf::Clock m_gameClock;
	// Dt: Time per frame
	sf::Time m_dt;

	sf::View m_view;

	sf::Vector2f m_platformSize = { 200, 500 };
	std::vector<Platform> m_platforms;

	Player m_player;
	float m_velocity = 0.f;
	Dir m_dir = Dir::None;
	bool m_jumpable = true,	m_rampable = false, m_grounded = true, m_queueJump = false,
		m_activatable = true;

	const float m_moveSpeed = 0.00075f, m_minJumpVel = -0.0004f, m_gravity = 0.0000000008f,
		m_terminalVel = 0.0025f;

	float m_jumpOrigin = 0, m_rampUp = 0, m_jumpHeight = 0, m_jumpTime;

	sf::RectangleShape m_shape;
};