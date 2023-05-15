#include "pch.h"
#include "CyanEnemy.h"

namespace GWar
{
	CyanEnemy::CyanEnemy()
	{
		initEnemy();
	}

	CyanEnemy::~CyanEnemy()
	{
		//Particle::_startPos = _enemyShape.getOrigin();
	}

	void CyanEnemy::initEnemy()
	{
		_enemyShape = sf::CircleShape{ 15 ,4 };
		_enemyShape.setOrigin(15.f, 15.f);
		_enemyShape.move(*_startPos);
		_enemyShape.setOutlineColor(sf::Color::Cyan);
		_enemyShape.setOutlineThickness(-2.f);
		_enemyShape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void CyanEnemy::draw(sf::RenderTarget& targetWindow, sf::RenderStates globalTransform) const
	{
		targetWindow.draw(_enemyShape, globalTransform);
	}

	void CyanEnemy::update()
	{
		if (_isSpawning)
		{
			if (_spawnClock.getElapsedTime() < _spawnTime)
			{
				spawningUpdate(_enemyShape);
			}
			else
			{
				_isSpawning = false;
				_enemyShape.setScale(1, 1);
			}
		}

		else
		{
			_enemyCollider = _enemyShape.getGlobalBounds();

			_velocity = *_playerPos - _enemyShape.getPosition();
			vectorNormalize(&_velocity);
			_velocity *= _speed;

			checkBounds();
			_enemyShape.move(_velocity);
		}
	}

}