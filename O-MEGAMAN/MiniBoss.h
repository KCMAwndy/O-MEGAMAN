#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Collider.h"
#include"EnergyBall.h"
#include"Megaman.h"

class MiniBoss
{
public:
	MiniBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, float speed);
	//void Update(float elapsedTime, sf::RenderWindow& window);
	void Update(float elapsedTime, float movement);
	void Hunt(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);
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
	Animation animation;
	unsigned int row;
	float speed;
	sf::Vector2f velocity;
	int randomMove;
};
