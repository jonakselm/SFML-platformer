#pragma once
#include "Shape.hpp"

class Platform : public Shape
{
public:
	Platform(const sf::Vector2f pos, const sf::Vector2f size);
	Platform(float posX, float posY, float sizeX, float sizeY);
	Platform(float posX, float posY, const sf::Vector2f size);
	Platform(const sf::Vector2f pos, float sizeX, float sizeY);
	~Platform();

	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2i getWindowedPosition(sf::RenderTarget &target) const;

	bool inView() const;

	void update(sf::RenderTarget &target);

	void draw(sf::RenderTarget &target);

private:
	sf::RectangleShape m_shape;
	bool m_inView = false;
};