#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
#include"Collider.h"

class Minion
{
public:
	Minion(sf::Texture* texture,sf::Vector2f position,float speed);
	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	std::vector<Minion> minions;
	//void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	Collider GetCollider() {
		return Collider(body);
	}
//	bool CheckLR(std::vector<class Minion> minions,int i);
private:
	sf::RectangleShape body;
	sf::Texture minionTexture;
	float speed;
	sf::Vector2f velocity;
	float collectPostition;
};