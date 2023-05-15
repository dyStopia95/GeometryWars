#include "pch.h"
#include "Game.h"

//Private Functions

using std::endl;

namespace GWar
{

	void Game::initVariables()
	{
		_window = nullptr;
	}

	void Game::initWindow()
	{
		_videoMode.width = 800;
		_videoMode.height = 600;
		_window = new sf::RenderWindow(_videoMode, "GeometryWars", sf::Style::Titlebar | sf::Style::Close);
		_window->setFramerateLimit(144);
	}

	const bool Game::isRunning()
	{
		return _window->isOpen();
	}

	//Constructor & Destructor
	Game::Game() : 
		_HUD{ },
		_mapCoord{ _HUD.getPlayArea() },
		player{ _HUD.getPlayArea() },
		bulletListRef{ player.getBulletList() },
		playerPos{ player.getPlayerPos() }					//Refactor Center Player and HUD to constructors.
	{
		initVariables();
		initWindow();
		_HUD.centerHUD(_window);
		player.centerPlayer(_window);

		Enemy::_bulletsRef = &bulletListRef;
		Enemy::_playerPos = player.getPlayerPos();
		Enemy::_playerCollider = player.getPlayerCollider();
		Enemy::_startPos = &randEnemySpawn;
		Enemy::_playAreaCollider = _HUD.getPlayArea().getGlobalBounds();
	}

	Game::~Game()
	{
		delete _window;
	}

	//Public Functions

	void Game::pollEvents()
	{
		while (_window->pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
				_window->close();
				break;
			case sf::Event::KeyPressed:
				if (_event.key.code == sf::Keyboard::Escape)
					_window->close();
				break;
			default:
				break;
			}
		}
	}

	void Game::manageSpawns()
	{
		float spawnVariance;

		/*int randSpawnWeight = std::rand() % 100;
		randSpawnWeight;*/

		/*
		Spawns occur at a minimum spawn interval + randomized value whose range reduces over time.
		Multiple enemies may also spawn based on time. As time increases, possible number of enemy spawned per spawn event increases.
		*/

		if (_spawnClock.getElapsedTime() > currentSpawnInterval)
		{
			if(!lowestVariance)
			{
				maxSpawnVariance = 1 / (WorldClock.getElapsedTime().asSeconds() / 750 + 0.2f); //Reduce variance amount as time increases
				cout << maxSpawnVariance << endl;
				spawnVariance = static_cast<float>(std::rand() % static_cast<int> (maxSpawnVariance));

				if (maxSpawnVariance < 2)
				{
					maxSpawnVariance = 0;
					lowestVariance = true;
				}
			}
			else
			{
				spawnVariance = static_cast<float>(std::rand() % 10);
				spawnVariance /= 10;
			}

			currentSpawnInterval = minSpawnInterval + sf::seconds(spawnVariance);

			if (!spawnCountMaxed)
			{
				currentSpawnCountVariance = 5 - static_cast<int>(maxSpawnVariance); //Increase max enemies spawned per spawn event with time
				if (maxSpawnVariance == 0)
				{
					currentSpawnCountVariance = maxSpawnCount;
					spawnCountMaxed = true;
				}
			}
			
			int currentSpawnCount = 1 + std::rand() % currentSpawnCountVariance;
			cout << currentSpawnCount << endl;

			for(int i = 0; i < currentSpawnCount; ++i)
			{
				int randType = std::rand() % 3;

				switch (randType)
				{
				case 0:
					_allEnemies._spawnType = EnemyTypes::PurpleEnemy;
					break;
				case 1:
					_allEnemies._spawnType = EnemyTypes::CyanEnemy;
					break;
				case 2:
					_allEnemies._spawnType = EnemyTypes::GreenEnemy;
					break;
				default:
					break;
				}

				while (!spawnEnemies());
			}

			_spawnClock.restart();
		}
	}

	void Game::generateEnemy()
	{
		//testEnemyList.emplace_back(PurpleEnemy{});
	}

	void Game::spawnHorde()
	{
		_allEnemies._spawnType = hordeType;

		if(_hordeCycleClock.getElapsedTime() > hordeSpawnInterval) //Delay spawn of a wave by spawnInterval
		{
			if (_currentHordeCycle < _hordeCycleCount) 
			{
				float tempX, tempY;
				tempX = _mapCoord.getGlobalBounds().left + spawnBoundaryOffset;
				tempY = _mapCoord.getGlobalBounds().top + spawnBoundaryOffset;
				randEnemySpawn = sf::Vector2{ tempX, tempY }; //Set spawn locations at four corners of the map
				_allEnemies.addEnemy();

				tempX = tempX + _mapCoord.getGlobalBounds().width - 2 * spawnBoundaryOffset;
				randEnemySpawn = sf::Vector2{ tempX, tempY };
				_allEnemies.addEnemy();

				tempY = tempY + _mapCoord.getGlobalBounds().height - 2 * spawnBoundaryOffset;
				randEnemySpawn = sf::Vector2{ tempX, tempY };
				_allEnemies.addEnemy();

				tempX = _mapCoord.getGlobalBounds().left;
				randEnemySpawn = sf::Vector2{ tempX, tempY };
				_allEnemies.addEnemy();

				++_currentHordeCycle;
				_hordeCycleClock.restart();
				_spawnClock.restart(); //Disable default spawns till horde has finished
			}
			else
			{
				int hordeRandomize = std::rand() % 2;

				switch (hordeRandomize)
				{
				case 0:
					hordeType = EnemyTypes::CyanEnemy;
					break;
				case 1:
					hordeType = EnemyTypes::GreenEnemy;
					break;
				default:
					break;
				}

				_hordeIntervalClock.restart();
				_currentHordeCycle = 0;
			}
		}
	}

	bool Game::spawnEnemies()
	{
		float tempX, tempY;

		noSpawnBox = player.getPlayerShapeCopy();
		noSpawnBox.setScale(20, 20);

		tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapCoord.getGlobalBounds().width - spawnBoundaryOffset))) + _mapCoord.getGlobalBounds().left;
		tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapCoord.getGlobalBounds().height - spawnBoundaryOffset))) + _mapCoord.getGlobalBounds().top;
		
		if (noSpawnBox.getGlobalBounds().contains(tempX, tempY)) //Check if randomized position is within some rectangular area of the player re-randomize if yes
			return false;
		else
		{
			randEnemySpawn = sf::Vector2{ tempX, tempY }; //Set position vector data member that is accessible by all enemies, and used when instantiating an Enemy obj
			_allEnemies.addEnemy();
			//generateEnemy();

			return true;
		}
	}

	void Game::update()
	{
		//Update mouse position
		_mouseCoord = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window));
		
		//Update player **needs mouse position
		player.updatePlayer(&_mouseCoord);

		//Get player movement and shift map by negative of that movement
		if(*player.getPlayerVelocity() != sf::Vector2f(0.f,0.f))
		{
			_globalTransform.translate( - *player.getPlayerVelocity() / 2.f); //Set the transfrom to shift in map. Simulates camera following behind the player at half speed

			_starTransform1.translate(-*player.getPlayerVelocity() / 8.f); //Star transforms at varying speeds less than object speeds for parallax effect
			_starTransform2.translate(-*player.getPlayerVelocity() / 6.f);
			_starTransform3.translate(-*player.getPlayerVelocity() / 3.f);
			_starTransform4.translate(-*player.getPlayerVelocity() / 10.f);
		}
		else
		{
			_globalTransform.translate(0.f, 0.f);
			_starTransform1.translate(0.f, 0.f);
			_starTransform2.translate(0.f, 0.f);
			_starTransform3.translate(0.f, 0.f);
			_starTransform4.translate(0.f, 0.f);
		}

		

		//Spawn enemies
		if (_hordeIntervalClock.getElapsedTime() > hordeInterval)
		{
			spawnHorde();
		}

		manageSpawns();

		//Update Enemy container

		_allEnemies.updateExplosions();

		if (!_allEnemies.updateAllEnemies())
		{
			_allEnemies.killAll();
			_lives -= 1;
			cout << _lives << endl;
		}

		if (_lives < 1)
			_playerAlive = false;

		pollEvents();
	}

	void Game::render()
	{
		_window->clear(sf::Color::Black);

		//Draw objects
		_HUD.drawHUD(_window, &_globalTransform, &_starTransform1, &_starTransform2, &_starTransform3, &_starTransform4);
		_window->draw(player, _globalTransform);

		_allEnemies.drawEnemies(_globalTransform, _window);

		//Swap buffer
		_window->display();
	}

	void Game::endScreen()
	{
		sf::Text endText;
		sf::Font font;
		if (!font.loadFromFile("Content/arial.ttf"))
			cout << "error loading!\n";
		endText.setFont(font);
		endText.setCharacterSize(50);
		endText.setString("Skill Issue??");
		endText.setFillColor(sf::Color::Red);
		endText.setStyle(sf::Text::Bold);
		endText.setOrigin(endText.getGlobalBounds().width/2, endText.getGlobalBounds().height/2);
		sf::Vector2f windowCenter = { static_cast<float>(_window->getSize().x) / 2, static_cast<float>(_window->getSize().y) / 2 };
		endText.setPosition(windowCenter);

		_window->draw(endText);
		_window->display();
	}
}

