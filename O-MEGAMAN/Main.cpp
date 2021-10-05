#include<SFML\Graphics.hpp>
#include<iostream>
#include<sstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"Animation.h"
#include"Megaman.h"
#include"Collider.h"
#include"Platform.h"
#include"EnergyBall.h"
#include"Minion.h"
#include"BatBoss.h"
#include"Items.h"

static const float VIEW_HEIGHT = 960.0f;

void ResizeView(const sf::RenderWindow& window){
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	//view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
	//screen.setSize(sf::Vector2f(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT));
}

void UpdateScore(std::ostringstream *pscore,int *score) {
	pscore->str(" ");
	*pscore << *score;
}


int main() {
	bool Screen[5] = { true,false,false,false,false };
	int enCount=0,score=0,megaHP=100,bossHp=500,minionSpeed=80,enballSpeed=250;
	int spawncount = 5;
	int *ptrenCount,*ptrScore,*ptrMegaHP,*ptrBossHP,*ptrminionSpeed, *ptrEnballSpeed,*ptrdeCount;
	ptrenCount = &enCount;
	ptrScore = &score;
	ptrMegaHP = &megaHP;
	ptrBossHP = &bossHp;
	ptrminionSpeed = &minionSpeed;
	ptrEnballSpeed = &enballSpeed;
	int colldataitem = 0;
	bool spawnMinion[4] = { false,false,true,true };
	bool boolenball = true;
	bool spawnbossBall = false;
	bool despawnMinionUp1 = false;
	//float spawnNum = 0.0f;
	//printf("HELLO ME NA");
	sf::RenderWindow window(sf::VideoMode(720, 960), "O-MEGAMAN GAME", sf::Style::Close | sf::Style::Resize);
	//	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture megamanTexture;
	megamanTexture.loadFromFile("Images/Megaman_movement.png");
	Megaman megaman(&megamanTexture, sf::Vector2u(3, 15), 0.8f, 150.0f, 300.0f);

	sf::Texture batbossTexture;
	batbossTexture.loadFromFile("Images/MegaBoss_Movement.png");
	BatBoss batboss(&batbossTexture, sf::Vector2u(2, 1), 0.9f, sf::Vector2f(360.0f, 140.0f), 150.0f);

	sf::Texture energyballRightTexture;
	sf::Texture energyballLeftTexture;
	sf::Texture megaBulletTexture;
	energyballRightTexture.loadFromFile("Images/EnergyBallRight.png");
	energyballLeftTexture.loadFromFile("Images/EnergyBallleft.png");
	megaBulletTexture.loadFromFile("Images/MegaBullet.png");

	sf::Texture bossBulletTexture;
	bossBulletTexture.loadFromFile("Images/MegaBossEnergyBall.png");

	std::vector<Minion> minionsLeft;
	std::vector<Minion> minionsRight;
	std::vector<Minion> minionsUp1;
	std::vector<Minion> minionsUp2;

	std::vector<class EnergyBall>	energyballs;
	std::vector<class EnergyBall>	bossballs;

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

	std::vector<Items> HPItem;
	std::vector<Items> coinItem;
	std::vector<Items> trapItem;
	sf::Texture HPTexture;
	HPTexture.loadFromFile("Images/Heart.png");
	sf::Texture coinTexture;
	coinTexture.loadFromFile("Images/Coin.png");
	sf::Texture TrapTexture;
	TrapTexture.loadFromFile("Images/Trap2.png");

	sf::Font scoreFont;
	scoreFont.loadFromFile("Fonts/TIme TRap.ttf");
	std::ostringstream ssScore;
	ssScore << *ptrScore;
	std::ostringstream ssMegaHP;
	ssMegaHP << *ptrMegaHP;
	std::ostringstream ssBossHP;
	ssBossHP << *ptrBossHP;
	
	std::srand(time(NULL));
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

	sf::Texture menuTexture;
	sf::Sprite menu;
	menuTexture.loadFromFile("Images/Menu.png");
	menu.setTexture(menuTexture);
	menu.setPosition(0.0f, 0.0f);

	sf::Font menuFont;
	menuFont.loadFromFile("Fonts/TIme TRap.ttf");
	sf::Text menuText[3];

	sf::Texture HTPTexture;
	sf::Sprite HTP;
	HTPTexture.loadFromFile("Images/Howtoplay.png");
	HTP.setTexture(HTPTexture);
	HTP.setPosition(0.0f, 0.0f);

	sf::Texture SBTexture;
	sf::Sprite SB;
	SBTexture.loadFromFile("Images/scoreboard.png");
	SB.setTexture(SBTexture);
	SB.setPosition(0.0f, 0.0f);

	sf::Text Back;
	sf::Text Next;

	//float spawnTime = 0.0f;
	float elapsedTime = 0.0f;
	double bossEnBallTime = 0.0f;
	double despawnTime = 0.0f;
	//if (Screen[3]) 
	//}

	sf::Clock clock;
	sf::Clock spawnClock;

	printf("%f", elapsedTime);
		while (window.isOpen()) {
			sf::Event evnt;
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
			if (Screen[0]) {
				clock.restart();
				spawnClock.restart();
				menuText[0].setFont(menuFont);
				menuText[0].setString("Start");
				//menuText[0].setFillColor(sf::Color::White);
				menuText[0].setCharacterSize(50);
				menuText[0].setPosition(285.0f,400.0f);

				menuText[1].setFont(menuFont);
				menuText[1].setString("Score Board");
				//menuText[1].setFillColor(sf::Color::White);
				menuText[1].setCharacterSize(50);
				menuText[1].setPosition(212.0f, 460.0f);

				menuText[2].setFont(menuFont);
				menuText[2].setString("Exit");
				//menuText[3].setFillColor(sf::Color::White);
				menuText[2].setCharacterSize(50);
				menuText[2].setPosition(315.0f, 520.0f);

				for (int i = 0; i < 3; i++) {
					if (menuText[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						menuText[i].setFillColor(sf::Color::Cyan);
						menuText[i].setStyle(sf::Text::Italic);
					}
					else {
						menuText[i].setFillColor(sf::Color::White);
						menuText[i].setStyle(0);
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (menuText[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							Screen[0] = false;
							Screen[2] = true;
						}
					}
					if (menuText[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							Screen[0] = false;
							Screen[1] = true;

					}
					if (menuText[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						break;
					}
				}

				window.clear();
				window.draw(menu);
				for (int i = 0; i < 3; i++) {
					window.draw(menuText[i]);
				}
				window.display();
			}

			if (Screen[1]) {
				clock.restart();
				spawnClock.restart();

				Back.setFont(menuFont);
				Back.setString("BACK");
				//menuText[0].setFillColor(sf::Color::White);
				Back.setCharacterSize(50);
				Back.setPosition(252.0f, 785.0f);

				if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					Back.setFillColor(sf::Color::Cyan);
					Back.setStyle(sf::Text::Italic);
				}
				else {
					Back.setFillColor(sf::Color::White);
					Back.setStyle(0);
				}
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							Screen[1] = false;
							Screen[0] = true;
						}
					}
				}
				window.clear();
				window.draw(SB);
				window.draw(Back);
				window.display();
			}

			if (Screen[2]) {
				clock.restart();
				spawnClock.restart();

				Back.setFont(menuFont);
				Back.setString("BACK");
				//menuText[0].setFillColor(sf::Color::White);
				Back.setCharacterSize(50);
				Back.setPosition(50.0f, 885.0f);

				Next.setFont(menuFont);
				Next.setString("NEXT");
				//menuText[1].setFillColor(sf::Color::White);
				Next.setCharacterSize(50);
				Next.setPosition(565.0f, 885.0f);

				if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					Back.setFillColor(sf::Color::Cyan);
					Back.setStyle(sf::Text::Italic);
				}
				else {
					Back.setFillColor(sf::Color::White);
					Back.setStyle(0);
				}
				if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					Next.setFillColor(sf::Color::Cyan);
					Next.setStyle(sf::Text::Italic);
				}
				else {
					Next.setFillColor(sf::Color::White);
					Next.setStyle(0);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							Screen[2] = false;
							Screen[0] = true;
						}
					}
					if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						Screen[2] = false;
						Screen[3] = true;
					}
				}
				window.clear();
				window.draw(HTP);
				window.draw(Back);
				window.draw(Next);
				window.display();
			}



			if (Screen[3]) {
				printf("\n%f", elapsedTime);
				elapsedTime = clock.restart().asSeconds();
				bossEnBallTime = spawnClock.getElapsedTime().asSeconds();
				if (elapsedTime > 1.0f / 20.0f) {
					elapsedTime = 1.0f / 20.0f;
				}
				sf::Text TextScore;
				TextScore.setCharacterSize(30);
				TextScore.setPosition(340.0f, 865.0f);
				TextScore.setFont(scoreFont);
				TextScore.setString(ssScore.str());
				sf::Text MegaHP;
				MegaHP.setCharacterSize(30);
				MegaHP.setPosition(125.0f, 865.0f);
				MegaHP.setFont(scoreFont);
				MegaHP.setString(ssMegaHP.str());
				sf::Text BossHP;
				BossHP.setCharacterSize(30);
				BossHP.setPosition(555.0f, 865.0f);
				BossHP.setFont(scoreFont);
				BossHP.setString(ssBossHP.str());

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && shootTimer >= 1) {
					checkLR = false;
					checkUP = true;
					checkBott = -1;
					energyballs.push_back(EnergyBall(&megaBulletTexture, sf::Vector2f(megaman.GetPosition().x, megaman.GetPosition().y - megaman.GetOrigin().y), sf::Vector2f(25.0f, 60.0f), 250.0f));
					shootTimer--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shootTimer >= 1) {
					checkLR = true;
					checkUP = false;
					energyballs.push_back(EnergyBall(&energyballRightTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 250.0f));
					shootTimer--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shootTimer >= 1) {
					checkLR = false;
					checkUP = false;
					energyballs.push_back(EnergyBall(&energyballLeftTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 250.0f));
					shootTimer--;

				}
				for (size_t i = 0; i < energyballs.size(); i++) {
					// energyball - corner
					energyballs[i].Update(elapsedTime, window, energyballs, checkUP, checkBott, checkLR); // ขวา , ซ้าย , บน
					if (energyballs[i].GetPosition().x >= window.getSize().x - 40.0f || energyballs[i].GetPosition().x <= 40.0f || energyballs[i].GetPosition().y <= 60.0f + 30.0f) {
						energyballs.erase(energyballs.begin() + i);
						shootTimer++;
					}
					else {
						// batboss - energyball
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (batboss.GetCollider().CheckCollision(energyballCollider)) {
								energyballs.erase(energyballs.begin() + i);
								//batboss.Update(elapsedTime,rand()%281-140.0f);
								*ptrScore += 50;
								*ptrBossHP -= 20;
								*ptrminionSpeed += 10;
								*ptrEnballSpeed += 5;
								shootTimer++;
								UpdateScore(&ssScore, ptrScore);
								UpdateScore(&ssBossHP, ptrBossHP);
							}
						}
					}
				}






				//printf("\n%f", bossEnBallTime);
				if (boolenball) {
					if ((int)bossEnBallTime % spawncount == 0.0f && (int)bossEnBallTime != 0) {
						printf("\n\t\tYOO");
						spawnbossBall = true;
						boolenball = false;
					}
				}
				else {
					spawncount += 5;
					boolenball = true;
				}




				if (spawnMinion[0]) {
					minionsLeft.push_back(Minion(&groundMinionRightTexture, sf::Vector2f(65.0f, 730.0f), sf::Vector2f(80.0f, 100.0f), 100.0f + (*ptrminionSpeed / 2)));
					spawnMinion[0] = false;
				}
				if (spawnMinion[1]) {
					minionsRight.push_back(Minion(&groundMinionLeftTexture, sf::Vector2f(640.0f, 730.0f), sf::Vector2f(80.0f, 100.0f), 100.0f + (*ptrminionSpeed / 2)));
					spawnMinion[1] = false;
				}
				if (spawnMinion[2]) {
					minionsUp1.push_back(Minion(&AirMinion01Texture, sf::Vector2f(655.0f, std::rand() % 141 + 490.0f), sf::Vector2f(70.0f, 50.0f), *ptrminionSpeed));
					spawnMinion[2] = false;
				}
				if (spawnMinion[3]) {
					minionsUp2.push_back(Minion(&AirMinion02Texture, sf::Vector2f(60.0f, std::rand() % 141 + 360.0f), sf::Vector2f(70.0f, 70.0f), *ptrminionSpeed));
					spawnMinion[3] = false;
				}
				if (spawnbossBall) {
					//for (int i = 0; i < 3; i++) {
						//printf("\nHello");
						//bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), 200.0f));
					//}
					int batbossPositionX = batboss.GetPosition().x;
					//int randombatbossSpawn = rand() % 441 - 220.0f;
					//while(batbossPositionX + randombatbossSpawn < 140.0f && batbossPositionX + randombatbossSpawn > 580.0f) {
					printf("\nHello");
					//batbossPositionX = batboss.GetPosition().x;
					int randombatbossSpawn = rand() % ((581 - batbossPositionX) - (batbossPositionX - 140)) - (batbossPositionX - 140.0f);
					printf("\n%d %d %d %d", batbossPositionX, randombatbossSpawn, (581 - batbossPositionX) - (batbossPositionX - 140), batbossPositionX - 140);
					//}
					batboss.Update(elapsedTime, randombatbossSpawn);
					if (*ptrBossHP <= 150) {
						bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x + 80.0f, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed));
					}
					if (*ptrBossHP <= 300) {
						bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x - 80.0f, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed));
					}
					//else {
					bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed));
					//}
					spawnbossBall = false;
				}


				megaman.Update(elapsedTime, window);
				batboss.Update(elapsedTime, 0.0f);
				sf::Vector2f direction;
				Collider megamanCollider = megaman.GetCollider();
				window.clear();
				//window.setView(view);
				window.draw(screen);
				//window.draw(screen);


				for (size_t i = 0; i < minionsLeft.size(); i++) {
					minionsLeft[i].Draw(window);
				}
				for (size_t i = 0; i < minionsLeft.size(); i++) {
					minionsLeft[i].Update(elapsedTime);
					// minionleft - corner / megaman
					if (minionsLeft[i].GetPosition().x >= window.getSize().x - 75) {
						minionsLeft.erase(minionsLeft.begin() + i);
						//spawnMinion[0] = true;
						//	spawnNum = (spawnNum + 1) % 4;
						//	printf("%d", spawnNum);
					}
					else if (minionsLeft[i].GetCollider().CheckCollision(megamanCollider)) {
						minionsLeft.erase(minionsLeft.begin() + i);
						//*ptrScore -= 20;
						*ptrMegaHP -= 20;
						//UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						// minionleft - energyball
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (minionsLeft[i].GetCollider().CheckCollision(energyballCollider)) {
								minionsLeft.erase(minionsLeft.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								//spawnMinion[0] = true;
								*ptrScore += 20;
								shootTimer++;
								*ptrenCount += 1;
								*ptrminionSpeed += 5;
								UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}

				for (size_t i = 0; i < minionsRight.size(); i++) {
					minionsRight[i].Draw(window);
				}
				for (size_t i = 0; i < minionsRight.size(); i++) {
					minionsRight[i].Update(elapsedTime);
					// minionright - corner / megaman
					if (minionsRight[i].GetPosition().x <= 60) {
						minionsRight.erase(minionsRight.begin() + i);
						//spawnMinion[1] = true;
						//	printf("%d", spawnNum);
					}
					else if (minionsRight[i].GetCollider().CheckCollision(megamanCollider)) {
						minionsRight.erase(minionsRight.begin() + i);
						//*ptrScore -= 20;
						*ptrMegaHP -= 20;
						//UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						// minionleft - energyball
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (minionsRight[i].GetCollider().CheckCollision(energyballCollider)) {
								minionsRight.erase(minionsRight.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								//spawnMinion[1] = true;
								*ptrScore += 20;
								shootTimer++;
								*ptrenCount += 1;
								*ptrminionSpeed += 5;
								UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}

				for (size_t i = 0; i < minionsUp1.size(); i++) {
					minionsUp1[i].Draw(window);
				}
				for (size_t i = 0; i < minionsUp1.size(); i++) {
					minionsUp1[i].Update(elapsedTime);
					// minionup1 - corner / megaman
					if (minionsUp1[i].GetPosition().x <= 60) {
						minionsUp1.erase(minionsUp1.begin() + i);
						spawnMinion[2] = true;
						//	printf("%d", spawnNum);
					}
					else if (minionsUp1[i].GetCollider().CheckCollision(megamanCollider)) {
						minionsUp1.erase(minionsUp1.begin() + i);
						spawnMinion[2] = true;
						//*ptrScore -= 20;
						*ptrMegaHP -= 20;
						//UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						// minionup1 - energyball
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (minionsUp1[i].GetCollider().CheckCollision(energyballCollider)) {
								minionsUp1.erase(minionsUp1.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								spawnMinion[2] = true;
								*ptrScore += 20;
								shootTimer++;
								*ptrenCount += 1;
								*ptrminionSpeed += 5;
								UpdateScore(&ssScore, ptrScore);
							}

						}
					}
				}

				for (size_t i = 0; i < minionsUp2.size(); i++) {
					minionsUp2[i].Draw(window);
				}
				for (size_t i = 0; i < minionsUp2.size(); i++) {
					minionsUp2[i].Update(elapsedTime);
					// minionup2 - corner / megaman
					if (minionsUp2[i].GetPosition().x >= window.getSize().x - 70) {
						minionsUp2.erase(minionsUp2.begin() + i);
						spawnMinion[3] = true;

						//	printf("%d", spawnNum);
					}
					else if (minionsUp2[i].GetCollider().CheckCollision(megamanCollider)) {
						minionsUp2.erase(minionsUp2.begin() + i);
						spawnMinion[3] = true;
						//*ptrScore -= 20;
						*ptrMegaHP -= 20;
						//UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						// minionup2 - energyball
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (minionsUp2[i].GetCollider().CheckCollision(energyballCollider)) {
								minionsUp2.erase(minionsUp2.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								spawnMinion[3] = true;
								*ptrScore += 20;
								shootTimer++;
								*ptrenCount += 1;
								*ptrminionSpeed += 5;
								UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}



				for (size_t i = 0; i < bossballs.size(); i++) {
					bossballs[i].Draw(window);
				}
				for (size_t i = 0; i < bossballs.size(); i++) {
					bossballs[i].Update(elapsedTime, window, energyballs, true, 1, false); //bottom
					if (bossballs[i].GetPosition().y >= window.getSize().y - 230.0f) {
						bossballs.erase(bossballs.begin() + i);
					}
					else if (bossballs[i].GetCollider().CheckCollision(megamanCollider)) {
						bossballs.erase(bossballs.begin() + i);
						//*ptrScore -= 50;
						*ptrMegaHP -= 40;
						//UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (bossballs[i].GetCollider().CheckCollision(energyballCollider)) {
								bossballs.erase(bossballs.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								shootTimer++;
								*ptrScore += 10;
								UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}




				if (*ptrenCount == 3) {
					int randomItems = rand() % 3 + 1;
					//int dataItem[colldataitem]
					sf::Vector2f randomSpawnItems(rand() % 621 + 50.0f, rand() % 181 + 220.0f);
					switch (randomItems) {
					case 1:
						HPItem.push_back(Items(&HPTexture, randomSpawnItems, sf::Vector2f(40.0f, 40.0f)));
						break;
					case 2:
						//coinItem.push_back(Items(&coinTexture,sf::Vector2f(randomSpawnItems.x,70.0f), sf::Vector2f(40.0f, 40.0f)));
						for (int i = 0; i < 5; i++) {
							coinItem.push_back(Items(&coinTexture, sf::Vector2f(rand() % 615 + 35.0f, 80.0f), sf::Vector2f(40.0f, 40.0f)));
						}
						break;
					case 3:
						trapItem.push_back(Items(&TrapTexture, randomSpawnItems, sf::Vector2f(45.0f, 35.0f)));
						break;
					}
					*ptrenCount = 0;
				}

				//window.draw(ground);
				//window.draw(leftWall);
				//window.draw(rightWall);
				//window.draw(upWall);
				for (size_t i = 0; i < energyballs.size(); i++) {
					energyballs[i].Draw(window);
				}
				for (size_t i = 0; i < HPItem.size(); i++) {
					HPItem[i].Draw(window);
				}
				// HP - energyball
				for (size_t i = 0; i < HPItem.size(); i++) {
					//HPItem[i].Move(elapsedTime);
					if (HPItem[i].GetPosition().y >= window.getSize().y - 210.0f) {
						HPItem.erase(HPItem.begin() + i);
					}
					else if (HPItem[i].GetCollider().CheckCollision(megamanCollider)) {
						HPItem.erase(HPItem.begin() + i);
						*ptrScore += 20;
						*ptrMegaHP += 20;
						UpdateScore(&ssScore, ptrScore);
						UpdateScore(&ssMegaHP, ptrMegaHP);
					}
					else {
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (HPItem[i].GetCollider().CheckCollision(energyballCollider)) {
								HPItem[i].Update(elapsedTime, 1, ptrScore);
								HPItem.erase(HPItem.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								shootTimer++;
								*ptrScore += 20;
								*ptrMegaHP += 20;
								UpdateScore(&ssScore, ptrScore);
								UpdateScore(&ssMegaHP, ptrMegaHP);

							}
						}
					}
				}

				for (size_t i = 0; i < coinItem.size(); i++) {
					coinItem[i].Draw(window);
				}
				// Coin - energyball
				for (size_t i = 0; i < coinItem.size(); i++) {
					coinItem[i].Move(elapsedTime);
					if (coinItem[i].GetPosition().y >= window.getSize().y - 210.0f) {
						coinItem.erase(coinItem.begin() + i);
					}
					else if (coinItem[i].GetCollider().CheckCollision(megamanCollider)) {
						coinItem.erase(coinItem.begin() + i);
						*ptrScore += 20;
						UpdateScore(&ssScore, ptrScore);
					}
					else {
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (coinItem[i].GetCollider().CheckCollision(energyballCollider)) {
								coinItem[i].Update(elapsedTime, 2, ptrScore);
								coinItem.erase(coinItem.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								shootTimer++;
								*ptrScore += 20;
								UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}
				for (size_t i = 0; i < trapItem.size(); i++) {
					trapItem[i].Draw(window);
				}
				// Trap - energyball
				for (size_t i = 0; i < trapItem.size(); i++) {
					//trapItem[i].Move(elapsedTime);
					if (trapItem[i].GetPosition().y >= window.getSize().y - 210.0f) {
						trapItem.erase(trapItem.begin() + i);
					}
					else if (trapItem[i].GetCollider().CheckCollision(megamanCollider)) {
						trapItem.erase(trapItem.begin() + i);
						spawnMinion[0] = true;
						spawnMinion[1] = true;
						//*ptrScore -= 20;
						//UpdateScore(&ssScore, ptrScore);
					}
					else {
						for (size_t j = 0; j < energyballs.size(); j++) {
							Collider energyballCollider = energyballs[j].GetCollider();
							if (trapItem[i].GetCollider().CheckCollision(energyballCollider)) {
								trapItem[i].Update(elapsedTime, 3, ptrScore);
								trapItem.erase(trapItem.begin() + i);
								energyballs.erase(energyballs.begin() + j);
								spawnMinion[0] = true;
								spawnMinion[1] = true;
								shootTimer++;
								//*ptrScore -= 20;
								//UpdateScore(&ssScore, ptrScore);
							}
						}
					}
				}
				//if (*ptrMegaHP == 0) {
				//	break;
				//}
				batboss.Draw(window);
				megaman.Draw(window);
				window.draw(TextScore);
				window.draw(MegaHP);
				window.draw(BossHP);
				window.display();
			}

			if (Screen[4]) {
				clock.restart();
				spawnClock.restart();

				Back.setFont(menuFont);
				Back.setString("BACK");
				//menuText[0].setFillColor(sf::Color::White);
				Back.setCharacterSize(50);
				Back.setPosition(50.0f, 885.0f);

				Next.setFont(menuFont);
				Next.setString("EXIT");
				//menuText[1].setFillColor(sf::Color::White);
				Next.setCharacterSize(50);
				Next.setPosition(565.0f, 885.0f);

				if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					Back.setFillColor(sf::Color::Cyan);
					Back.setStyle(sf::Text::Italic);
				}
				else {
					Back.setFillColor(sf::Color::White);
					Back.setStyle(0);
				}
				if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					Next.setFillColor(sf::Color::Cyan);
					Next.setStyle(sf::Text::Italic);
				}
				else {
					Next.setFillColor(sf::Color::White);
					Next.setStyle(0);
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (Back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							Screen[2] = false;
							Screen[0] = true;
						}
					}
					if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						Screen[2] = false;
						Screen[3] = true;
					}
				}
				window.clear();
				window.draw(HTP);
				window.draw(Back);
				window.draw(Next);
				window.display();
			}
		}
		return 0;
}