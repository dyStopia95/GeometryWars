#include "pch.h"
#include "GreenEnemy.h"

namespace GWar
{
	GreenEnemy::GreenEnemy()
	{
		initEnemy();
	}

	GreenEnemy::~GreenEnemy()
	{
		//Particle::_startPos = _enemyShape.getOrigin();
	}

	void GreenEnemy::initEnemy()
	{
		_enemyShape.setSize(sf::Vector2f{ 25.f, 25.f });
		_enemyShape.setFillColor(sf::Color::Transparent);
		_enemyShape.setOrigin(12.5, 12.5);
		_enemyShape.setOutlineColor(sf::Color::Green);
		_enemyShape.setOutlineThickness(-2.f);

		_innerShape = sf::CircleShape{ 12.5, 4 };
		_innerShape.setOrigin(12.5, 12.5);
		_innerShape.setFillColor(sf::Color::Transparent);
		_innerShape.setOutlineColor(sf::Color::Green);
		_innerShape.setOutlineThickness(-2.f);

		_enemyShape.move(*_startPos);
		_innerShape.move(*_startPos);
	}

	void GreenEnemy::moveShapes()
	{
		_enemyShape.move(_velocity);
		_innerShape.move(_velocity);
	}

	void GreenEnemy::draw(sf::RenderTarget& targetWindow, sf::RenderStates globalTransform) const
	{
		targetWindow.draw(_enemyShape, globalTransform);
		targetWindow.draw(_innerShape, globalTransform);
	}

	bool GreenEnemy::checkBulletCollision()
	{
		if (_isSpawning)
			return false;

		auto checkingBullet = _bulletsRef->begin();

		while (checkingBullet != _bulletsRef->end())
		{
			if (_enemyCollider.intersects(checkingBullet->getBulletCollider()))
			{
				checkingBullet = _bulletsRef->erase(checkingBullet);
				return true;
			}

			{
				sf::Vector2f bulletDirVector = _enemyShape.getPosition() - checkingBullet->getBulletPos();

				if(getMagnitude(&bulletDirVector) < 75.f)
				{
					sf::Vector2f bulletVelocity = checkingBullet->getBulletVelocity();

					vectorNormalize(&bulletVelocity);

					float dotProduct = getDotProduct(bulletDirVector, bulletVelocity);

					/*
					dot product will be magnitude of the direction vector along bullet velocity.
					therefore component of direction vector along bullet vel is normalized bullet vel * dot product.
					parallel component + perpendicular component = direction vector.
					therefore perpendicular component = direction vector - parallel component.
					magnitude of perpendicular component is distance of min approach.
					*/

					sf::Vector2f dirParallel = bulletVelocity * dotProduct;
					sf::Vector2f dirPerpendicular = bulletDirVector - dirParallel;

					float minimumApproach = getMagnitude(&dirPerpendicular);

					if (minimumApproach < 45.0f && minimumApproach > 2.0f && dotProduct > 0)
					{
						vectorNormalize(&dirPerpendicular);
						_acceleration = dirPerpendicular * 0.25f;
						isDodging = true;
						dodgeClock.restart();
					}

				}
			}
			++checkingBullet;
		}
		return false;
	}

	void GreenEnemy::update()
	{
		if (_isSpawning)
		{
			if (_spawnClock.getElapsedTime() < _spawnTime)
			{
				spawningUpdate(_innerShape);
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
			if (isDodging)
			{
				if (dodgeClock.getElapsedTime() < dodgeDuration)
				{
					updateVelocity();
					_acceleration = -_velocity * 0.1f;
				}
				else
					isDodging = false;
			}
			else
			{
				_acceleration = *_playerPos - _enemyShape.getPosition();
				vectorNormalize(&_acceleration);
				_acceleration *= 0.25f;
				updateVelocity();
				vectorNormalize(&_velocity);
				_velocity *= _speed;
			}

			checkBounds();
			moveShapes();
		}
	}
}