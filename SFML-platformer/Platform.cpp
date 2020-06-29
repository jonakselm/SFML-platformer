#include "stdafx.h"
#include "Platform.hpp"

Platform::Platform(const sf::Vector2f pos, const sf::Vector2f size)
	:
	m_shape(size)
{
	m_shape.setPosition(pos);
}

Platform::Platform(float posX, float posY, float sizeX, float sizeY)
	:
	Platform({ posX, posY }, { sizeX, sizeY })
{
}

Platform::Platform(float posX, float posY, const sf::Vector2f size)
	:
	Platform({ posX, posY }, size)
{
}

Platform::Platform(const sf::Vector2f pos, float sizeX, float sizeY)
	:
	Platform(pos, { sizeX, sizeY })
{
}

Platform::~Platform()
{
}

sf::FloatRect Platform::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const
{
	return m_shape.getPosition();
}

sf::Vector2f Platform::getSize() const
{
	return m_shape.getSize();
}

sf::Vector2i Platform::getWindowedPosition(sf::RenderTarget &target) const
{
	return target.mapCoordsToPixel(m_shape.getPosition());
}

bool Platform::inView() const
{
	return m_inView;
}

void Platform::update(sf::RenderTarget &target)
{
	auto windowedPos = sf::Vector2f(target.mapCoordsToPixel(m_shape.getPosition()));
	if (windowedPos.x + m_shape.getSize().x > 0 && windowedPos.x < target.getSize().x &&
		windowedPos.y + m_shape.getSize().y > 0 && windowedPos.y < target.getSize().y)
		m_inView = true;
	else
		m_inView = false;
}

void Platform::draw(sf::RenderTarget &target)
{
	target.draw(m_shape);
}
