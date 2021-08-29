#pragma once
#include<SFML\Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Megaman
{
public:
	Megaman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	void Update(float elapsedTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() {
		return Collider(body);
	}
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	sf::Vector2f velocity;
	bool canjump ;
	float jumpHeight;
	float height = 0.0;
};