#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
private:
	sf::Vector2<float> m_Position;

	// A RectangleShape object
	sf::RectangleShape m_Shape;

	float m_Speed = 1000.0f;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;

public:
	Bat(float startX, float startY);

	sf::Rect<float> getPosition();

	sf::RectangleShape getShape();

	void moveLeft();

	void moveRight();

	void stopLeft();

	void stopRight();

	void update(sf::Time dt);

};