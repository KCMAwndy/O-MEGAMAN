#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Megaman.h"

class EnergyBall
{
public:
	EnergyBall(sf::Texture* texture,sf::Vector2f position, sf::Vector2f size, float speed);
	void Update(float elapsedTime,bool checkUP, int checkBott, bool checkLR);
	void FollowUpdate(float elapsedTime, sf::Vector2f megamanPos);
	void parabolaUpdtae(float elapsedTime, int face);
	void strikeUpdate(float elapsedTime,float x);
	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() {
		return Collider(body);
	}
public:
	bool spawnBall;
private:
	sf::RectangleShape body;
	float speed;
	bool faceRight;
	int checkBott;
	sf::Vector2f velocity;
	sf::Texture energyballTexture;
};