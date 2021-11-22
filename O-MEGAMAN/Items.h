#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"EnergyBall.h"

class Items
{
public:
	Items(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size);
	void Move(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::Vector2f GetOrigin() {
		return body.getOrigin();
	}
	Collider GetCollider() {
		return Collider(body);
	}
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
};