//Draw test list objects
//for (auto& tE : testEnemyList)
//{
//	_window->draw(tE, _globalTransform);
//}

//Draw debug objects
		//_window->draw(noSpawnBox, _globalTransform);
		//_window->draw(&debugPoint, 1, sf::Points, _globalTransform);
		//auto& tSE = testEnemy;
		//->draw(tSE, _globalTransform);

//Update test objects
		/*auto& tSE = testEnemy;
		tSE.update();
		tSE.checkBulletCollision();*/

		//Update test object list
		/*auto tE = testEnemyList.begin();
		while (tE != testEnemyList.end())
		{
			if (tE->checkBulletCollision())
			{
				tE = testEnemyList.erase(tE);
			}
			else
			{
				tE->update();
				if (tE->checkPlayerCollision())
					cout << "Dieded!\n";
				++tE;
			}
		}*/

//enemy.updateEnemy();
//_window->draw(enemy, _globalTransform);

/*
		tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapCoord.getGlobalBounds().width) - 2 * noSpawnRadius - spawnBoundaryOffset));
		if (tempX < (playerPos->x - noSpawnRadius - _mapCoord.getGlobalBounds().left))
			tempX += _mapCoord.getGlobalBounds().left + 10.f;
		else
			tempX += playerPos->x + noSpawnRadius;

		tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapCoord.getGlobalBounds().height) - 2 * noSpawnRadius - spawnBoundaryOffset));
		if (tempY < playerPos->y - noSpawnRadius - _mapCoord.getGlobalBounds().top)
			tempY += _mapCoord.getGlobalBounds().top + 10.f;
		else
			tempY += playerPos->y + noSpawnRadius;*/