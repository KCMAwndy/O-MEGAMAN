#include<SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include"Animation.h"
#include"Megaman.h"
#include "Collider.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 960.0f;

void ResizeView(const sf::RenderWindow& window){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	//view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
	//screen.setSize(sf::Vector2f(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT));
}

int main() {
	sf::RenderWindow window(sf::VideoMode(720, 960), "O-MEGAMAN GAME", sf::Style::Close | sf::Style::Resize);
//	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture megamanTexture;
	megamanTexture.loadFromFile("Images/Megaman_movement.png");
	Megaman megaman(&megamanTexture, sf::Vector2u(3, 15), 0.8f, 150.0f, 300.0f);
	//std::vector<Platform> platforms;
	sf::RectangleShape ground;
	sf::Texture groundTexture;
	groundTexture.loadFromFile("Images/Layer 9.png");
	ground.setTexture(&groundTexture);
	ground.setPosition(sf::Vector2f(22.0f, 767.0f));
	ground.setSize(sf::Vector2f(674.0f, 20.0f));
	sf::RectangleShape leftWall;
	sf::Texture leftWallTexture;
	leftWallTexture.loadFromFile("Images/Layer 5.png");
	leftWall.setTexture(&leftWallTexture);
	leftWall.setPosition(sf::Vector2f(0.0f, 0.0f));
	leftWall.setSize(sf::Vector2f(20.0f, 790.0f));
	sf::RectangleShape rightWall;
	sf::Texture rightWallTexture;
	rightWallTexture.loadFromFile("Images/Layer 6.png");
	rightWall.setTexture(&rightWallTexture);
	rightWall.setPosition(sf::Vector2f(700.0f, 0.0f));
	rightWall.setSize(sf::Vector2f(20.0f, 790.0f));
	sf::RectangleShape upWall;
	sf::Texture upWallTexture;
	upWallTexture.loadFromFile("Images/Layer 7.png");
	upWall.setTexture(&upWallTexture);
	upWall.setPosition(sf::Vector2f(20.0f, 0.0f));
	upWall.setSize(sf::Vector2f(680.0f, 65.0f));
	sf::Texture screenTexture;
	sf::Sprite screen;
	screenTexture.loadFromFile("Images/Background.png");
	screen.setTexture(screenTexture);
	screen.setPosition(0.0f,0.0f);

	float elapsedTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event evnt;
		elapsedTime = clock.restart().asSeconds();
		if (elapsedTime > 1.0f / 20.0f) {
			elapsedTime = 1.0f / 20.0f;
		}
		while (window.pollEvent(evnt)) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window);
				break;
			case sf::Event::MouseButtonPressed:
				printf("%d,%d\n", x, y);
				break;
			}
		}
		megaman.Update(elapsedTime,window);
		sf::Vector2f direction;
		//Collider megamanCollider = megaman.GetCollider();
		window.clear();
		//window.setView(view);
		window.draw(screen);
		window.draw(ground);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(upWall);
		megaman.Draw(window);
		window.display();
	}
	return 0;
}