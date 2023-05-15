#include "pch.h"
#include "EnemyContainer.h"

namespace GWar
{
	void EnemyContainer::addEnemy()
	{

		switch (_spawnType)
		{
		case GWar::EnemyTypes::PurpleEnemy:
			_purpleEnList.emplace_back(PurpleEnemy{});
			cout << "spawned Purple!\n";
			break;
		case GWar::EnemyTypes::CyanEnemy:
			_cyanEnList.emplace_back(CyanEnemy{});
			cout << "spawned Cyan!\n";
			break;
		case GWar::EnemyTypes::GreenEnemy:
			_greenEnList.emplace_back(GreenEnemy{});
			cout << "spawned Green!\n";
			break;
		default:
			break;
		}
	}

	bool EnemyContainer::updateAllEnemies()
	{
		{
			auto currentEnemy = _purpleEnList.begin();
			while (currentEnemy != _purpleEnList.end())
			{
				if (currentEnemy->checkBulletCollision())
				{
					currentEnemy->setExplosion();
					_explosionList.emplace_back(Explosion{});
					currentEnemy = _purpleEnList.erase(currentEnemy);
				}
				else
				{
					currentEnemy->update();
					if (currentEnemy->checkPlayerCollision())
					{
						cout << "Dieded!\n";
						pause(1.f);
						return false;
					}
					++currentEnemy;
				}
			}
		}

		{
			auto currentEnemy = _cyanEnList.begin();
			while (currentEnemy != _cyanEnList.end())
			{
				if (currentEnemy->checkBulletCollision())
				{
					currentEnemy->setExplosion();
					_explosionList.emplace_back(Explosion{});
					currentEnemy = _cyanEnList.erase(currentEnemy);
				}
				else
				{
					currentEnemy->update();
					if (currentEnemy->checkPlayerCollision())
					{
						cout << "Dieded!\n";
						pause(1.f);
						return false;
					}

					++currentEnemy;
				}
			}
		}

		{
			auto currentEnemy = _greenEnList.begin();
			while (currentEnemy != _greenEnList.end())
			{
				if (currentEnemy->checkBulletCollision())
				{
					currentEnemy->setExplosion();
					_explosionList.emplace_back(Explosion{});
					currentEnemy = _greenEnList.erase(currentEnemy);
				}
				else
				{
					currentEnemy->update();
					if (currentEnemy->checkPlayerCollision())
					{
						cout << "Dieded!\n";
						pause(1.f);
						return false;
					}

					++currentEnemy;
				}
			}
		}
		return true;
	}

	void EnemyContainer::updateExplosions()
	{
		auto explosion = _explosionList.begin();
		while (explosion != _explosionList.end())
		{
			explosion->update();
			if (explosion->_explosionClock.getElapsedTime() > explosionLife)
			{
				explosion = _explosionList.erase(explosion);
			}
			else
				++explosion;
		}
	}

	void EnemyContainer::drawEnemies(const sf::Transform& globalTransform, sf::RenderTarget* window)
	{
		for (auto& currentEnemy : _purpleEnList)
			window->draw(currentEnemy, globalTransform);
		for (auto& currentEnemy : _cyanEnList)
			window->draw(currentEnemy, globalTransform);
		for (auto& currentEnemy : _greenEnList)
			window->draw(currentEnemy, globalTransform);
		for (auto& explosion : _explosionList)
			window->draw(explosion, globalTransform);
	}

	void EnemyContainer::killAll()
	{
		_purpleEnList.clear();
		_cyanEnList.clear();
		_greenEnList.clear();
	}


	EnemyContainer::EnemyContainer() : _spawnType{EnemyTypes::PurpleEnemy}
	{
		_purpleEnList.reserve(1000);
		_cyanEnList.reserve(1000);
		_greenEnList.reserve(1000);
	}

	EnemyContainer::~EnemyContainer()
	{
	}

}

	/*void EnemyContainer::updateList(std::vector<Enemy>& currentList)
	{
		
	}*/