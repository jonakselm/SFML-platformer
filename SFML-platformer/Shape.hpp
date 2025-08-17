#pragma once

#include <SFML/Graphics/Rect.hpp>

class Shape
{
public:
	virtual sf::FloatRect getGlobalBounds() const = 0;

	bool intersects(const Shape &other)
	{
		return getGlobalBounds().findIntersection(other.getGlobalBounds()).has_value();
	}
	bool insideXBounds(const Shape &other)
	{
		return getGlobalBounds().position.x + getGlobalBounds().size.x > other.getGlobalBounds().position.x &&
			getGlobalBounds().position.x < other.getGlobalBounds().position.x + other.getGlobalBounds().size.x;
	}
	bool insideOffsetXBounds(const Shape &other, float offset)
	{
		return getGlobalBounds().position.x + getGlobalBounds().size.x + offset > other.getGlobalBounds().position.x &&
			getGlobalBounds().position.x + offset < other.getGlobalBounds().position.x + other.getGlobalBounds().size.x;
	}
	bool insideYBounds(const Shape &other)
	{
		return getGlobalBounds().position.y + getGlobalBounds().size.y > other.getGlobalBounds().position.y &&
			getGlobalBounds().position.y < other.getGlobalBounds().position.y + other.getGlobalBounds().size.y;
	}
	bool insideOffsetYBounds(const Shape &other, float offset)
	{
		return getGlobalBounds().position.y + getGlobalBounds().size.y + offset > other.getGlobalBounds().position.y &&
			getGlobalBounds().position.y + offset < other.getGlobalBounds().position.y + other.getGlobalBounds().size.y;
	}
};
