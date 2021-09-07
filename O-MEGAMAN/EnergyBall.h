#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Megaman.h"

class EnergyBall
{
public:
	EnergyBall(sf::Texture* texture,sf::Vector2f position, sf::Vector2f size, float speed);
	void Update(float elapsedTime, sf::RenderWindow& window,std::vector<class EnergyBall> energyballs,bool checkUP, int checkBott, bool checkLR);
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
	float speed;
	bool faceRight;
	int checkBott;
	sf::Vector2f velocity;
	sf::Texture energyballTexture;
};