#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Megaman.h"

class EnergyBall
{
public:
	EnergyBall(sf::Texture* texture,sf::Vector2f position, float speed);
	void Update(float elapsedTime, sf::RenderWindow& window,std::vector<class EnergyBall> energyballs,bool checkUP, bool checkLR);
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
	sf::Vector2f velocity;
	sf::Texture energyballTexture;
};