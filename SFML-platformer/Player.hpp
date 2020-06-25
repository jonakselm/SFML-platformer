#pragma once
#include "Shape.hpp"

class Player : public Shape
{
public:
	Player();
	~Player();

	sf::Vector2f getPosition() const;
	sf::Vector2i getWindowedPosition(sf::RenderWindow &window) const;
	sf::Vector2f getSize() const;
	//sf::Vector2f getVelocity() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(const sf::Vector2f &pos);
	void setPosition(float x, float y);
	void setFillColor(const sf::Color &color);

	/*bool isJumping() const;

	void jump(float height);
	void fall(bool set);
	void update(sf::Time &dt, Dir dir);*/
	void move(const sf::Vector2f &offset);
	void move(float offsetX, float offsetY);

	void draw(sf::RenderTarget &target);

private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_vel;
	bool m_jumping = false, m_falling = false;
	float m_jumpHeight = 0, m_origin = 0;
};