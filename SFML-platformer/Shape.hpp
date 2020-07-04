#pragma once

class Shape
{
public:
	virtual sf::FloatRect getGlobalBounds() const = 0;

	bool intersects(const Shape &other)
	{
		return getGlobalBounds().intersects(other.getGlobalBounds());
	}
	bool insideXBounds(const Shape &other)
	{
		return getGlobalBounds().left + getGlobalBounds().width > other.getGlobalBounds().left &&
			getGlobalBounds().left < other.getGlobalBounds().left + other.getGlobalBounds().width;
	}
	bool insideOffsetXBounds(const Shape &other, float offset)
	{
		return getGlobalBounds().left + getGlobalBounds().width + offset > other.getGlobalBounds().left &&
			getGlobalBounds().left + offset < other.getGlobalBounds().left + other.getGlobalBounds().width;
	}
	bool insideYBounds(const Shape &other)
	{
		return getGlobalBounds().top + getGlobalBounds().height > other.getGlobalBounds().top &&
			getGlobalBounds().top < other.getGlobalBounds().top + other.getGlobalBounds().height;
	}
	bool insideOffsetYBounds(const Shape &other, float offset)
	{
		return getGlobalBounds().top + getGlobalBounds().height + offset > other.getGlobalBounds().top &&
			getGlobalBounds().top + offset < other.getGlobalBounds().top + other.getGlobalBounds().height;
	}
};