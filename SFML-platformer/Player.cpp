#include "stdafx.h"
#include "Player.hpp"

Player::Player()
	:
	m_shape(sf::Vector2f(30, 30)),
	m_vel(0, 0)
{
}

Player::~Player()
{
}

sf::Vector2f Player::getPosition() const
{
	return m_shape.getPosition();
}

sf::Vector2i Player::getWindowedPosition(sf::RenderTarget &target) const
{
	return target.mapCoordsToPixel(m_shape.getPosition());
}

sf::Vector2f Player::getSize() const
{
	return m_shape.getSize();
}

/*sf::Vector2f Player::getVelocity() const
{
	return m_vel;
}*/

sf::FloatRect Player::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f &pos)
{
	m_shape.setPosition(pos);
}

void Player::setPosition(float x, float y)
{
	setPosition({ x, y });
}

void Player::setFillColor(const sf::Color &color)
{
	m_shape.setFillColor(color);
}

/*bool Player::isJumping() const
{
	return m_jumping;
}

void Player::jump(float height)
{
	m_jumping = true;
	m_jumpHeight = height;
	m_origin = m_shape.getPosition().y;
}

void Player::fall(bool set)
{
	if (set)
		m_falling = true;
	else
		m_falling = false;
}

void Player::update(sf::Time &dt, Dir dir)
{
	if (m_jumping)
		m_vel.y = -0.5;
	else if (m_falling)
		m_vel.y = 0.5;
	else
		m_vel.y = 0;

	switch (dir)
	{
	case Dir::None:
		m_vel.x = 0;
		break;
	case Dir::Left:
		m_vel.x = -1;
		break;
	case Dir::Right:
		m_vel.x = 1;
		break;
	}
	m_shape.move(m_vel* static_cast<float>(dt.asMilliseconds()));

	if (m_shape.getPosition().y <= m_origin - m_jumpHeight)
	{
		m_jumping = false;
		m_falling = true;
	}
}*/

void Player::move(const sf::Vector2f &offset)
{
	m_shape.move(offset);
}

void Player::move(float offsetX, float offsetY)
{
	move({ offsetX, offsetY });
}

void Player::draw(sf::RenderTarget &target)
{
	target.draw(m_shape);
}
