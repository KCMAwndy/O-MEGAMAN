#include<SFML\Graphics.hpp>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"Animation.h"
#include"Megaman.h"
#include "Collider.h"
#include "Platform.h"
#include"EnergyBall.h"
#include "Minion.h"
#include "BatBoss.h"

static const float VIEW_HEIGHT = 960.0f;

void ResizeView(const sf::RenderWindow& window){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	//view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
	//screen.setSize(sf::Vector2f(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT));
}

int main() {
	bool spawnMinion[4] = { true,true,true,true };
	//float spawnNum = 0.0f;
	//printf("HELLO ME NA");
	sf::RenderWindow window(sf::VideoMode(720, 960), "O-MEGAMAN GAME", sf::Style::Close | sf::Style::Resize);
	//	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture megamanTexture;
	megamanTexture.loadFromFile("Images/Megaman_movement.png");
	Megaman megaman(&megamanTexture, sf::Vector2u(3, 15), 0.8f, 150.0f, 300.0f);

	sf::Texture batbossTexture;
	batbossTexture.loadFromFile("Images/MegaBoss_Movement.png");
	BatBoss batboss(&batbossTexture, sf::Vector2u(2, 1), 0.9f, 150.0f);

	sf::Texture energyballRightTexture;
	sf::Texture energyballLeftTexture;
	sf::Texture megaBulletTexture;
	energyballRightTexture.loadFromFile("Images/EnergyBallRight.png");
	energyballLeftTexture.loadFromFile("Images/EnergyBallleft.png");
	megaBulletTexture.loadFromFile("Images/MegaBullet.png");

	std::vector<Minion> minionsLeft;
	std::vector<Minion> minionsRight;
	std::vector<Minion> minionsUp1;
	std::vector<Minion> minionsUp2;

	std::vector<class EnergyBall>	energyballs;
	bool checkLR= true;
	bool checkUP = false;
	int checkBott=0;
	int shootTimer = 1;
	sf::Texture groundMinionLeftTexture;
	groundMinionLeftTexture.loadFromFile("Images/groundMinion_Left.png");
	sf::Texture groundMinionRightTexture;
	groundMinionRightTexture.loadFromFile("Images/groundMinion_Right.png");
	sf::Texture AirMinion01Texture;
	AirMinion01Texture.loadFromFile("Images/AirMinion_1.png");
	sf::Texture AirMinion02Texture;
	AirMinion02Texture.loadFromFile("Images/AirMinion_2.png");

	std::srand(time(0));
	//printf("%d\n", std::rand() % 191 + 370);
	//minions.push_back(Minion(&groundMinionRightTexture,sf::Vector2f(25.0f, 680.0f), sf::Vector2f(80.0f, 100.0f), 200.0f));
	//minions.push_back(Minion(&groundMinionLeftTexture,sf::Vector2f(615.0f, 680.0f), sf::Vector2f(80.0f, 100.0f),200.0f));
	//minions.push_back(Minion(&AirMinion01Texture, sf::Vector2f(615.0f,std::rand() % 141 + 490.0f), sf::Vector2f(70.0f, 50.0f), 200.0f));
	//minions.push_back(Minion(&AirMinion02Texture, sf::Vector2f(25.0f, std::rand() % 141 + 360.0f), sf::Vector2f(70.0f, 70.0f), 200.0f));

	//std::vector<Platform> platforms;
	//sf::RectangleShape ground;
	//sf::Texture groundTexture;
	//groundTexture.loadFromFile("Images/Layer 9.png");
	//ground.setTexture(&groundTexture);
	//ground.setPosition(sf::Vector2f(22.0f, 767.0f));
	//ground.setSize(sf::Vector2f(674.0f, 20.0f));
	//sf::RectangleShape leftWall;
	//sf::Texture leftWallTexture;
	//leftWallTexture.loadFromFile("Images/Layer 5.png");
	//leftWall.setTexture(&leftWallTexture);
	//leftWall.setPosition(sf::Vector2f(0.0f, 0.0f));
	//leftWall.setSize(sf::Vector2f(20.0f, 790.0f));
	//sf::RectangleShape rightWall;
	//sf::Texture rightWallTexture;
	//rightWallTexture.loadFromFile("Images/Layer 6.png");
	//rightWall.setTexture(&rightWallTexture);
	//rightWall.setPosition(sf::Vector2f(700.0f, 0.0f));
	//rightWall.setSize(sf::Vector2f(20.0f, 790.0f));
	//sf::RectangleShape upWall;
	//sf::Texture upWallTexture;
	//upWallTexture.loadFromFile("Images/Layer 7.png");
	//upWall.setTexture(&upWallTexture);
	//upWall.setPosition(sf::Vector2f(20.0f, 0.0f));
	//upWall.setSize(sf::Vector2f(680.0f, 65.0f));
	sf::Texture screenTexture;
	sf::Sprite screen;
	screenTexture.loadFromFile("Images/Background.png");
	screen.setTexture(screenTexture);
	screen.setPosition(0.0f, 0.0f);
	//float spawnTime = 0.0f;
	float elapsedTime = 0.0f;
	sf::Clock clock;
	sf::Clock spawnclock;

	while (window.isOpen()) {
		sf::Event evnt;
		elapsedTime = clock.restart().asSeconds();
		//spawnTime	+= spawnclock.restart().asSeconds();
		if (elapsedTime > 1.0f / 20.0f) {
			elapsedTime = 1.0f / 20.0f;
		}
		while (window.pollEvent(evnt)) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window);
				break;
			case sf::Event::MouseButtonPressed:
				printf("%d,%d\n", x, y);
				break;
			}
		}
		//printf("%f", elapsedTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && shootTimer >= 1) {
			checkLR = false;
			checkUP = true;
			checkBott = -1;
			energyballs.push_back(EnergyBall(&megaBulletTexture, sf::Vector2f(megaman.GetPosition().x, megaman.GetPosition().y - megaman.GetOrigin().y), sf::Vector2f(25.0f, 60.0f), 200.0f));
			shootTimer--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shootTimer >= 1) {
			checkLR = true;
			checkUP = false;
			energyballs.push_back(EnergyBall(&energyballRightTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 200.0f));
			shootTimer--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shootTimer >= 1) {
			checkLR = false;
			checkUP = false;
			energyballs.push_back(EnergyBall(&energyballLeftTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 200.0f));
			shootTimer--;

		}
		for (size_t i = 0; i < energyballs.size(); i++) {
			energyballs[i].Update(elapsedTime, window, energyballs, checkUP, checkBott, checkLR); // ขวา , ซ้าย , บน
			if (energyballs[i].GetPosition().x >= window.getSize().x - 40.0f || energyballs[i].GetPosition().x <= 40.0f || energyballs[i].GetPosition().y <= 60.0f + 30.0f) {
				energyballs.erase(energyballs.begin() + i);
				shootTimer++;
			}
		}

		if (spawnMinion[0]) {
			minionsLeft.push_back(Minion(&groundMinionRightTexture, sf::Vector2f(65.0f, 730.0f), sf::Vector2f(80.0f, 100.0f), 80.0f));
			spawnMinion[0] = false;
		}
		if (spawnMinion[1] ) {
			minionsRight.push_back(Minion(&groundMinionLeftTexture, sf::Vector2f(640.0f, 730.0f), sf::Vector2f(80.0f, 100.0f), 80.0f));
			spawnMinion[1] = false;
		}
		if (spawnMinion[2] ) {
			minionsUp1.push_back(Minion(&AirMinion01Texture, sf::Vector2f(655.0f, std::rand() % 141 + 490.0f), sf::Vector2f(70.0f, 50.0f), 80.0f));
			spawnMinion[2] = false;
		}
		if (spawnMinion[3]) {
			minionsUp2.push_back(Minion(&AirMinion02Texture, sf::Vector2f(60.0f, std::rand() % 141 + 360.0f), sf::Vector2f(70.0f, 70.0f), 80.0f));
			spawnMinion[3] = false;
		}
		megaman.Update(elapsedTime, window);
		batboss.Update(elapsedTime, window);
		sf::Vector2f direction;
		Collider megamanCollider = megaman.GetCollider();
		window.clear();
		//window.setView(view);
		window.draw(screen);
		for (size_t i = 0; i < minionsLeft.size(); i++) {
			minionsLeft[i].Draw(window);
		}
		for (size_t i = 0; i < minionsLeft.size(); i++) {
			minionsLeft[i].Update(elapsedTime);
			if (minionsLeft[i].GetPosition().x >= window.getSize().x - 75 || minionsLeft[i].GetCollider().CheckCollision(megamanCollider)) {
				minionsLeft.erase(minionsLeft.begin() + i);
				spawnMinion[0] = true;
				//	spawnNum = (spawnNum + 1) % 4;
				//	printf("%d", spawnNum);
			}
				else {
					for (size_t j = 0; j < energyballs.size(); j++) {
						Collider energyballCollider = energyballs[j].GetCollider();
						if (minionsLeft[i].GetCollider().CheckCollision(energyballCollider)) {
							minionsLeft.erase(minionsLeft.begin() + i);
							energyballs.erase(energyballs.begin() + j);
							spawnMinion[0] = true;
							shootTimer++;
						}
					}
				}
		}
		for (size_t i = 0; i < minionsRight.size(); i++) {
			minionsRight[i].Draw(window);
		}
		for (size_t i = 0; i < minionsRight.size(); i++) {
			minionsRight[i].Update(elapsedTime);
				if (minionsRight[i].GetPosition().x <= 60 || minionsRight[i].GetCollider().CheckCollision(megamanCollider)) {
					minionsRight.erase(minionsRight.begin() + i);
					spawnMinion[1] = true;
					//	printf("%d", spawnNum);
				}
				else {
					for (size_t j = 0; j < energyballs.size(); j++) {
						Collider energyballCollider = energyballs[j].GetCollider();
						if (minionsRight[i].GetCollider().CheckCollision(energyballCollider)) {
							minionsRight.erase(minionsRight.begin() + i);
							energyballs.erase(energyballs.begin() + j);
							spawnMinion[1] = true;
							shootTimer++;
						}
					}
				}
		}
		for (size_t i = 0; i < minionsUp1.size(); i++) {
			 minionsUp1[i].Draw(window);
		}
		for (size_t i = 0; i <  minionsUp1.size(); i++) {
			minionsUp1[i].Update(elapsedTime);
				if (minionsUp1[i].GetPosition().x <= 60 || minionsUp1[i].GetCollider().CheckCollision(megamanCollider)) {
					minionsUp1.erase(minionsUp1.begin() + i);
					spawnMinion[2] = true;
					//	printf("%d", spawnNum);
				}
				else {
					for (size_t j = 0; j < energyballs.size(); j++) {
						Collider energyballCollider = energyballs[j].GetCollider();
						if (minionsUp1[i].GetCollider().CheckCollision(energyballCollider)) {
							minionsUp1.erase(minionsUp1.begin() + i);
							energyballs.erase(energyballs.begin() + j);
							spawnMinion[2] = true;
							shootTimer++;
						}
					}
				}
		}
		for (size_t i = 0; i < minionsUp2.size(); i++) {
			minionsUp2[i].Draw(window);
		}
		for (size_t i = 0; i < minionsUp2.size(); i++) {
			minionsUp2[i].Update(elapsedTime);
				if (minionsUp2[i].GetPosition().x >= window.getSize().x - 70 || minionsUp2[i].GetCollider().CheckCollision(megamanCollider)) {
					minionsUp2.erase(minionsUp2.begin() + i);
					spawnMinion[3] = true;

					//	printf("%d", spawnNum);
				}
				else {
					for (size_t j = 0; j < energyballs.size(); j++) {
						Collider energyballCollider = energyballs[j].GetCollider();
						if (minionsUp2[i].GetCollider().CheckCollision(energyballCollider)) {
							minionsUp2.erase(minionsUp2.begin() + i);
							energyballs.erase(energyballs.begin() + j);
							spawnMinion[3] = true;
							shootTimer++;
						}
					}
				}
		}
			//window.draw(ground);
			//window.draw(leftWall);
			//window.draw(rightWall);
			//window.draw(upWall);
			for (size_t i = 0; i < energyballs.size(); i++) {
					energyballs[i].Draw(window);
				}
			megaman.Draw(window);
			batboss.Draw(window);
			window.display();
		}
		return 0;
}