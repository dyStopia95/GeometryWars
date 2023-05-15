#include "pch.h"
#include "Enemy.h"

namespace GWar
{
	std::vector<Bullet>* Enemy::_bulletsRef = nullptr;
	sf::Vector2f* Enemy::_playerPos = nullptr;
	sf::Vector2f* Enemy::_startPos = nullptr;
	sf::FloatRect* Enemy::_playerCollider = nullptr;
	sf::FloatRect Enemy::_playAreaCollider;

	void Enemy::updateVelocity()
	{
		_velocity += _acceleration;
	}

	void Enemy::spawningUpdate(sf::Transformable& enemyShape)
	{
		_currentScale = _spawnClock.getElapsedTime() / _spawnTime;
		enemyShape.setScale(_currentScale, _currentScale);
	}

	void Enemy::checkBounds()
	{
		if (_enemyCollider.top <= _playAreaCollider.top + 3.f && _velocity.y < 0)
			_velocity.y = 0;
		if ((_enemyCollider.top + _enemyCollider.height >= _playAreaCollider.top + _playAreaCollider.height - 3.f) && _velocity.y > 0)
			_velocity.y = 0;
		if (_enemyCollider.left <= _playAreaCollider.left + 3.f && _velocity.x < 0)
			_velocity.x = 0;
		if ((_enemyCollider.left + _enemyCollider.width >= _playAreaCollider.left + _playAreaCollider.width - 3.f) && _velocity.x > 0)
			_velocity.x = 0;
	}

	void Enemy::setExplosion()
	{
		Particle::_startPos.x = _enemyCollider.left + _enemyCollider.width / 2.f;
		Particle::_startPos.y = _enemyCollider.top - _enemyCollider.height / 2.f;
	}

	Enemy::~Enemy()
	{
	}

	bool Enemy::checkBulletCollision()
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
			else
				++checkingBullet;
		}

		return false;
	}

	bool Enemy::checkPlayerCollision()
	{
		if (_enemyCollider.intersects(*_playerCollider))
		{
			return true;
		}
		else
			return false;
	}

}