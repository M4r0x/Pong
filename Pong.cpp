// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Ball.h"
#include "Definitions.h"
#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	// Create a video mode object
	sf::VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Create and open a window for the game

	sf::RenderWindow window(vm, "Pong", sf::Style::Fullscreen);

	int score = 0;
	int lives = 3;

	// Create a bat at the bottom center of the screen
	Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);

	// Create a ball
	Ball ball(SCREEN_WIDTH / 2, 0);

	// Create a Text object called HUD
	sf::Text hud;

	// A cool retro-style font
	sf::Font font;
	font.loadFromFile("Fonts/DS-DIGI.TTF");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(sf::Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything

	sf::Clock clock;

	// Here is our event object for checking for event

	sf::Event event;

	while (window.isOpen()) {
		/*
		Handle the player input
		*/
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bat.getPosition().left > 0)
		{
			bat.moveLeft();
		}
		else 
		{
			bat.stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bat.getPosition().left+bat.getPosition().width<window.getSize().x)
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}


		/*
		Update the bat, the ball and the HUD
		*/

		// Update the delta time
		sf::Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		//Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			//reverse the ball direction
			ball.reboundBottom();

			// Remove a life
			lives--;

			//Check for zero lives
			if (lives < 1) {
				//reset the score
				score = 0;
				//reset the lives
				ball.setSpeed();
				lives = 3;
			}
		}
		// Handle ball hitting the top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			
			// Add a point to the players score
			score++;
		}
		// Handle ball hitting the sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width> window.getSize().x)
		{
			ball.reboundSides();
		}
		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			//Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
		}

		/*
		Draw the bat, the ball and the HUD
		*/

		window.clear(); // Clear previous frame
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display(); // display new frame


	}
	return EXIT_SUCCESS;
}

