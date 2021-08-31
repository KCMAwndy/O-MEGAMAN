#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Collider.h"
#include"EnergyBall.h"

class Megaman
{
public:
	Megaman(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	void Update(float elapsedTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	//void OnCollision(sf::Vector2f direction);
	std::vector<class EnergyBall>	energyballs;
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() {
		return Collider(body);
	}
private:
	int shootTimer=3;
	bool checkLR ;
	bool checkUP;
	sf::RectangleShape body;
	sf::Texture energyBallTexture;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	sf::Vector2f velocity;
	bool canjump = false;
	float jumpHeight;
	float height = 0.0;
};