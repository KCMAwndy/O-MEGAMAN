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
	void Update(float elapsedTime, sf::RenderWindow& window,bool iceHit,bool fireHit,bool dead);
	void Draw(sf::RenderWindow& window);
	void Hit(float elapsedTime, float scale);
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
public:
	bool iceHit;
	bool fireHit;
	bool dead;
private:
	sf::RectangleShape body;
	sf::Vector2f velocity;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	bool canjump = false;
	float jumpHeight;
	float height = 0.0;
};