#pragma once
#include "PurpleEnemy.h"
#include "CyanEnemy.h"
#include "GreenEnemy.h"
#include "Utilities.h"
#include "Explosion.h"

namespace GWar
{
	enum class EnemyTypes
	{
		PurpleEnemy,
		CyanEnemy,
		GreenEnemy,
	};

	class EnemyContainer
	{
	public:
		std::vector<PurpleEnemy> _purpleEnList;
		std::vector<CyanEnemy> _cyanEnList;
		std::vector<GreenEnemy> _greenEnList;
		std::vector<Explosion> _explosionList;

		sf::Time explosionLife = sf::seconds(1.f);

		void addEnemy();
		bool updateAllEnemies();
		//void updateList(std::vector<Enemy>&);
		void updateExplosions();
		void drawEnemies(const sf::Transform&, sf::RenderTarget*);
		void killAll();

		EnemyTypes _spawnType = EnemyTypes::PurpleEnemy;

		EnemyContainer();
		~EnemyContainer();
	};
}