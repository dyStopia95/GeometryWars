#pragma once
#include "Player.h"
#include "HUD.h"
#include "EnemyContainer.h"

/*
	Game Engine Class
*/

namespace GWar
{
	class Game
	{
	private:
		// Window Variables
		sf::RenderWindow* _window;
		sf::VideoMode _videoMode;
		sf::Event _event;

		//World Variables
		sf::Clock WorldClock;

		sf::Clock _spawnClock;
		sf::Clock _spawnClockTest;
		sf::Time currentSpawnInterval = sf::seconds(2.f);
		sf::Time minSpawnInterval = sf::seconds(0.75f);

		int currentSpawnCountVariance = 0;
		int maxSpawnCount = 4;
		bool lowestVariance = false;
		bool spawnCountMaxed = false;
		float maxSpawnVariance = 10.f;

		sf::Clock _hordeIntervalClock;
		sf::Clock _hordeCycleClock;
		sf::Time hordeInterval = sf::seconds(30.f);
		sf::Time hordeSpawnInterval = sf::seconds(0.25f);
		EnemyTypes hordeType = EnemyTypes::CyanEnemy;
		int _currentHordeCycle = 0;
		int _hordeCycleCount = 10;

		//HUD
		HUD _HUD;
		const sf::RectangleShape& _mapCoord;
		sf::Vector2f _mouseCoord;
		sf::Transform _globalTransform;
		sf::Transform _starTransform1;
		sf::Transform _starTransform2;
		sf::Transform _starTransform3;
		sf::Transform _starTransform4;

		//Player
		Player player;
		sf::Vector2f* const playerPos;
		std::vector<Bullet>& bulletListRef;
		int _lives = 3;

		//Enemies
		EnemyContainer _allEnemies;
		float noSpawnRadius = 100;
		float spawnBoundaryOffset = 20;
		sf::Transform scaleUp;
		sf::CircleShape noSpawnBox;		
		sf::Vector2f randEnemySpawn;

		//Test Enemies
		//sf::Vertex debugPoint;
		//GreenEnemy testEnemy;
		std::vector<PurpleEnemy> testEnemyList;


		//Functions
		void initVariables();
		void initWindow();

		//Functions
		void generateEnemy();
		void spawnHorde();
		bool spawnEnemies();
		void manageSpawns();

	public:
		bool _playerAlive = true;
		const bool isRunning();


		// Constructor & Destructor
		Game();
		virtual ~Game();

		void pollEvents();
		void update();
		void render();
		void endScreen();
	};
}