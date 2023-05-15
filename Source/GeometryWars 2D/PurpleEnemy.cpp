#include "pch.h"
#include "PurpleEnemy.h"

namespace GWar
{
	PurpleEnemy::PurpleEnemy()
	{
		initEnemy();
		_speed = 0.25f;

		float tempX = static_cast<float>(std::rand() % 100);
		if (tempX > 50.f)
			tempX -= 100.f;
		float tempY = static_cast<float>(std::rand() % 100);
		if (tempY > 50.f)
			tempY -= 100.f;

		_velocity = sf::Vector2f{ tempX,tempY };
		vectorNormalize(&_velocity);
		_velocity *= _speed;

		currentZ = 1;
		_acceleration = getNormalVector(_velocity, currentZ)/200.f;
	}

	PurpleEnemy::~PurpleEnemy()
	{
		//Particle::_startPos = _enemyShape.getOrigin();
	}

	void PurpleEnemy::update()
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

			if (inflectionClock.getElapsedTime() > inflectionTime)
			{
				int temp = std::rand() % 2;
				if (temp != 1)
					currentZ = -1;
				else
					currentZ = 1;

				inflectionClock.restart();
			}

			_acceleration = getNormalVector(_velocity, currentZ) / 200.f; //Provide centrifugal force to maintain circular trajectory.
			updateVelocity();

			vectorNormalize(&_velocity);
			_velocity *= _speed;

			checkBounds();
			_enemyShape.move(_velocity);
		}
	}

	void PurpleEnemy::initEnemy()
	{
		_enemyShape = sf::CircleShape{ 15 ,3 };
		_enemyShape.setOrigin(15.f, 15.f);
		_enemyShape.move(*_startPos);
		_enemyShape.setOutlineColor(sf::Color(132, 3, 252, 255));
		_enemyShape.setOutlineThickness(-2.f);
		_enemyShape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void PurpleEnemy::draw(sf::RenderTarget& targetWindow, sf::RenderStates globalTransform) const
	{
		targetWindow.draw(_enemyShape, globalTransform);
	}


}

		/*float tempX = static_cast<float>(std::rand() % 100);
		if (tempX > 50.f)
			tempX -= 100.f;
		float tempY = static_cast<float>(std::rand() % 100);
		if (tempY > 50.f)
			tempY -= 100.f;

		_acceleration.x = tempX/4;
		_acceleration.y = tempY/4;
		updateVelocity();*/