#include "Game.h"


//private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space War", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}


void Game::initMenu()
{
	this->bg.setSize(sf::Vector2f(800.f, 600.f));
	this->bg.setPosition(0, 0);
	this->bg.setFillColor(sf::Color::Black);
	//Load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	this->gameOverPointsText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverPointsText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverPointsText.getGlobalBounds().height / 2.f - 100.f);
	this->gameOverPointsText.setFont(this->font);
	this->gameOverPointsText.setCharacterSize(50);
	this->gameOverPointsText.setFillColor(sf::Color::White);

	this->exitButton.setPosition(50, 400);
	this->exitButton.setFont(this->font);
	this->exitButton.setCharacterSize(50);
	this->exitButton.setFillColor(sf::Color::White);
	this->exitButton.setString("EXIT");

	this->name.setPosition(450, 500);
	this->name.setFont(this->font);
	this->name.setCharacterSize(20);
	this->name.setFillColor(sf::Color::White);
	this->name.setString("Game develoed by : Surapat Wongprapaipak 63011018");
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initSound()
{
	if (!this->soundEffect.loadFromFile("Sounds/soundEffect1.WAV"))
		std::cout << "ERROR::GAME::Could not load the sound" << "\n";
	this->shootEffect.setBuffer(this->soundEffect);
}

void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	
	//this->gameOverPointsText.setString("Your score : ");
	//this->gameOverPointsText.setString(std::to_string(points));
	

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;

}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initMenu();
	this->initSound();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
}
Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete Bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvent();

		if (this->player->getHp() > 0)
			this->update();
		this->render();
	}
}

void Game::updatePollEvent()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::updateMenu()
{
	std::stringstream ss2;

	ss2 << "Your score : " << this->points;

	this->gameOverPointsText.setString(ss2.str());
	/*if (this->startButton.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
	{
		this->startButton.setFillColor(sf::Color::Red);
		this->startButton.setStyle(sf::Text::Underlined);
	}*/

	if (this->exitButton.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
	{
		this->exitButton.setFillColor(sf::Color::Red);
		this->exitButton.setStyle(sf::Text::Underlined);
	}
	else
	{
		this->startButton.setFillColor(sf::Color::White);


		this->exitButton.setFillColor(sf::Color::White);

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		/*if (this->startButton.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
		{
			Game Game();
			this->update();
			this->render();
		}*/

		if (this->exitButton.getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y))
		{
			this->window->close();
		}
	}
}

void Game::updateSound1()
{

}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		this->player->move(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->canAttack())
	{
		this->shootEffect.play();
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 2.f, this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points : " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	//Right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x-this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//Buttom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of the screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);


		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 5.f;
	}
	
	//Update
	unsigned counter = 0;

	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of the screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);


		}
		//Enemy player collision
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->shootEffect.play();
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

		}

		++counter;
	}

}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points+=this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin()+i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				this->shootEffect.play();

				enemy_deleted = true;
			}

		}
	}
}

void Game::update()
{
	this->updateMenu();

	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderMenu()
{
	this->window->draw(this->bg);
	this->window->draw(this->gameOverPointsText);
	//this->window->draw(this->startButton);
	this->window->draw(this->exitButton);
	this->window->draw(this->name);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();


	//Draw world
	this->renderWorld();

	//Draw  all the stuff
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{
		this->shootEffect.play();
		this->window->draw(this->gameOverText);
		//this->window->draw(this->gameOverPointsText);
		this->initMenu();
		this->updateMenu();
		this->renderMenu();
	}

	//this->renderMenu();
	this->window->display();
}
