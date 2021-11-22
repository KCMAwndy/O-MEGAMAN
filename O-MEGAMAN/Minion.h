#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Collider.h"

class Minion
{
public:
	Minion(sf::Texture* texture,sf::Vector2f position, sf::Vector2f size,float speed);
	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::Vector2f GetOrigin() {
		return body.getOrigin();
	}
	Collider GetCollider() {
		return Collider(body);
	}
	Collider CheckCollision(Collider& other, sf::Vector2f direction, float push);
public:
	bool faceRight;
private:
	sf::RectangleShape body;
	sf::Texture minionTexture;
	sf::Vector2f velocity;
	float speed;
	float collectPostition;
	float collectTime;
};