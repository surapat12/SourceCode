#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include"Player.h"
#include<map>
#include"Bullet.h"
#include"Enemy.h"
#include<sstream>
#include<string>

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map <std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//Menu
	sf::RectangleShape bg;
	sf::Text startButton;
	sf::Text exitButton;

	sf::Text name;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;
	sf::Text gameOverPointsText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Sounds
	sf::SoundBuffer soundEffect;
	sf::Sound shootEffect;
	

	//Player
	Player* player;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	sf::RectangleShape heal;
	sf::RectangleShape bomb;

	
	//private functions
	void initWindow();
	void initMenu();
	void initTextures();
	void initSound();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();

public:
	Game();
	~Game();
	
	//Functions
	void run();

	void updatePollEvent();
	void updateMenu();
	void updateSound1();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderMenu();
	void renderGUI();
	void renderWorld();
	void render();

};

