#define _CRT_SECURE_NO_WARNINGS
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
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
#include"EnergyBall.h"
#include"Minion.h"
#include"BatBoss.h"
#include"MiniBoss.h"
#include"Items.h"

void UpdateScore(std::ostringstream *pscore,int *score) {
	pscore->str(" ");
	*pscore << *score;
}

void ShowOderScore(sf::RenderWindow& window, sf::Text ScrOder[]) {
	for (int i = 0; i < 5; i++) {
		window.draw(ScrOder[i]);
	}
}

struct score {
	std::string Plr;
	int Scr;
};
struct score ScBoard[5];

int main() {
	std::srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(720, 960), "O-MEGAMAN GAME", sf::Style::Close | sf::Style::Resize);
	//------BOOLEAN------
	bool Screen[5] = { true,false,false,false,false };
	bool boolDelay[8] = { false,false,true,false,false,false,false,false };
	bool spawnMinion[4] = { false,false,true,true };
	bool boolMinion[2] = { true,true };
	bool playerEnter = true;
	bool GameOver = false;
	bool quickExit = false;
	bool checkLR = true;
	bool checkUP = false;
	bool boolSheild = false;
	bool snakeBallSpawn = true;
	bool snakeHunt = true;
	bool SnakeShootLeft = true;
	//------INT------
	int enCount = 0, score = 0, megaHP = 100, bossHp = 500, minionSpeed = 80, enballSpeed = 250, iceCount = 0, bossCount = 0;
	int* ptrenCount, * ptrScore, * ptrMegaHP, * ptrBossHP, * ptrminionSpeed, * ptrEnballSpeed, * ptriceCount, * ptrbossCount;
	ptrenCount = &enCount;
	ptrScore = &score;
	ptrMegaHP = &megaHP;
	ptrBossHP = &bossHp;
	ptrminionSpeed = &minionSpeed;
	ptrEnballSpeed = &enballSpeed;
	ptriceCount = &iceCount;
	ptrbossCount = &bossCount;
	int minionDropInt[2] = { 3,3 };
	int checkBott = 0;
	int shootTimer = 1;
	int snakeShoot = 1;
	//------FLOAT & DOUBLE------
	float collectTime[8] = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
	float timeSpeed = 0.0f;
	float elapsedTime = 0.0f;
	double bossEnBallTime = 0.0f;
	double icebossTime = 0.0f;
	double despawnTime = 0.0f;
	double HuntTime = 0.0f;
	double SnakeTime = 0.0f;
	double minionTime[2] = { 0.0f,0.0f };
	//-------CHAR-----------
	char temp[256] = { " " };
	//-------BACKGROUND TEXTURE--------
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

	sf::Texture SBTexture;
	sf::Sprite SB;
	SBTexture.loadFromFile("Images/scoreboard.png");
	SB.setTexture(SBTexture);
	SB.setPosition(0.0f, 0.0f);

	sf::Texture CreditTexture;
	sf::Sprite Credit;
	CreditTexture.loadFromFile("Images/credit.png");
	Credit.setTexture(CreditTexture);
	Credit.setPosition(0.0f, 0.0f);

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
	//-------CHARACTER TEXTURE--------
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
	//-------ITEMS TEXTURE--------
	sf::Texture HPTexture;
	HPTexture.loadFromFile("Images/Heart.png");
	sf::Texture coinTexture;
	coinTexture.loadFromFile("Images/Coin.png");
	sf::Texture TrapTexture;
	TrapTexture.loadFromFile("Images/Trap2.png");
	sf::Texture ShieldTexture;
	ShieldTexture.loadFromFile("Images/Shield.png");
	//-------FONTS--------
	sf::Font menuFont;
	menuFont.loadFromFile("Fonts/Duracellio-Regular.ttf");
	sf::Text menuText[4];
	sf::Text Back;
	sf::Text Next;
	sf::String playerInput;
	sf::Text playerText;
	std::string playerName;
	std::ostringstream ssScore;
	ssScore << *ptrScore;
	std::ostringstream ssMegaHP;
	ssMegaHP << *ptrMegaHP;
	std::ostringstream ssBossHP;
	ssBossHP << *ptrBossHP;
	std::ostringstream ssResult;
	ssResult << "Your Score : ";
	std::ostringstream ssplName;
	ssplName << "Enter your name ";
	std::ostringstream ssdisScore;
	ssdisScore << *ptrScore;
	//-------MUSIC & SOUNDS--------
	sf::Music music;
	music.openFromFile("Sounds/03 - Title Screen.wav");
	music.setVolume(8);
	music.play();
	music.setLoop(true);

	sf::Sound click;
	sf::SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("Sounds/click.wav");
	click.setVolume(20);
	click.setBuffer(clickBuffer);

	sf::Sound shoot;
	sf::SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("Sounds/shoot.wav");
	shoot.setVolume(20);
	shoot.setBuffer(shootBuffer);

	sf::Sound enermyHit;
	sf::SoundBuffer enermyHitBuffer;
	enermyHitBuffer.loadFromFile("Sounds/EnemyDamage.wav");
	enermyHit.setVolume(25);
	enermyHit.setBuffer(enermyHitBuffer);

	sf::Sound megamanHit;
	sf::SoundBuffer megamanHitBuffer;
	megamanHitBuffer.loadFromFile("Sounds/MegamanDamage.wav");
	megamanHit.setVolume(25);
	megamanHit.setBuffer(megamanHitBuffer);

	sf::Sound getItem;
	sf::SoundBuffer getItemBuffer;
	getItemBuffer.loadFromFile("Sounds/itemCollect.wav");
	getItem.setVolume(25);
	getItem.setBuffer(getItemBuffer);

	sf::Sound dropSound;
	sf::SoundBuffer dropSoundBuffer;
	dropSoundBuffer.loadFromFile("Sounds/iceDrop.wav");
	dropSound.setVolume(25);
	dropSound.setBuffer(dropSoundBuffer);

	sf::Sound GameOverSound;
	sf::SoundBuffer GameOverBuffer;
	GameOverBuffer.loadFromFile("Sounds/Game Over.wav");
	GameOverSound.setVolume(30);
	GameOverSound.setBuffer(GameOverBuffer);

	sf::Sound VictorySound;
	sf::SoundBuffer VictorySoundBuffer;
	VictorySoundBuffer.loadFromFile("Sounds/Victory.wav");
	VictorySound.setVolume(30);
	VictorySound.setBuffer(VictorySoundBuffer);
	//----------FILE-----------
	std::ifstream inputFile;
	std::ofstream outputFile;
	//---------CLOCK----------
	sf::Clock clock;
	sf::Clock spawnClock;
	sf::Clock delayClock;
	sf::Clock HuntClock;
	sf::Clock SnakeClock;
	sf::Clock minionClock_1;
	sf::Clock minionClock_2;
	//--------SET VECTOR---------
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
	std::vector<class EnergyBall>   snakeballs;
	std::vector<class EnergyBall>   hitman;

	std::vector<Items> HPItem;
	std::vector<Items> coinItem;
	std::vector<Items> trapItem;
	std::vector<Items> shieldItem;
	
	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				//printf("%d,%d\n", x, y);
				break;
			}
			if (Screen[4]) {
				int ScrInt, j = 0, tempScore, order=0, tempScore2;
				std::string PlrString, tmpName, tmpName2;
				playerText.setCharacterSize(50);
				playerText.setFont(menuFont);
				playerText.setFillColor(sf::Color::Yellow);
				playerText.setPosition(185.0f, 460.0f);
				if (evnt.type == sf::Event::TextEntered) {
					if (evnt.text.unicode < 128 && playerEnter) {
						playerInput += evnt.text.unicode;
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
							playerInput = playerInput.substring(0, playerInput.getSize() - 2);
						}
						playerText.setString(playerInput);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && playerEnter && !GameOver && !quickExit) {
						playerName = playerInput;
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
				//MENU
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
					menuText[0].setCharacterSize(50);
					menuText[0].setPosition(280.0f,360.0f);

					menuText[1].setFont(menuFont);
					menuText[1].setString("ScoreBoard");
					menuText[1].setCharacterSize(50);
					menuText[1].setPosition(195.0f, 420.0f);

					menuText[2].setFont(menuFont);
					menuText[2].setString("CREDIT");
					menuText[2].setCharacterSize(50);
					menuText[2].setPosition(275.0f, 480.0f);

					menuText[3].setFont(menuFont);
					menuText[3].setString("Exit");
					menuText[3].setCharacterSize(50);
					menuText[3].setPosition(305.0f, 540.0f);	

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
								click.play();
							}
						}
						if (menuText[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
								Screen[0] = false;
								Screen[1] = true;
								click.play();

						}
						if (menuText[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							Screen[0] = false;
							Screen[2] = true;
							click.play();

						}
						if (menuText[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
							click.play();
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
				//SCOREBOARD
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
					sf::Text Scrore[5];
					std::ostringstream ssScrore[5];
					std::string PlrString;
					inputFile.open("Score_Board.txt");

					Back.setFont(menuFont);
					Back.setString("BACK");
					Back.setCharacterSize(50);
					Back.setPosition(285.0f, 770.0f);

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
								click.play();
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
						ScrOder[i].setCharacterSize(40);
						ScrOder[i].setPosition(110.0f, 280.0f + (80.0f * i));
						Scrore[i].setFont(menuFont);
						Scrore[i].setCharacterSize(40);
						Scrore[i].setFillColor(sf::Color::Magenta);
						Scrore[i].setPosition(480.0f, 280.0f + (80.0f * i));
						ssScrOder[i] << i + 1 << " ." << " " << ScBoard[i].Plr;
						ssScrore[i] << ScBoard[i].Scr;
						ScrOder[i].setString(ssScrOder[i].str());
						Scrore[i].setString(ssScrore[i].str());
					}
					window.clear();
					window.draw(SB);
					window.draw(Back);
					ShowOderScore(window, ScrOder);
					ShowOderScore(window, Scrore);
					window.display();
				}
				//CREDIT
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
								click.play();
							}
						}
					}

					window.clear();
					window.draw(Credit);
					window.draw(Back);
					window.display();
				}
				//PLAY
				if (Screen[3]) {
					elapsedTime = clock.restart().asSeconds();
					bossEnBallTime = spawnClock.getElapsedTime().asSeconds();
					delayClock.getElapsedTime().asSeconds();
					HuntClock.getElapsedTime().asSeconds();

					if (elapsedTime > 1.0f / 20.0f) {
						elapsedTime = 1.0f / 20.0f;
					}

					timeSpeed += elapsedTime;
					if (timeSpeed >= 30.0f) {
						*ptrminionSpeed += 1;
						*ptrEnballSpeed += 2;
						timeSpeed -= 30.0f;
					}

					sf::Text TextScore;
					TextScore.setCharacterSize(30);
					TextScore.setPosition(340.0f, 865.0f);
					TextScore.setFillColor(sf::Color::Yellow);
					TextScore.setFont(menuFont);
					TextScore.setString(ssScore.str());
					sf::Text MegaHP;
					MegaHP.setCharacterSize(30);
					MegaHP.setPosition(160.0f, 865.0f);
					MegaHP.setFont(menuFont);
					MegaHP.setFillColor(sf::Color::Cyan);
					MegaHP.setString(ssMegaHP.str());
					sf::Text BossHP;
					BossHP.setCharacterSize(30);
					BossHP.setPosition(595.0f, 865.0f);
					BossHP.setFont(menuFont);
					BossHP.setFillColor(sf::Color::Magenta);
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
						click.play();
					}
					if (!megaman.dead && !megaman.fireHit && !megaman.iceHit) {
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && shootTimer >= 1) {
							checkLR = false;
							checkUP = true;
							checkBott = -1;
							energyballs.push_back(energyBallB);
							shoot.play();
							shootTimer--;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && shootTimer >= 1) {
							checkLR = true;
							checkUP = false;
							energyballs.push_back(energyBallR);
							shoot.play();
							shootTimer--;
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && shootTimer >= 1) {
							checkLR = false;
							checkUP = false;
							energyballs.push_back(energyBallL);
							shoot.play();
							shootTimer--;
						}
					}
					for (size_t i = 0; i < energyballs.size(); i++) {
						// energyball - corner
						energyballs[i].Update(elapsedTime,checkUP, checkBott, checkLR); // ขวา , ซ้าย , บน
						if (energyballs[i].GetPosition().x >= window.getSize().x - 40.0f || energyballs[i].GetPosition().x <= 40.0f || energyballs[i].GetPosition().y <= 60.0f + 30.0f) {
							energyballs.erase(energyballs.begin() + i);
							shootTimer++;
						}
						// energyball - iceboss
						else if (energyballs[i].GetCollider().CheckCollision(icebossCollider)) { 
							energyballs.erase(energyballs.begin() + i);
							enermyHit.play();
							*ptrminionSpeed += 2;
							if (!iceboss.icebossHunt) {
								*ptrScore += 15;
							}
							if (!boolDelay[3]) {
								*ptriceCount += 1;
							}
							shootTimer++;
							UpdateScore(&ssScore, ptrScore);
						}
						// batboss - energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (batboss.GetCollider().CheckCollision(energyballCollider)) {
									energyballs.erase(energyballs.begin() + i);
									enermyHit.play();
									*ptrScore += 20;
									*ptrBossHP -= 20;
									*ptrminionSpeed += 2;
									*ptrEnballSpeed += 5;
									*ptrbossCount += 1;
									shootTimer++;
									UpdateScore(&ssScore, ptrScore);
									UpdateScore(&ssBossHP, ptrBossHP);
								}
							}
						}
					}
					//DELAY batBall
					if (batboss.bossShoot) {
						if ((int)bossEnBallTime % batboss.ballBossCount == 0.0f && (int)bossEnBallTime != 0) {
							batboss.spawnbossBall = true;
							batboss.bossShoot = false;
						}
					}
					else {
						batboss.ballBossCount += 5;
						batboss.bossShoot = true;
					}
					//DELAY minionUp1_balls
					if (!boolDelay[0]) {
						minionTime[0] = minionClock_1.getElapsedTime().asSeconds();
						if (boolMinion[0]) {
							if ((int)minionTime[0] % minionDropInt[0] == 0.0f && (int)minionTime[0] != 0) {
								for (size_t i = 0; i < minionsUp1.size(); i++) {
									EnergyBall bombMinion(&minionDropTexture, sf::Vector2f(minionsUp1[i].GetPosition()), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed);
									dropSound.play();
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
					//DELAY minionUp2_balls
					if (!boolDelay[1]) {
						minionTime[1] = minionClock_2.getElapsedTime().asSeconds();
						if (boolMinion[1]) {
							if ((int)minionTime[1] % minionDropInt[1] == 0.0f && (int)minionTime[1] != 0) {
								for (size_t i = 0; i < minionsUp2.size(); i++) {
									EnergyBall bombMinion(&minionDropTexture, sf::Vector2f(minionsUp2[i].GetPosition()), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed);
									dropSound.play();
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
					//DELAY minionUp1
					if (boolDelay[0]) {
						if (iceboss.icebossHunt) {
							spawnMinion[2] = false;
							boolDelay[0] = false;
						}
						else {
							collectTime[0] += elapsedTime;
							if (collectTime[0] >= 3.0f) {
								spawnMinion[2] = true;
								boolDelay[0] = false;
								collectTime[0] -= 3;
								minionDropInt[0] += 3;
							}
						}
					}
					//DELAY minionUp2
					if (boolDelay[1]) {
						if (iceboss.icebossHunt) {
							spawnMinion[3] = false;
							boolDelay[1] = false;
						}
						else {
							collectTime[1] += elapsedTime;
							if (collectTime[1] >= 3.0f) {
								spawnMinion[3] = true;
								boolDelay[1] = false;
								collectTime[1] -= 3;
							}
						}
					}
					//SPAWN SNAKE
					if (*ptriceCount == 4) {
						boolDelay[3] = true;
					}
					//USE SHEILD
					else if (*ptriceCount == 2) {
						*ptriceCount += 1;
						shieldItem.push_back(Items(&ShieldTexture,megaman.GetPosition(), sf::Vector2f(110.0f, 110.0f)));
						getItem.play();
						boolSheild = true;
					}
					//DELAY ICEBOSS HUNT
					if (boolDelay[3]) {
						if (iceboss.icebossHunt) {
							boolDelay[3] = false;
						}
						else {
							*ptriceCount = 1;
							collectTime[3] += elapsedTime;
							if (collectTime[3] >= 10.0f) {
								boolDelay[3] = false;
								collectTime[3] -= 10;
								snakeShoot = 1;
							}
							if (snakeBallSpawn) {
								if ((int)collectTime[3] % snakeShoot == 0.0f && (int)collectTime[3] != 0) {
									SnakeShootLeft = true;
									snakeBallSpawn = false;
									snake.push_back(Minion(&snakeLeftTaxture, sf::Vector2f(80.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									snakeBall.SetPosition(sf::Vector2f(80.0f, 760.0f));
									snakeballs.push_back(snakeBall);
									dropSound.play();
								}
								if ((int)snakeShoot == 10) {
								for (size_t i = 0; i < snake.size(); i++) {
										snake.erase(snake.begin() + i);
									}
								}
							}
							else {
								snakeShoot += 1;
								snakeBallSpawn = true;
							}
						}
					}
					//DELAY  IceHit
					if (boolDelay[4]) {
						if (!megaman.dead) {
							collectTime[4] += elapsedTime;
							if (collectTime[4] >= 4.0f) {
								boolDelay[4] = false;
								megaman.iceHit = false;
								collectTime[4] -= 4;
							}
						}
					}
					//DELAY  FireHit
					if (boolDelay[5]) {
						if (!megaman.dead) {
							collectTime[5] += elapsedTime;
							if (collectTime[5] >= 4.0f) {
								boolDelay[5] = false;
								megaman.fireHit = false;
								collectTime[5] -= 4;
							}
						}
					}
					//DELAY  MegamanDead
					if (boolDelay[6]) {
						collectTime[6] += elapsedTime;
						if (collectTime[6] >= 3.0f) {
							Screen[3] = false;
							Screen[4] = true;
							GameOver = true;
							music.stop();
							GameOverSound.play();
							collectTime[6] -= 3;
						}
					}
					//DELAY  BossDead
					if (boolDelay[7]) {
						collectTime[7] += elapsedTime;
						if (collectTime[7] >= 3.0f) {
							Screen[3] = false;
							Screen[4] = true;
							GameOver = false;
							music.stop();
							VictorySound.play();
							collectTime[7] -= 3;
						}
					}
					//Delay Sheild
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
					//Spawn Minions
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
					//Spawn BatBall & Movement BatBoss
					if (batboss.spawnbossBall && !batboss.deadBoss) {
						int batbossPositionX = batboss.GetPosition().x;
						int randombatbossSpawn = rand() % ((581 - batbossPositionX) - (batbossPositionX - 140)) - (batbossPositionX - 140.0f);
						batboss.Update(elapsedTime, randombatbossSpawn, batboss.deadBoss);
						EnergyBall bossBall(&bossBulletTexture, sf::Vector2f(batboss.GetPosition().x, batboss.GetPosition().y), sf::Vector2f(40.0f, 80.0f), *ptrEnballSpeed);
						bossballs.push_back(bossBall);
						if (*ptrBossHP <= 150) {
							bossBall.SetPosition(sf::Vector2f(batboss.GetPosition().x + 80.0f, batboss.GetPosition().y));
							bossballs.push_back(bossBall);
						}
						if (*ptrBossHP <= 300) {
							bossBall.SetPosition(sf::Vector2f(batboss.GetPosition().x - 80.0f, batboss.GetPosition().y));
							bossballs.push_back(bossBall);
						}
						dropSound.play();
						batboss.spawnbossBall = false;
					}
					//Spawn Hitman
					if (*ptrbossCount == 3) {
						*ptrbossCount = 0;
						int randomSpawn = rand() % 2 + 1;
						hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
						switch (randomSpawn) {
						case 1:
							hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(35.0f, rand() % 381 + 275.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
							dropSound.play();
							break;
						case 2:
							hitman.push_back(EnergyBall(&HitManTextrue, sf::Vector2f(685.0f, rand() % 381 + 275.0f), sf::Vector2f(70.0f, 60.0f), *ptrEnballSpeed));
							dropSound.play();
							break;
						}
					}
					//Spawn Items
					if (*ptrenCount == 3) {
						int randomItems = rand() % 3 + 1;
						sf::Vector2f HP_HPCollider;
						sf::Vector2f randomSpawnItems(rand() % 621 + 50.0f, rand() % 341 + 320.0f);
						switch (randomItems) {
						case 1:
							HPItem.push_back(Items(&HPTexture, randomSpawnItems, sf::Vector2f(40.0f, 40.0f)));
							break;
						case 2:
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
						if (iceboss.iceboosDrop) {
							int randomSnakeSpawn = 2;
							if (boolDelay[2]) {
								HuntTime += elapsedTime;
								if ((int)HuntTime % iceboss.spawnIceHit == 0.0f && (int)HuntTime != 0) {
									for (int i = 0; i < 2; i++) {
										EnergyBall iceBossDrop(&iceDropTexture, sf::Vector2f(rand() % 625 + 35.0f, 80.0f), sf::Vector2f(40.0f, 70.0f), *ptrEnballSpeed);
										dropSound.play();
										icedrop.push_back(iceBossDrop);
									}
									boolDelay[2] = false;
								}
							}
							else {
								iceboss.spawnIceHit += 1;
								boolDelay[2] = true;
							}
							if (snakeBallSpawn) {
								switch (randomSnakeSpawn) {
								case 1:
									snake.push_back(Minion(&snakeLeftTaxture, sf::Vector2f(80.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									SnakeShootLeft = true;
									snakeBallSpawn = false;
									break;
								case 2:
									snake.push_back(Minion(&snakeRightTaxture, sf::Vector2f(640.0f, 745.0f), sf::Vector2f(110.0f, 90.0f), 0));
									SnakeShootLeft = false;
									snakeBallSpawn = false;
									break;
								}
							}
						}
						if (iceboss.GetPosition().y >= 825.0f) {
							iceboss.SetPosition(sf::Vector2f(360.0f, 240.0f));
							iceboss.icebossHunt = false;
							spawnMinion[2] = true;
							spawnMinion[3] = true;
							iceboss.iceboosDrop = true;
							snakeBallSpawn = true;
							HuntTime = 0;
							iceboss.spawnCount = 3;
							icebossTime = 0;
							iceboss.spawnIceHit = 1;
							for (size_t i = 0; i < snake.size(); i++) {
								snake.erase(snake.begin() + i);
							}
						}
					}
					else {
						if (iceboss.booliceMove) {
							icebossTime += elapsedTime;
							if ((int)icebossTime % iceboss.spawnCount == 0.0f && (int)icebossTime != 0) {
								int icebossPositionX = iceboss.GetPosition().x;
								int randomicebossSpawn = rand() % ((581 - icebossPositionX) - (icebossPositionX - 140)) - (icebossPositionX - 140.0f);
								iceboss.booliceMove = false;
								iceboss.Update(elapsedTime, randomicebossSpawn);
							}
						}
						else {
							iceboss.spawnCount += 3;
							iceboss.booliceMove = true;
						}
						iceboss.Update(elapsedTime, 0);
					}
					
					window.clear();
					window.draw(screen);

					//EnergyBall
					for (size_t i = 0; i < energyballs.size(); i++) {
						energyballs[i].Draw(window);
					}
					//MinionsLeft Collider
					for (size_t i = 0; i < minionsLeft.size(); i++) {
						minionsLeft[i].Draw(window);
					}
					for (size_t i = 0; i < minionsLeft.size(); i++) {
						minionsLeft[i].Update(elapsedTime);
						// minionleft - corner
						if (minionsLeft[i].GetPosition().x >= window.getSize().x - 75) {
							minionsLeft.erase(minionsLeft.begin() + i);
						}
						// minionleft - megaman
						else if (minionsLeft[i].GetCollider().CheckCollision(megamanCollider)) {
							minionsLeft.erase(minionsLeft.begin() + i);
							enermyHit.play();
							megamanHit.play();
							*ptrMegaHP -= 10;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							// minionleft - energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionsLeft[i].GetCollider().CheckCollision(energyballCollider)) {
									minionsLeft.erase(minionsLeft.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									*ptrScore += 10;
									shootTimer++;
					
									*ptrminionSpeed += 1;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//MinionsRight Collider
					for (size_t i = 0; i < minionsRight.size(); i++) {
						minionsRight[i].Draw(window);
					}
					for (size_t i = 0; i < minionsRight.size(); i++) {
						// minionright - corner
						minionsRight[i].Update(elapsedTime);
						if (minionsRight[i].GetPosition().x <= 60) {
							minionsRight.erase(minionsRight.begin() + i);
						}
						// minionright - megaman
						else if (minionsRight[i].GetCollider().CheckCollision(megamanCollider)) {
							minionsRight.erase(minionsRight.begin() + i);
							enermyHit.play();
							megamanHit.play();
							*ptrMegaHP -= 10;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							// minionleft - energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionsRight[i].GetCollider().CheckCollision(energyballCollider)) {
									minionsRight.erase(minionsRight.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									*ptrScore += 10;
									shootTimer++;
									*ptrenCount += 1;
									*ptrminionSpeed += 1;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					// MinionsUp1 Collider
					for (size_t i = 0; i < minionsUp1.size(); i++) {
						minionsUp1[i].Draw(window);
					}
					for (size_t i = 0; i < minionsUp1.size(); i++) {
						minionsUp1[i].Update(elapsedTime);
						// minionup1 - corner
						if (minionsUp1[i].GetPosition().x <= 60) {
							spawnMinion[2] = true;
							minionsUp1.erase(minionsUp1.begin() + i);

						}
						//minionip1 - megaman
						else if (minionsUp1[i].GetCollider().CheckCollision(megamanCollider)) {
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
									enermyHit.play();
									*ptrScore += 10;
									shootTimer++;
									*ptrenCount += 1;
									*ptrminionSpeed += 1;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					// Minionup2 Collider
					for (size_t i = 0; i < minionsUp2.size(); i++) {
						minionsUp2[i].Draw(window);
					}
					for (size_t i = 0; i < minionsUp2.size(); i++) {
						minionsUp2[i].Update(elapsedTime);
						// minionup2 - corner 
						if (minionsUp2[i].GetPosition().x >= window.getSize().x - 70) {
							spawnMinion[3] = true;
							minionsUp2.erase(minionsUp2.begin() + i);
						}
						// minionup2 - megaman
						else if (minionsUp2[i].GetCollider().CheckCollision(megamanCollider)) {
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
									enermyHit.play();
									*ptrScore += 10;
									shootTimer++;
									*ptrenCount += 1;
									*ptrminionSpeed += 1;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//BatBoss Ball
					for (size_t i = 0; i < bossballs.size(); i++) {
						bossballs[i].Draw(window);
					}
					for (size_t i = 0; i < bossballs.size(); i++) {
						bossballs[i].Update(elapsedTime,true, 1, false); //bottom
						// Batboss Ball - corner
						if (bossballs[i].GetPosition().y >= window.getSize().y - 230.0f) {
							bossballs.erase(bossballs.begin() + i);
						}
						// Batboss Ball - megaman
						else if (bossballs[i].GetCollider().CheckCollision(megamanCollider)) {
							bossballs.erase(bossballs.begin() + i);
							megamanHit.play();
							*ptrMegaHP -= 20;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							// Batboss Ball - Energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (bossballs[i].GetCollider().CheckCollision(energyballCollider)) {
									bossballs.erase(bossballs.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									shootTimer++;
									*ptrScore += 10;
									*ptrEnballSpeed += 2;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//IceDrop
					for (size_t i = 0; i < icedrop.size(); i++) {
						icedrop[i].Draw(window);
					}
					for (size_t i = 0; i < icedrop.size(); i++) {
						icedrop[i].Update(elapsedTime,true, 1, false); //bottom
						// IceDrop - corner
						if (icedrop[i].GetPosition().y >= window.getSize().y - 230.0f) {
							icedrop.erase(icedrop.begin() + i);
						}
						//IceDrop - megaman
						else if (icedrop[i].GetCollider().CheckCollision(megamanCollider)) {
							icedrop.erase(icedrop.begin() + i);
							megamanHit.play();
							*ptrMegaHP -= 5;
							if (!megaman.fireHit) {
								boolDelay[4] = true;
								megaman.iceHit = true;
							}
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						else {
							//IceDrop - energyball
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (icedrop[i].GetCollider().CheckCollision(energyballCollider)) {
									icedrop.erase(icedrop.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									shootTimer++;
									*ptrScore += 5;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//MinionsUp1_balls
					for (size_t i = 0; i < minionUp1_balls.size(); i++) {
						minionUp1_balls[i].Draw(window);
					}
					for (size_t i = 0; i < minionUp1_balls.size(); i++) {
						minionUp1_balls[i].parabolaUpdtae(elapsedTime, 1);
						//MinionsUp1_balls - corner
						if (minionUp1_balls[i].GetPosition().y >= window.getSize().y - 230.0f) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
						}
						//MinionsUp1_balls - megaman
						else if (minionUp1_balls[i].GetCollider().CheckCollision(megamanCollider)) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
							megamanHit.play();
							*ptrMegaHP -= 5;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						//MinionsUp1_balls - cornerRight
						else if (minionUp1_balls[i].GetPosition().x >= window.getSize().x - 75) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
						}
						//MinionsUp1_balls - cornerLeft
						else if(minionUp1_balls[i].GetPosition().x <= 60) {
							minionUp1_balls.erase(minionUp1_balls.begin() + i);
						}
						//MinionsUp1_balls - Energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionUp1_balls[i].GetCollider().CheckCollision(energyballCollider)) {
									minionUp1_balls.erase(minionUp1_balls.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									shootTimer++;
									*ptrScore += 5;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//MinionsUp2_balls
					for (size_t i = 0; i < minionUp2_balls.size(); i++) {
						minionUp2_balls[i].Draw(window);
					}
					for (size_t i = 0; i < minionUp2_balls.size(); i++) {
						minionUp2_balls[i].parabolaUpdtae(elapsedTime, -1);
						//MinionsUp2_balls - corner
						if (minionUp2_balls[i].GetPosition().y >= window.getSize().y - 230.0f) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
						}
						//MinionsUp2_balls - megaman
						else if (minionUp2_balls[i].GetCollider().CheckCollision(megamanCollider)) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
							megamanHit.play();
							*ptrMegaHP -= 5;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						//MinionsUp2_balls - cornerRight
						else if (minionUp2_balls[i].GetPosition().x >= window.getSize().x - 75) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
						}
						//MinionsUp2_balls - cornerLeft
						else if (minionUp2_balls[i].GetPosition().x <= 60) {
							minionUp2_balls.erase(minionUp2_balls.begin() + i);
						}
						//MinionsUp2_balls - energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (minionUp2_balls[i].GetCollider().CheckCollision(energyballCollider)) {
									minionUp2_balls.erase(minionUp2_balls.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									shootTimer++;
									*ptrScore += 5;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					//HPitems
					for (size_t i = 0; i < HPItem.size(); i++) {
						HPItem[i].Draw(window);
					}
					for (size_t i = 0; i < HPItem.size(); i++) {
						// HPitems - megaman
						if (HPItem[i].GetCollider().CheckCollision(megamanCollider)) {
							HPItem.erase(HPItem.begin() + i);
							getItem.play();
							*ptrScore += 10;
							*ptrMegaHP += 20;
							UpdateScore(&ssScore, ptrScore);
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						// HPitems - energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (HPItem[i].GetCollider().CheckCollision(energyballCollider)) {
									HPItem.erase(HPItem.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									getItem.play();
									shootTimer++;
									*ptrScore += 10;
									*ptrMegaHP += 20;
									UpdateScore(&ssScore, ptrScore);
									UpdateScore(&ssMegaHP, ptrMegaHP);

								}
							}
						}
					}
					// Coinitems
					for (size_t i = 0; i < coinItem.size(); i++) {
						coinItem[i].Draw(window);
					}
					for (size_t i = 0; i < coinItem.size(); i++) {
						coinItem[i].Move(elapsedTime);
						// Coinitems - corner
						if (coinItem[i].GetPosition().y >= window.getSize().y - 210.0f) {
							coinItem.erase(coinItem.begin() + i);
						}
						// Coinitems - megaman
						else if (coinItem[i].GetCollider().CheckCollision(megamanCollider)) {
							coinItem.erase(coinItem.begin() + i);
							getItem.play();
							*ptrScore += 10;
							UpdateScore(&ssScore, ptrScore);
						}
						// Coinitems-energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (coinItem[i].GetCollider().CheckCollision(energyballCollider)) {
									coinItem.erase(coinItem.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									getItem.play();
									shootTimer++;
									*ptrScore += 10;
									UpdateScore(&ssScore, ptrScore);
								}
							}
						}
					}
					// Trapitems
					for (size_t i = 0; i < trapItem.size(); i++) {
						trapItem[i].Draw(window);
					}
					for (size_t i = 0; i < trapItem.size(); i++) {
						// Trapitems - megaman
						if (trapItem[i].GetCollider().CheckCollision(megamanCollider)) {
							trapItem.erase(trapItem.begin() + i);
							getItem.play();
							spawnMinion[0] = true;
							spawnMinion[1] = true;
						}
						// Trapitems - IceBoss
						else if (trapItem[i].GetCollider().CheckCollision(icebossCollider)) {
							trapItem.erase(trapItem.begin() + i);
							if (SnakeShootLeft) {
								snakeballs.push_back(EnergyBall(&snakeShootTexture, sf::Vector2f(80.0f, 760.0f), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed));
								dropSound.play();
							}
							else {
								snakeballs.push_back(EnergyBall(&snakeShootTexture, sf::Vector2f(640.0f, 760.0f), sf::Vector2f(40.0f, 40.0f), *ptrEnballSpeed));
								dropSound.play();
							}
						}
						// Trapitems - energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (trapItem[i].GetCollider().CheckCollision(energyballCollider)) {
									trapItem.erase(trapItem.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									getItem.play();
									spawnMinion[0] = true;
									spawnMinion[1] = true;
									shootTimer++;
								}
							}
						}
					}
					// ShieldItems
					for (size_t i = 0; i < shieldItem.size(); i++) {
						shieldItem[i].Draw(window);
					}
					for (size_t i = 0; i < shieldItem.size(); i++) {
						shieldItem[i].SetPosition(megaman.GetPosition());
							// ShieldItems - minionsUp1
							for (size_t j = 0; j < minionsUp1.size(); j++) {
								Collider minionUp1Collider = minionsUp1[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp1Collider)) {
									minionsUp1.erase(minionsUp1.begin() + j);
									enermyHit.play();
									spawnMinion[2] = true;
								}
							}
							// ShieldItems - minionsUp2
							for (size_t j = 0; j < minionsUp2.size(); j++) {
								Collider minionUp2Collider = minionsUp2[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp2Collider)) {
									minionsUp2.erase(minionsUp2.begin() + j);
									enermyHit.play();
									spawnMinion[3] = true;
								}
							}
							// ShieldItems - minionsLeft
							for (size_t j = 0; j < minionsLeft.size(); j++) {
								Collider minionLeftCollider = minionsLeft[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionLeftCollider)) {
									minionsLeft.erase(minionsLeft.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - minionsRight
							for (size_t j = 0; j < minionsRight.size(); j++) {
								Collider minionRightCollider = minionsRight[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionRightCollider)) {
									minionsRight.erase(minionsRight.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - BatBall
							for (size_t j = 0; j < bossballs.size(); j++) {
								Collider bossballCollider = bossballs[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(bossballCollider)) {
									bossballs.erase(bossballs.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - IceDrop
							for (size_t j = 0; j < icedrop.size(); j++) {
								Collider icedropCollider = icedrop[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(icedropCollider)) {
									icedrop.erase(icedrop.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - SnakeBalls
							for (size_t j = 0; j < snakeballs.size(); j++) {
								Collider snakeBallCollider = snakeballs[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(snakeBallCollider)) {
									snakeballs.erase(snakeballs.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - minionsUp1_balls
							for (size_t j = 0; j < minionUp1_balls.size(); j++) {
								Collider minionUp1_ballsCollider = minionUp1_balls[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp1_ballsCollider)) {
									minionUp1_balls.erase(minionUp1_balls.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - minionsUp2_balls
							for (size_t j = 0; j < minionUp2_balls.size(); j++) {
								Collider minionUp2_ballsCollider = minionUp2_balls[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(minionUp2_ballsCollider)) {
									minionUp2_balls.erase(minionUp2_balls.begin() + j);
									enermyHit.play();
								}
							}
							// ShieldItems - Hitman
							for (size_t j = 0; j < hitman.size(); j++) {
								Collider hitmanCollider = hitman[j].GetCollider();
								if (shieldItem[i].GetCollider().CheckCollision(hitmanCollider)) {
									hitman.erase(hitman.begin() + j);
									enermyHit.play();
								}
							}
					}

					//SnakeBalls
					for (size_t i = 0; i < snakeballs.size(); i++) {
						snakeballs[i].Draw(window);
					}
					for (size_t i = 0; i < snakeballs.size(); i++) {
						if (SnakeShootLeft) {
							snakeballs[i].Update(elapsedTime, 0, 0, 1); // ขวา , ขวา , บน
						}
						else {
							snakeballs[i].Update(elapsedTime, 1, 1, 1); // ขวา , ขวา , บน
						}
						if (SnakeShootLeft) {
							//SnakeBallsLeft - corner
							if (snakeballs[i].GetPosition().x >= window.getSize().x - 75) {
								snakeballs.erase(snakeballs.begin() + i);
							}
							//SnakeBallsLeft - corner
							else if (snakeballs[i].GetCollider().CheckCollision(megamanCollider)) {
								snakeballs.erase(snakeballs.begin() + i);
								megamanHit.play();
								if (!megaman.iceHit) {
									boolDelay[5] = true;
									megaman.fireHit = true;
								}
								*ptrMegaHP -= 5;
								UpdateScore(&ssMegaHP, ptrMegaHP);
							}
						}
						else {
							//SnakeBallsRight - corner
							if (snakeballs[i].GetPosition().x <= 60) {
								snakeballs.erase(snakeballs.begin() + i);
							}
							//SnakeBallsRight - megaman
							else if (snakeballs[i].GetCollider().CheckCollision(megamanCollider)) {
								snakeballs.erase(snakeballs.begin() + i);
								megamanHit.play();
								if (!megaman.iceHit) {
									boolDelay[5] = true;
									megaman.fireHit = true;
								}
								*ptrMegaHP -= 5;
								UpdateScore(&ssMegaHP, ptrMegaHP);
							}
						}
					}
					//Snake
					for (size_t i = 0; i < snake.size(); i++) {
						snake[i].Draw(window);
					}
					for (size_t i = 0; i < snake.size(); i++) {
						//Snake - megaman
						if (snake[i].GetCollider().CheckCollision(megamanCollider)) {
							if (snake[i].GetPosition().x < 360.0f) {
								megaman.SetPosition(snake[i].GetPosition().x+110.0f, megaman.GetPosition().y);
							}
							else {
								megaman.SetPosition(snake[i].GetPosition().x - 110.0f, megaman.GetPosition().y);
							}
						}
					}
					//Hitman
					for (size_t i = 0; i < hitman.size(); i++) {
						hitman[i].Draw(window);
					}
					for (size_t i = 0; i < hitman.size(); i++) {
						hitman[i].FollowUpdate(elapsedTime, megaman.GetPosition());
						//Hitman - megaman
						if (hitman[i].GetCollider().CheckCollision(megamanCollider)) {
							hitman.erase(hitman.begin() + i);
							megamanHit.play();
							*ptrMegaHP -= 10;
							UpdateScore(&ssMegaHP, ptrMegaHP);
						}
						//Hitman - energyball
						else {
							for (size_t j = 0; j < energyballs.size(); j++) {
								Collider energyballCollider = energyballs[j].GetCollider();
								if (hitman[i].GetCollider().CheckCollision(energyballCollider)) {
									hitman.erase(hitman.begin() + i);
									energyballs.erase(energyballs.begin() + j);
									enermyHit.play();
									*ptrminionSpeed += 2;
									shootTimer++;
									*ptrScore += 10;
									*ptrEnballSpeed += 5;
									*ptrenCount += 1;
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
						boolDelay[6] = true;
						megaman.dead = true;
						UpdateScore(&ssMegaHP, ptrMegaHP);
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
				//END
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
					textScore.setPosition(165.0f, 235.0f);
					textScore.setFont(menuFont);
					textScore.setFillColor(sf::Color::Red);
					textScore.setString(ssResult.str());

					yourScore.setCharacterSize(40);
					yourScore.setPosition(495.0f, 235.0f);
					yourScore.setFont(menuFont);
					yourScore.setFillColor(sf::Color::Red);
					yourScore.setString(ssdisScore.str());
					UpdateScore(&ssdisScore, ptrScore);

					sf::Text yourName;
					yourName.setCharacterSize(40);
					yourName.setPosition(165.0f, 390.0f);
					yourName.setFont(menuFont);
					yourName.setString(ssplName.str());

					Next.setFont(menuFont);
					Next.setString("EXIT");
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
								click.play();
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