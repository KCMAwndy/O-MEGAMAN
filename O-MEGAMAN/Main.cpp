#define _CRT_SECURE_NO_WARNINGS
#include<SFML\Graphics.hpp>
#include<stdio.h>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include"Animation.h"
#include"Megaman.h"
#include"Collider.h"
#include"Platform.h"
#include"EnergyBall.h"
#include"Minion.h"
#include"BatBoss.h"
#include"MiniBoss.h"
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
void ShowOderScore(sf::RenderWindow& window, sf::Text ScrOder[]);

struct score {
	std::string Plr;
	int Scr;
};
struct score ScBoard[5];

int main() {
	std::srand(time(NULL));
	bool Screen[5] = { true,false,false,false,false };
	int enCount=0,score=0,megaHP=100,bossHp=500,minionSpeed=80,enballSpeed=250,iceCount=0,bossCount=0;
	//int ballBossCount = 5;
	//int iceBossSpawn = 3;
	//int spawnIceHit = 1;
	bool checkLR = true;
	bool checkUP = false;
	int checkBott = 0;
	int shootTimer = 1;
	int minionDropInt[2] = { 3,3 };
	int snakeShoot = 1;
	int *ptrenCount,*ptrScore,*ptrMegaHP,*ptrBossHP,*ptrminionSpeed, *ptrEnballSpeed,*ptrdeCount, *ptriceCount,*ptrbossCount;
	ptrenCount = &enCount;
	ptrScore = &score;
	ptrMegaHP = &megaHP;
	ptrBossHP = &bossHp;
	ptrminionSpeed = &minionSpeed;
	ptrEnballSpeed = &enballSpeed;
	ptriceCount = &iceCount;
	ptrbossCount = &bossCount;
	bool spawnMinion[4] = { false,false,true,true };
	//bool boolenball = true;
	bool boolMinion[2] = { true,true };
	//bool booliceMove = true;
	//bool spawnbossBall = false;
	//bool despawnMinionUp1 = false;
	bool playerEnter = true;
	bool GameOver = false;
	char temp[256] = {" "};
	float collectTime[8] = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
	bool boolDelay[8] = { false,false,true,false,false,false,false,false };
	bool boolSheild=false;
	//bool icebossHunt = false;
	//bool iceboosDrop = true;
	bool snakeSpawn = true;
	bool snakeHunt = true;
	//bool iceHit = false;
	//bool fireHit = false;
	//bool dead = false;
	//bool deadBoss = false;
	//int HMitem[3] = { 0,0,0 };
	//float spawnNum = 0.0f;

	sf::RenderWindow window(sf::VideoMode(720, 960), "O-MEGAMAN GAME", sf::Style::Close | sf::Style::Resize);
	//	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::Texture megamanTexture;
	megamanTexture.loadFromFile("Images/Megaman_movement3.png");
	Megaman megaman(&megamanTexture, sf::Vector2u(3, 5), 0.8f, 150.0f, 300.0f);

	sf::Texture batbossTexture;
	batbossTexture.loadFromFile("Images/MegaBoss_Movement2.png");
	BatBoss batboss(&batbossTexture, sf::Vector2u(2, 2), 0.9f, sf::Vector2f(360.0f, 140.0f), 150.0f);

	sf::Texture iceBossTexture;
	iceBossTexture.loadFromFile("Images/miniBoss2.png");
	MiniBoss iceboss(&iceBossTexture, sf::Vector2u(4, 1), 0.9f, sf::Vector2f(360.0f, 240.0f), 200.0f,3);

	sf::Texture energyballRightTexture;
	energyballRightTexture.loadFromFile("Images/EnergyBallRight.png");
	sf::Texture energyballLeftTexture;
	energyballLeftTexture.loadFromFile("Images/EnergyBallleft.png");
	sf::Texture megaBulletTexture;
	megaBulletTexture.loadFromFile("Images/MegaBullet.png");
	sf::Texture iceDropTexture;
	iceDropTexture.loadFromFile("Images/minibossSnow.png");
	sf::Texture minionDropTexture;
	minionDropTexture.loadFromFile("Images/Trap.png");
	sf::Texture snakeShootTexture;
	snakeShootTexture.loadFromFile("Images/SnakeBall.png");
	sf::Texture HitManTextrue;
	HitManTextrue.loadFromFile("Images/Hitman2.png");
	sf::Texture bossBulletTexture;
	bossBulletTexture.loadFromFile("Images/MegaBossEnergyBall.png");
	sf::Texture groundMinionLeftTexture;
	groundMinionLeftTexture.loadFromFile("Images/groundMinion_Left.png");
	sf::Texture groundMinionRightTexture;
	groundMinionRightTexture.loadFromFile("Images/groundMinion_Right.png");
	sf::Texture AirMinion01Texture;
	AirMinion01Texture.loadFromFile("Images/AirMinion_1.png");
	sf::Texture AirMinion02Texture;
	AirMinion02Texture.loadFromFile("Images/AirMinion_2.png");
	sf::Texture snakeLeftTaxture;
	snakeLeftTaxture.loadFromFile("Images/SnakeLeft.png");
	sf::Texture snakeRightTaxture;
	snakeRightTaxture.loadFromFile("Images/SnakeRight.png");

	std::vector<Minion> minionsLeft;
	std::vector<Minion> minionsRight;
	std::vector<Minion> minionsUp1;
	std::vector<Minion> minionsUp2;
	std::vector<Minion> snake;

	std::vector<class EnergyBall>	energyballs;
	std::vector<class EnergyBall>	bossballs;
	std::vector<class EnergyBall>	icedrop;
	std::vector<class EnergyBall>	minionUp1_balls;
	std::vector<class EnergyBall>	minionUp2_balls;
	std::vector<class EnergyBall>   snakeLeftBall;
	std::vector<class EnergyBall>   snakeRightBall;
	std::vector<class EnergyBall>   hitman;

	std::vector<Items> HPItem;
	std::vector<Items> coinItem;
	std::vector<Items> trapItem;
	std::vector<Items> shieldItem;
	sf::Texture HPTexture;
	HPTexture.loadFromFile("Images/Heart.png");
	sf::Texture coinTexture;
	coinTexture.loadFromFile("Images/Coin.png");
	sf::Texture TrapTexture;
	TrapTexture.loadFromFile("Images/Trap2.png");
	sf::Texture ShieldTexture;
	ShieldTexture.loadFromFile("Images/Shield.png");

	sf::Font scoreFont;
	scoreFont.loadFromFile("Fonts/TIme TRap.ttf");
	std::ostringstream ssScore;
	ssScore << *ptrScore;
	std::ostringstream ssMegaHP;
	ssMegaHP << *ptrMegaHP;
	std::ostringstream ssBossHP;
	ssBossHP << *ptrBossHP;
	std::ostringstream ssResult;
	ssResult << "Your Score : " ;
	std::ostringstream ssplName;
	ssplName << "Ener your name ";
	std::ostringstream ssdisScore;
	ssdisScore << *ptrScore;
	
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
	sf::Text menuText[4];

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

	sf::Texture winTexture;
	sf::Sprite win;
	winTexture.loadFromFile("Images/Youwin.png");
	win.setTexture(winTexture);
	win.setPosition(0.0f, 0.0f);

	sf::Texture GameoverTexture;
	sf::Sprite Gameover;
	GameoverTexture.loadFromFile("Images/Gameover.png");
	Gameover.setTexture(GameoverTexture);
	Gameover.setPosition(0.0f, 0.0f);

	sf::Texture ExitTexture;
	sf::Sprite Exit;
	ExitTexture.loadFromFile("Images/Exit.png");
	Exit.setTexture(ExitTexture);
	Exit.setPosition(0.0f, 0.0f);

	sf::Texture CreditTexture;
	sf::Sprite Credit;
	CreditTexture.loadFromFile("Images/credit.png");
	Credit.setTexture(CreditTexture);
	Credit.setPosition(0.0f, 0.0f);

	int order = 0;

	sf::Text Back;
	sf::Text Next;

	sf::String playerInput;
	sf::Text playerText;

	std::string playerName;

	//float spawnTime = 0.0f;
	float elapsedTime = 0.0f;
	double bossEnBallTime = 0.0f;
	double icebossTime = 0.0f;
	double despawnTime = 0.0f;
	double HuntTime = 0.0f;
	double SnakeTime = 0.0f;
	double minionTime[2] = { 0.0f,0.0f };
	bool deCheck=false;
	bool SnakeShootface = true;
	bool quickExit = false;
	//if (Screen[3]) 
	//}
	//std::ofstream writefile;
	//writefile.open("Score_Board.txt",std::ios::app);

	std::ifstream inputFile;
	std::ofstream outputFile;

	sf::Clock clock;
	sf::Clock spawnClock;
	sf::Clock delayClock;
	sf::Clock HuntClock;
	sf::Clock SnakeClock;
	sf::Clock minionClock_1;
	sf::Clock minionClock_2;

	printf("%f", elapsedTime);
	while (window.isOpen()) {
		sf::Event evnt;
		//DelaySpawn();
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
			if (Screen[4]) {
				int ScrInt, j = 0, tempScore, order, tempScore2;
				std::string PlrString, tmpName, tmpName2;
				playerText.setCharacterSize(50);
				playerText.setFont(menuFont);
				playerText.setFillColor(sf::Color::Yellow);
				playerText.setPosition(210.0f, 505.0f);
				if (evnt.type == sf::Event::TextEntered) {
					if (evnt.text.unicode < 128 && playerEnter) {
						playerInput += evnt.text.unicode;
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
							playerInput = playerInput.substring(0, playerInput.getSize() - 2);
						}
						playerText.setString(playerInput);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && playerEnter) {
						playerName = playerInput;
						//Scoretemp = *ptrScore;
						//std::cout << playerName << std::endl;
						playerEnter = false;
						inputFile.open("Score_Board.txt");
						if (inputFile.is_open()) {
							while (!inputFile.eof()) {
								inputFile >> PlrString >> ScrInt;
								ScBoard[j].Plr = PlrString;
								ScBoard[j].Scr = ScrInt;
								j++;
							}
							inputFile.close();
						}
						for (int i = 0; i < 5; i++) {
							if (ScBoard[i].Scr < *ptrScore) {
								tmpName = ScBoard[i].Plr;
								tempScore = ScBoard[i].Scr;
								ScBoard[i].Scr = *ptrScore;
								ScBoard[i].Plr = playerName;
								order = i;
								for (int j = order + 1; j < 5; j++) {
									tmpName2 = ScBoard[j].Plr;
									tempScore2 = ScBoard[j].Scr;
									ScBoard[j].Plr = tmpName;
									ScBoard[j].Scr = tempScore;
									tmpName = tmpName2;
									tempScore = tempScore2;
									i++;
								}
							}
						}
						outputFile.open("Score_Board.txt");
						if (outputFile.is_open()) {
							for (int i = 0; i < 5; i++) {
								outputFile << ScBoard[i].Plr << " " << ScBoard[i].Scr << std::endl;
							}
							outputFile.close();
						}
					}
				}
			}
		}
				//printf("%f", elapsedTime);
				if (Screen[0]) {
					clock.restart();
					spawnClock.restart();
					delayClock.restart();
					HuntClock.restart();
					SnakeClock.restart();
					minionClock_1.restart();
					minionClock_2.restart();

					menuText[0].setFont(menuFont);
					menuText[0].setString("Start");
					//menuText[0].setFillColor(sf::Color::White);
					menuText[0].setCharacterSize(50);
					menuText[0].setPosition(285.0f,360.0f);

					menuText[1].setFont(menuFont);
					menuText[1].setString("Score Board");
					//menuText[1].setFillColor(sf::Color::White);
					menuText[1].setCharacterSize(50);
					menuText[1].setPosition(212.0f, 420.0f);

					menuText[2].setFont(menuFont);
					menuText[2].setString("CREDIT");
					//menuText[3].setFillColor(sf::Color::White);
					menuText[2].setCharacterSize(50);
					menuText[2].setPosition(275.0f, 480.0f);

					menuText[3].setFont(menuFont);
					menuText[3].setString("Exit");
					//menuText[3].setFillColor(sf::Color::White);
					menuText[3].setCharacterSize(50);
					menuText[3].setPosition(315.0f, 540.0f);	

					for (int i = 0; i < 4; i++) {
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
								Screen[3] = true;
							}
						}
						if (menuText[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
								Screen[0] = false;
								Screen[1] = true;

						}
						if (menuText[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							Screen[0] = false;
							Screen[2] = true;

						}
						if (menuText[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							break;
						}
					}

					window.clear();
					window.draw(menu);
					for (int i = 0; i < 4; i++) {
						window.draw(menuText[i]);
					}
					window.display();
				}

				if (Screen[1]) {
					clock.restart();
					spawnClock.restart();
					delayClock.restart();
					HuntClock.restart();
					SnakeClock.restart();
					minionClock_1.restart();
					minionClock_2.restart();

					int ScrInt, j = 0;
					sf::Text ScrOder[5];
					std::ostringstream ssScrOder[5];
					std::string PlrString;
					inputFile.open("Score_Board.txt");

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
					if (inputFile.is_open()) {
						while (!inputFile.eof()) {
							inputFile >> PlrString >> ScrInt;
							ScBoard[j].Plr = PlrString;
							ScBoard[j].Scr = ScrInt;
							j++;
						}
						inputFile.close();
					}
					for (int i = 0; i < 5; i++) {
						ScrOder[i].setFont(menuFont);
						ScrOder[i].setCharacterSize(50);
						ScrOder[i].setPosition(100.0f, 240.0f + (80.0f * i));
						ssScrOder[i] << i+1 << " )"<<"\t"<<ScBoard[i].Plr << "\t" << ScBoard[i].Scr;
						ScrOder[i].setString(ssScrOder[i].str());
					}
					window.clear();
					window.draw(SB);
					window.draw(Back);
					ShowOderScore(window, ScrOder);
					window.display();
				}

				if (Screen[2]) {
					clock.restart();
					spawnClock.restart();
					delayClock.restart();
					HuntClock.restart();
					SnakeClock.restart();
					minionClock_1.restart();
					minionClock_2.restart();

					Back.setFont(menuFont);
					Back.setString("BACK");
					//menuText[0].setFillColor(sf::Color::White);
					Back.setCharacterSize(50);
					Back.setPosition(50.0f, 885.0f);


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
								Screen[2] = false;
								Screen[0] = true;
							}
						}
					}

					window.clear();
					window.draw(Credit);
					window.draw(Back);
					window.display();
				}



				if (Screen[3]) {
					//printf("\n%f", elapsedTime);
					elapsedTime = clock.restart().asSeconds();
					bossEnBallTime = spawnClock.getElapsedTime().asSeconds();
					icebossTime = spawnClock.getElapsedTime().asSeconds();
					delayClock.getElapsedTime().asSeconds();
					HuntClock.getElapsedTime().asSeconds();

					//std::cout << despawnTime << std::endl;
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

					Collider megamanCollider = megaman.GetCollider();
					Collider icebossCollider = iceboss.GetCollider();

					EnergyBall energyBallR(&energyballRightTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 250.0f);
					EnergyBall energyBallL(&energyballLeftTexture, megaman.GetPosition(), sf::Vector2f(40.0f, 30.0f), 250.0f);
					EnergyBall energyBallB(&megaBulletTexture, sf::Vector2f(megaman.GetPosition().x, megaman.GetPosition().y - megaman.GetOrigin().y), sf::Vector2f(25.0f, 60.0f), 250.0f);
					EnergyBall snakeBall(&snakeShootTexture, sf::Vector2f(640.0f, 760.0f), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed);
					EnergyBall hitmanStrike(&HitManTextrue, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed);



					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
						quickExit = true;
						Screen[4] = true;
						Screen[3] = false;
					}
					if (!megaman.dead && !megaman.fireHit && !megaman.iceHit) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && shootTimer >= 1) {
							checkLR = false;
							checkUP = true;
							checkBott = -1;
							energyballs.push_back(energyBallB);
							shootTimer--;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shootTimer >= 1) {
							checkLR = true;
							checkUP = false;
							energyballs.push_back(energyBallR);
							shootTimer--;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shootTimer >= 1) {
							checkLR = false;
							checkUP = false;
							energyballs.push_back(energyBallL);
							shootTimer--;
						}
					}
					for (size_t i = 0; i < energyballs.size(); i++) {
						// energyball - corner
						energyballs[i].Update(elapsedTime, window, energyballs, checkUP, checkBott, checkLR); // ขวา , ซ้าย , บน
						if (energyballs[i].GetPosition().x >= window.getSize().x - 40.0f || energyballs[i].GetPosition().x <= 40.0f || energyballs[i].GetPosition().y <= 60.0f + 30.0f) {
							energyballs.erase(energyballs.begin() + i);
							shootTimer++;
						}
						else if (energyballs[i].GetCollider().CheckCollision(icebossCollider)) {
							energyballs.erase(energyballs.begin() + i);
							*ptriceCount += 1;
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
									*ptrminionSpeed += 5;
									*ptrEnballSpeed += 5;
									*ptrbossCount += 1;
									shootTimer++;
									UpdateScore(&ssScore, ptrScore);
									UpdateScore(&ssBossHP, ptrBossHP);
								}
							}
						}
					}






					//printf("\n%d",iceboss.spawnCount);
				
					if (batboss.bossShoot) {
						if ((int)bossEnBallTime % batboss.ballBossCount == 0.0f && (int)bossEnBallTime != 0) {
							//printf("\n\t\tYOO");
							batboss.spawnbossBall = true;
							batboss.bossShoot = false;
						}
					}
					else {
						batboss.ballBossCount += 5;
						batboss.bossShoot = true;
					}

					if (!boolDelay[0]) {
						minionTime[0] = minionClock_1.getElapsedTime().asSeconds();
						if (boolMinion[0]) {
							if ((int)minionTime[0] % minionDropInt[0] == 0.0f && (int)minionTime[0] != 0) {
								//printf("\n\t\tYOO");
								for (size_t i = 0; i < minionsUp1.size(); i++) {
									EnergyBall bombMinion(&minionDropTexture, sf::Vector2f(minionsUp1[i].GetPosition()), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed);
									minionUp1_balls.push_back(bombMinion);
								}
								boolMinion[0] = false;
							}
						}
						else {
							minionDropInt[0] += 3;
							boolMinion[0] = true;
						}
					}
					if (!boolDelay[1]) {
						minionTime[1] = minionClock_2.getElapsedTime().asSeconds();
						if (boolMinion[1]) {
							if ((int)minionTime[1] % minionDropInt[1] == 0.0f && (int)minionTime[1] != 0) {
								//printf("\n\t\tYOO");
								for (size_t i = 0; i < minionsUp2.size(); i++) {
									EnergyBall bombMinion(&minionDropTexture, sf::Vector2f(minionsUp2[i].GetPosition()), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed);
									minionUp2_balls.push_back(bombMinion);
								}
								boolMinion[1] = false;
							}
						}
						else {
							minionDropInt[1] += 3;
							boolMinion[1] = true;
						}
					}
					//printf("%d\n", iceHuntCount);
				


					if (boolDelay[0]) {
						if (iceboss.icebossHunt) {
							spawnMinion[2] = false;
							boolDelay[0] = false;
						}
						else {
							//delayClock.restart().asSeconds();
							collectTime[0] += elapsedTime;
							if (collectTime[0] >= 3.0f) {
								spawnMinion[2] = true;
								boolDelay[0] = false;
								collectTime[0] -= 3;
								minionDropInt[0] += 3;
							}
						}
					}
					//printf("%f", delayClock);
					if (boolDelay[1]) {
						if (iceboss.icebossHunt) {
							spawnMinion[3] = false;
							boolDelay[1] = false;
						}
						else {
							//delayClock.restart().asSeconds();
							collectTime[1] += elapsedTime;
							if (collectTime[1] >= 3.0f) {
								spawnMinion[3] = true;
								boolDelay[1] = false;
								collectTime[1] -= 3;
							}
						}
					}

					
					
					if (*ptriceCount == 4) {
						boolDelay[3] = true;
					}
					else if (*ptriceCount == 2) {
						*ptriceCount += 1;
						shieldItem.push_back(Items(&ShieldTexture, megaman.GetPosition(), sf::Vector2f(100.0f, 100.0f)));
						boolSheild = true;
					}
					
					if (*ptrbossCount == 3) {
						*ptrbossCount = 0;
						//for (int i = 0; i < 2; i++) {
							//EnergyBall hitmanStrike(&HitManTextrue, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed);
							hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
							hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(35.0f,rand()%381+275.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
							hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(685.0f, rand() % 381 + 275.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
						//}
					}


					//printf("%d %d\n", shieldItem.size(), *ptriceCount);


					if (boolDelay[3]) {
						if (iceboss.icebossHunt) {
							boolDelay[3] = false;
						}
						else {
							*ptriceCount = 1;
							//delayClock.restart().asSeconds();
							//snakeHunt = false;
							collectTime[3] += elapsedTime;
							if (collectTime[3] >= 10.0f) {
							//	snakeHunt=true;
								boolDelay[3] = false;
								collectTime[3] -= 10;
								snakeShoot = 1;
							}
							if (snakeSpawn) {
								//SnakeTime = SnakeClock.getElapsedTime().asSeconds();
								if ((int)collectTime[3] % snakeShoot == 0.0f && (int)collectTime[3] != 0) {
									snake.push_back(Minion(&snakeLeftTaxture, sf::Vector2f(80.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									snakeBall.SetPosition(sf::Vector2f(80.0f, 760.0f));
									snakeLeftBall.push_back(snakeBall);
									snakeSpawn = false;
								}
								if ((int)snakeShoot == 10) {
								for (size_t i = 0; i < snake.size(); i++) {
										snake.erase(snake.begin() + i);
									}
								}
							}
							else {
								snakeShoot += 1;
								snakeSpawn = true;
							}
						}
					}

					if (boolDelay[4]) {
						if (!megaman.dead) {
							//delayClock.restart().asSeconds();
							collectTime[4] += elapsedTime;
							if (collectTime[4] >= 5.0f) {
								boolDelay[4] = false;
								megaman.iceHit = false;
								collectTime[4] -= 5;
							}
						}
					}
					if (boolDelay[5]) {
						if (!megaman.dead) {
							//delayClock.restart().asSeconds();
							collectTime[5] += elapsedTime;
							if (collectTime[5] >= 5.0f) {
								boolDelay[5] = false;
								megaman.fireHit = false;
								collectTime[5] -= 5;
							}
						}
					}
					if (boolDelay[6]) {
						//delayClock.restart().asSeconds();
						collectTime[6] += elapsedTime;
						if (collectTime[6] >= 3.0f) {
							Screen[3] = false;
							Screen[4] = true;
							GameOver = true;
							collectTime[6] -= 3;
						}
					}
					if (boolDelay[7]) {
						//delayClock.restart().asSeconds();
						collectTime[7] += elapsedTime;
						if (collectTime[7] >= 3.0f) {
							Screen[3] = false;
							Screen[4] = true;
							GameOver = false;
							collectTime[7] -= 3;
						}
					}


					if (boolSheild) {
						collectTime[2] += elapsedTime;
						if (collectTime[2] >= 10.0f) {
							boolSheild = false;
							for (size_t i = 0; i < shieldItem.size(); i++) {
									shieldItem.erase(shieldItem.begin() + i);
							}
							collectTime[2] -= 10;
						}
					}
					//printf("%d\n", iceboss.spawnCount);
				

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
					if (batboss.spawnbossBall) {
						//for (int i = 0; i < 3; i++) {
							//printf("\nHello");
							//bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), 200.0f));
						//}
						int batbossPositionX = batboss.GetPosition().x;
						//int randombatbossSpawn = rand() % 441 - 220.0f;
						//while(batbossPositionX + randombatbossSpawn < 140.0f && batbossPositionX + randombatbossSpawn > 580.0f) {
						//printf("\nHello");
						//batbossPositionX = batboss.GetPosition().x;
						int randombatbossSpawn = rand() % ((581 - batbossPositionX) - (batbossPositionX - 140)) - (batbossPositionX - 140.0f);
						//printf("\n%d %d %d %d", batbossPositionX, randombatbossSpawn, (581 - batbossPositionX) - (batbossPositionX - 140), batbossPositionX - 140);
						//}
						batboss.Update(elapsedTime, randombatbossSpawn, batboss.deadBoss);
						//batboss.Update(elapsedTime, megaman.GetPosition().x-batboss.GetPosition().x);
						EnergyBall bossBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed);
						bossballs.push_back(bossBall);
						if (*ptrBossHP <= 150) {
							bossBall.SetPosition(sf::Vector2f(batboss.GetPosition().x + 80.0f, batboss.GetPosition().y));
							//bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x + 80.0f, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed));
							bossballs.push_back(bossBall);
						}
						if (*ptrBossHP <= 300) {
							bossBall.SetPosition(sf::Vector2f(batboss.GetPosition().x - 80.0f, batboss.GetPosition().y));
							//bossballs.push_back(EnergyBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x - 80.0f, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed));
							bossballs.push_back(bossBall);
						}
						//else {
						//}
						batboss.spawnbossBall = false;
					}


					megaman.Update(elapsedTime, window, megaman.iceHit,megaman.fireHit,megaman.dead);
					batboss.Update(elapsedTime, 0.0f, batboss.deadBoss);

					if (boolDelay[0] && boolDelay[1]) {
						if (boolDelay[3]) {
							iceboss.icebossHunt = false;
						}
						else {
							iceboss.icebossHunt = true;
						}
					}
					if (iceboss.icebossHunt) {
						iceboss.Hunt(elapsedTime);
						*ptriceCount = 0;

						//switch (iceboosDrop) {
						//case 1:
						if (iceboss.iceboosDrop) {
							//for (int i = 0; i < 5; i++) {
							//	coinItem.push_back(Items(&coinTexture, sf::Vector2f(rand() % 615 + 35.0f, 80.0f), sf::Vector2f(40.0f, 40.0f)));
							//}
							//iceboosDrop = false;
							//break;
							//int randomSnakeSpawn = rand() % 2 + 1;
							int randomSnakeSpawn = 2;
							if (boolDelay[2]) {
								HuntTime += elapsedTime;
								if ((int)HuntTime % iceboss.spawnIceHit == 0.0f && (int)HuntTime != 0) {
									for (int i = 0; i < 2; i++) {
										EnergyBall iceBossDrop(&iceDropTexture, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(40.0f, 70.0f), *ptrEnballSpeed);
										icedrop.push_back(iceBossDrop);
									}
									boolDelay[2] = false;
								}
							}
							else {
								iceboss.spawnIceHit += 1;
								boolDelay[2] = true;
							}
							if (snakeSpawn) {
								switch (randomSnakeSpawn) {
								case 1:
									snake.push_back(Minion(&snakeLeftTaxture, sf::Vector2f(80.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									SnakeShootface = true;
									snakeSpawn = false;
									break;
								case 2:
									snake.push_back(Minion(&snakeRightTaxture, sf::Vector2f(640.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									SnakeShootface = false;
									snakeSpawn = false;
									break;
								}
							}
						}
						//iceboosDrop = true;
						if (iceboss.GetPosition().y >= 825.0f) {
							iceboss.SetPosition(sf::Vector2f(360.0f, 240.0f));
							iceboss.icebossHunt = false;
							spawnMinion[2] = true;
							spawnMinion[3] = true;
							iceboss.iceboosDrop = true;
							snakeSpawn = true;
							HuntTime = 0;
							iceboss.spawnIceHit = 1;
							for (size_t i = 0; i < snake.size(); i++) {
								snake.erase(snake.begin() + i);
							}
						
						}
					
					}
					else {
						if (iceboss.booliceMove) {
							if ((int)icebossTime % iceboss.spawnCount == 0.0f && (int)icebossTime != 0) {
								int icebossPositionX = iceboss.GetPosition().x;
								int randomicebossSpawn = rand() % ((581 - icebossPositionX) - (icebossPositionX - 140)) - (icebossPositionX - 140.0f);
								iceboss.booliceMove = false;
								iceboss.Update(elapsedTime, randomicebossSpawn);
								//printf("%f\t%d\n", iceboss.GetPosition().x, randomicebossSpawn);
							}
						}
						else {
							iceboss.spawnCount += 3;
							iceboss.booliceMove = true;
						}
						//iceboss.Update(elapsedTime, (360.0f, 240.0f));
						iceboss.Update(elapsedTime, 0);
					}
					//printf("\n%lf %d", minionTime[0], minionDropInt[0]);
					//printf("%d\n", collectSnakeShoot);
				//printf("\n%lf ", collectTime[3]);



					sf::Vector2f direction;
					window.clear();
					//window.setView(view);
					window.draw(screen);
					//window.draw(screen);


					for (size_t i = 0; i < minionsLeft.size(); i++) {
						minionsLeft[i].Draw(window);
					}
					for (size_t i = 0; i < minionsLeft.size(); i++) {
						// minionleft - corner / megaman
						minionsLeft[i].Update(elapsedTime);
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
						// minionright - corner / megaman
						minionsRight[i].Update(elapsedTime);
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
							spawnMinion[2] = true;
							minionsUp1.erase(minionsUp1.begin() + i);

						}
						else if (minionsUp1[i].GetCollider().CheckCollision(megamanCollider)) {
							//boolDelay[0] = true;
							//minionsUp1.erase(minionsUp1.begin() + i);
							//*ptrScore -= 20;
							//*ptrMegaHP -= 20;
							//UpdateScore(&ssScore, ptrScore);
							//UpdateScore(&ssMegaHP, ptrMegaHP);
							megaman.Hit(elapsedTime, 250);
						}
						else {
							// minionup1 - energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionsUp1[i].GetCollider().CheckCollision(energyballCollider)) {
									boolDelay[0] = true;
									minionsUp1.erase(minionsUp1.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									//*ptriceCount += 1;
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
						// minionup2 - corner / megaman
						minionsUp2[i].Update(elapsedTime);
						if (minionsUp2[i].GetPosition().x >= window.getSize().x - 70) {
							spawnMinion[3] = true;
							minionsUp2.erase(minionsUp2.begin() + i);
							//	printf("%d", spawnNum);
						}
						else if (minionsUp2[i].GetCollider().CheckCollision(megamanCollider)) {
							//boolDelay[1] = true;
							//minionsUp2.erase(minionsUp2.begin() + i);
							//*ptrScore -= 20;
							//*ptrMegaHP -= 20;
							//UpdateScore(&ssScore, ptrScore);
							//UpdateScore(&ssMegaHP, ptrMegaHP);
							megaman.Hit(elapsedTime, 250);
						}
						else {
							// minionup2 - energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionsUp2[i].GetCollider().CheckCollision(energyballCollider)) {
									boolDelay[1] = true;
									minionsUp2.erase(minionsUp2.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									//*ptriceCount += 1;
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
						//bossballs[i].FollowUpdate(elapsedTime, megaman.GetPosition());
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

					for (size_t i = 0; i < icedrop.size(); i++) {
						icedrop[i].Draw(window);
					}
					for (size_t i = 0; i < icedrop.size(); i++) {
						icedrop[i].Update(elapsedTime, window, energyballs, true, 1, false); //bottom
						if (icedrop[i].GetPosition().y >= window.getSize().y - 230.0f) {
							icedrop.erase(icedrop.begin() + i);
						}
						else if (icedrop[i].GetCollider().CheckCollision(megamanCollider)) {
							icedrop.erase(icedrop.begin() + i);
							//*ptrScore -= 50;
							*ptrMegaHP -= 10;
							megaman.iceHit = true;
							boolDelay[4] = true;
							//UpdateScore(&ssScore, ptrScore);
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (icedrop[i].GetCollider().CheckCollision(energyballCollider)) {
									icedrop.erase(icedrop.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									shootTimer++;
									*ptrScore += 10;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}


					for (size_t i = 0; i < minionUp1_balls.size(); i++) {
						minionUp1_balls[i].Draw(window);
					}
					for (size_t i = 0; i < minionUp1_balls.size(); i++) {
						//minionballs[i].Update(elapsedTime, window, energyballs, true, 1, false); //bottom
						minionUp1_balls[i].parabolaUpdtae(elapsedTime, 1);
						//bossballs[i].FollowUpdate(elapsedTime, megaman.GetPosition());
						if (minionUp1_balls[i].GetPosition().y >= window.getSize().y - 230.0f) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
						}
						else if (minionUp1_balls[i].GetCollider().CheckCollision(megamanCollider)) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
							//*ptrScore -= 50;
							*ptrMegaHP -= 10;
							//UpdateScore(&ssScore, ptrScore);
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else if (minionUp1_balls[i].GetPosition().x >= window.getSize().x - 75) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
							//spawnMinion[0] = true;
							//	spawnNum = (spawnNum + 1) % 4;
							//	printf("%d", spawnNum);
						}
						else if(minionUp1_balls[i].GetPosition().x <= 60) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
							//spawnMinion[1] = true;
							//	printf("%d", spawnNum);
						}
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionUp1_balls[i].GetCollider().CheckCollision(energyballCollider)) {
									minionUp1_balls.erase(minionUp1_balls.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									shootTimer++;
									*ptrScore += 10;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}

					for (size_t i = 0; i < minionUp2_balls.size(); i++) {
						minionUp2_balls[i].Draw(window);
					}
					for (size_t i = 0; i < minionUp2_balls.size(); i++) {
						//minionballs[i].Update(elapsedTime, window, energyballs, true, 1, false); //bottom
						minionUp2_balls[i].parabolaUpdtae(elapsedTime, -1);
						//bossballs[i].FollowUpdate(elapsedTime, megaman.GetPosition());
						if (minionUp2_balls[i].GetPosition().y >= window.getSize().y - 230.0f) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
						}
						else if (minionUp2_balls[i].GetCollider().CheckCollision(megamanCollider)) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
							//*ptrScore -= 50;
							*ptrMegaHP -= 10;
							//UpdateScore(&ssScore, ptrScore);
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else if (minionUp2_balls[i].GetPosition().x >= window.getSize().x - 75) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
							//spawnMinion[0] = true;
							//	spawnNum = (spawnNum + 1) % 4;
							//	printf("%d", spawnNum);
						}
						else if (minionUp2_balls[i].GetPosition().x <= 60) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
							//spawnMinion[1] = true;
							//	printf("%d", spawnNum);
						}
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionUp2_balls[i].GetCollider().CheckCollision(energyballCollider)) {
									minionUp2_balls.erase(minionUp2_balls.begin() + i);
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
						//int randomItems = 4;
						sf::Vector2f HP_HPCollider;
						sf::Vector2f randomSpawnItems(rand() % 621 + 50.0f, rand() % 341 + 320.0f);
						switch (randomItems) {
						case 1:
							//HMitem[0]++;
							//if (HPItem.size() > 0) {
								//for (int j = 0; j < HMitem[0]-1; j++) {
								//	HP_HPCollider = HPItem[j].GetOrigin();
									//if (abs(HP_HPCollider.x - randomSpawnItems.x) <= 40.0f|| abs(HP_HPCollider.y - randomSpawnItems.y) <= 40.0f) {
										//sf::Vector2f randomSpawnItems(rand() % 621 + 50.0f, rand() % 181 + 220.0f);
										//printf("Hello");
									//}
									//else {
									//	HPItem.push_back(Items(&HPTexture, randomSpawnItems, sf::Vector2f(40.0f, 40.0f)));
								//	}
								//}
						//	}
							//else {
								HPItem.push_back(Items(&HPTexture, randomSpawnItems, sf::Vector2f(40.0f, 40.0f)));
						//}
								break;
							//}for (size_t k = 0; j < trapItem.size(); j++) {Collider HP_TrapCollider = trapItem[k].GetCollider();
						case 2:
							//HMitem[1]++;
							//coinItem.push_back(Items(&coinTexture,sf::Vector2f(randomSpawnItems.x,70.0f), sf::Vector2f(40.0f, 40.0f)));
							for (int i = 0; i < 5; i++) {
								coinItem.push_back(Items(&coinTexture, sf::Vector2f(rand() % 615 + 35.0f, 80.0f), sf::Vector2f(40.0f, 40.0f)));
							}
							break;
						case 3:
						//	HMitem[2]++;
							trapItem.push_back(Items(&TrapTexture, randomSpawnItems, sf::Vector2f(45.0f, 35.0f)));
							break;
						//case 4:
							//	HMitem[2]++;
							//shieldItem.push_back(Items(&ShieldTexture, megaman.GetPosition(), sf::Vector2f(120.0f, 120.0f)));
						//	boolSheild = true;
						//	break;
						}
						*ptrenCount = 0;
					}

					for (size_t i = 0; i < shieldItem.size(); i++) {
						shieldItem[i].movementUpdate(megaman.GetPosition());
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
						
						else if (HPItem[i].GetCollider().CheckCollision(icebossCollider)) {
							HPItem.erase(HPItem.begin() + i);
							if (SnakeShootface) {
								snakeBall.SetPosition(sf::Vector2f(80.0f, 760.0f));
								snakeLeftBall.push_back(snakeBall);
								//*ptrSnakeShoot+=1;
							}
							else {
								snakeRightBall.push_back(snakeBall);
							}
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
						else if (trapItem[i].GetCollider().CheckCollision(icebossCollider)) {
							trapItem.erase(trapItem.begin() + i);
							if (SnakeShootface) {
								snakeLeftBall.push_back(EnergyBall(&snakeShootTexture, sf::Vector2f(80.0f, 760.0f), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed));
								//*ptrSnakeShoot+=1;
							}
							else {
								snakeRightBall.push_back(EnergyBall(&snakeShootTexture, sf::Vector2f(640.0f, 760.0f), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed));
							}
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
					for (size_t i = 0; i < shieldItem.size(); i++) {
						shieldItem[i].Draw(window);
					}
					for (size_t i = 0; i < shieldItem.size(); i++) {
							for (size_t j = 0; j < minionsUp1.size(); j++) {
								Collider minionUp1Collider = minionsUp1[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp1Collider)) {
									minionsUp1.erase(minionsUp1.begin() + j);
									spawnMinion[2] = true;
								}
							}
							for (size_t j = 0; j < minionsUp2.size(); j++) {
								Collider minionUp2Collider = minionsUp2[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp2Collider)) {
									minionsUp2.erase(minionsUp2.begin() + j);
									spawnMinion[3] = true;
								}
							}
							for (size_t j = 0; j < minionsLeft.size(); j++) {
								Collider minionLeftCollider = minionsLeft[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionLeftCollider)) {
									minionsLeft.erase(minionsLeft.begin() + j);
									spawnMinion[0] = true;
								}
							}
							for (size_t j = 0; j < minionsRight.size(); j++) {
								Collider minionRightCollider = minionsRight[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionRightCollider)) {
									minionsRight.erase(minionsRight.begin() + j);
									spawnMinion[1] = true;
								}
							}
							for (size_t j = 0; j < bossballs.size(); j++) {
								Collider bossballCollider = bossballs[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(bossballCollider)) {
									bossballs.erase(bossballs.begin() + j);
								}
							}
							for (size_t j = 0; j < icedrop.size(); j++) {
								Collider icedropCollider = icedrop[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(icedropCollider)) {
									icedrop.erase(icedrop.begin() + j);
								}
							}
							for (size_t j = 0; j < snakeLeftBall.size(); j++) {
								Collider snakeLeftBallCollider = snakeLeftBall[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(snakeLeftBallCollider)) {
									snakeLeftBall.erase(snakeLeftBall.begin() + j);
								}
							}
							for (size_t j = 0; j < snakeRightBall.size(); j++) {
								Collider snakeRightBallCollider = snakeRightBall[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(snakeRightBallCollider)) {
									snakeRightBall.erase(snakeRightBall.begin() + j);
								}
							}
							for (size_t j = 0; j < minionUp1_balls.size(); j++) {
								Collider minionUp1_ballsCollider = minionUp1_balls[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp1_ballsCollider)) {
									minionUp1_balls.erase(minionUp1_balls.begin() + j);
								}
							}
							for (size_t j = 0; j < minionUp2_balls.size(); j++) {
								Collider minionUp2_ballsCollider = minionUp2_balls[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp2_ballsCollider)) {
									minionUp2_balls.erase(minionUp2_balls.begin() + j);
								}
							}
							for (size_t j = 0; j < hitman.size(); j++) {
								Collider hitmanCollider = hitman[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(hitmanCollider)) {
									hitman.erase(hitman.begin() + j);
								}
							}
					}
					for (size_t i = 0; i < snakeLeftBall.size(); i++) {
						snakeLeftBall[i].Draw(window);
					}
					for (size_t i = 0; i < snakeLeftBall.size(); i++) {
						// minionleft - corner / megaman
						snakeLeftBall[i].Update(elapsedTime, window, energyballs, 0, 0, 1); // ขวา , ซ้าย , บน
						if (snakeLeftBall[i].GetPosition().x >= window.getSize().x - 75) {
							snakeLeftBall.erase(snakeLeftBall.begin() + i);
							//spawnMinion[0] = true;
							//	spawnNum = (spawnNum + 1) % 4;
							//	printf("%d", spawnNum);
						}
						else if (snakeLeftBall[i].GetCollider().CheckCollision(megamanCollider)) {
							snakeLeftBall.erase(snakeLeftBall.begin() + i);
							//megaman.SetPosition(megaman.GetPosition().x, megaman.GetPosition().y - 50.0f);
							boolDelay[5] = true;
							megaman.fireHit = true;
							//megaman.Hit(elapsedTime,-800.0f);
							//*ptrMegaHP -= 10;
							//UpdateScore(&ssMegaHP, ptrMegaHP);
						}

					}
					for (size_t i = 0; i < snakeRightBall.size(); i++) {
						snakeRightBall[i].Draw(window);
					}
					for (size_t i = 0; i < snakeRightBall.size(); i++) {
						// minionleft - corner / megaman
						snakeRightBall[i].Update(elapsedTime, window, energyballs, 1, 1, 1); // ขวา , ซ้าย , บน
						if (snakeRightBall[i].GetPosition().x <= 60) {
							snakeRightBall.erase(snakeRightBall.begin() + i);
							//spawnMinion[0] = true;
							//	spawnNum = (spawnNum + 1) % 4;
							//	printf("%d", spawnNum);
						}
						else if (snakeRightBall[i].GetCollider().CheckCollision(megamanCollider)) {
							snakeRightBall.erase(snakeRightBall.begin() + i);
							//megaman.SetPosition(megaman.GetPosition().x, megaman.GetPosition().y - 50.0f);
							boolDelay[5] = true;
							megaman.fireHit = true;
							//megaman.Hit(elapsedTime,-800.0f);
							//*ptrMegaHP -= 10;
							//UpdateScore(&ssMegaHP, ptrMegaHP);
						}
					}

					for (size_t i = 0; i < snake.size(); i++) {
						snake[i].Draw(window);
					}
					for (size_t i = 0; i < snake.size(); i++) {
						if (snake[i].GetCollider().CheckCollision(megamanCollider)) {
							if (snake[i].GetPosition().x < 360.0f) {
								megaman.SetPosition(snake[i].GetPosition().x+110.0f, megaman.GetPosition().y);
							}
							else {
								megaman.SetPosition(snake[i].GetPosition().x - 110.0f, megaman.GetPosition().y);
							}
						}
					}

					for (size_t i = 0; i < hitman.size(); i++) {
						hitman[i].Draw(window);
					}
					for (size_t i = 0; i < hitman.size(); i++) {
						hitman[i].FollowUpdate(elapsedTime, megaman.GetPosition());
						if (hitman[i].GetCollider().CheckCollision(megamanCollider)) {
							hitman.erase(hitman.begin() + i);
							*ptrMegaHP -= 20;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (hitman[i].GetCollider().CheckCollision(energyballCollider)) {
									hitman.erase(hitman.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									shootTimer++;
									*ptrScore += 20;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					if (megaman.GetCollider().CheckCollision(icebossCollider)) {
						megaman.Hit(elapsedTime, -500.0f);
					}

					if (*ptrMegaHP <= 0) {
						*ptrMegaHP = 0;
						UpdateScore(&ssMegaHP, ptrMegaHP);
						boolDelay[6] = true;
						megaman.dead = true;
					}
					if (*ptrBossHP <= 0) {
						*ptrBossHP = 0;
						boolDelay[7] = true;
						batboss.deadBoss = true;
						UpdateScore(&ssBossHP, ptrBossHP);
					
					}
					batboss.Draw(window);
					iceboss.Draw(window);
					megaman.Draw(window);
					window.draw(TextScore);
					window.draw(MegaHP);
					window.draw(BossHP);
					window.display();
				}

				if (Screen[4]) {
					clock.restart();
					spawnClock.restart();
					delayClock.restart();
					HuntClock.restart();
					SnakeClock.restart();
					minionClock_1.restart();
					minionClock_2.restart();

					sf::Text textScore;
					sf::Text yourScore;
					textScore.setCharacterSize(40);
					textScore.setPosition(195.0f, 235.0f);
					textScore.setFont(scoreFont);
					textScore.setFillColor(sf::Color::Red);
					textScore.setString(ssResult.str());


				
					yourScore.setCharacterSize(40);
					yourScore.setPosition(495.0f, 235.0f);
					yourScore.setFont(scoreFont);
					yourScore.setFillColor(sf::Color::Red);
					yourScore.setString(ssdisScore.str());
					UpdateScore(&ssdisScore, ptrScore);



					sf::Text yourName;
					yourName.setCharacterSize(40);
					yourName.setPosition(180.0f, 340.0f);
					yourName.setFont(scoreFont);
					yourName.setString(ssplName.str());

					Next.setFont(menuFont);
					Next.setString("EXIT");
					//menuText[0].setFillColor(sf::Color::White);
					Next.setCharacterSize(40);
					Next.setPosition(320.0f, 630.0f);

					if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						Next.setFillColor(sf::Color::Cyan);
						Next.setStyle(sf::Text::Italic);
					}
					else {
						Next.setFillColor(sf::Color::White);
						Next.setStyle(0);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						if (Next.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
								break;
							}
						}
					}

					window.clear();
					if (quickExit) {
						window.draw(Exit);
					}
					else {
						if (GameOver) {
							window.draw(Gameover);
						}
						else {
							window.draw(win);
						}
					}
					window.draw(playerText);
					window.draw(textScore);
					window.draw(yourName);
					window.draw(yourScore);
					window.draw(Next);
					window.display();
				}
		}
		return 0;
	}
	void ShowOderScore(sf::RenderWindow& window,sf::Text ScrOder[]) {

		for (int i = 0; i < 5; i++) {
			window.draw(ScrOder[i]);
		}
	}