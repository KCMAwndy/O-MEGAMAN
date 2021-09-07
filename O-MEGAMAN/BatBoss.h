#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"Collider.h"
#include"EnergyBall.h"
#include"Megaman.h"

class BatBoss
{
public:
	BatBoss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	void Update(float elapsedTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	std::vector<class EnergyBall>	energyballs;
	//void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() {
		return Collider(body);
	}
private:
	sf::RectangleShape body;
	Animation animation;
	//Megaman megaman;
	sf::Texture energyballBossTexture;
	bool checkLR;
	bool checkUP;
	int checkBott;
	unsigned int row;
	float speed;
	sf::Vector2f velocity;
};