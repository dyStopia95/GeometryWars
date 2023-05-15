#include "pch.h"
#include "Enemies.h"
#include "Utilities.h"

namespace GWar
{
	std::vector<Bullet>* Enemies::_bulletsRef = nullptr;
	sf::Vector2f* Enemies::_playerPos = nullptr;
	sf::FloatRect* Enemies::_playerCollider = nullptr;
	sf::Vector2f* Enemies::_startPos = nullptr;

	void Enemies::initEnemy()
	{
		_enemyShape.setSize(sf::Vector2f(20.f, 20.f));
		_enemyShape.setOrigin(10.f,10.f);
		_enemyShape.move(*_startPos);
		_enemyShape.setRotation(45.f);
		_enemyShape.setOutlineColor(sf::Color::Cyan);
		_enemyShape.setOutlineThickness(-2.f);
		_enemyShape.setFillColor(sf::Color(0, 0, 0, 0));
	}

	void Enemies::draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const
	{
		targetWindow.draw(_enemyShape, states);
	}

	Enemies::Enemies()
	{
		initEnemy();
	}

	Enemies::~Enemies()
	{

	}
	
	bool Enemies::updateAndCheckAliveEnemy()
	{		
		//Spawning update
		if (_isSpawning == true)
		{
			if (_spawnClock.getElapsedTime() < _spawnTime)
			{
				_currentScale = _spawnClock.getElapsedTime() / _spawnTime;
				_enemyShape.setScale(_currentScale, _currentScale);
				return true;
			}
			else
			{
				_isSpawning = false;
				_enemyShape.setScale(1, 1);
			}
		}

		//Update enemy collider
		_tempCollider = _enemyShape.getGlobalBounds();

		//Check bullet collision
		auto B = _bulletsRef->begin();

		while (B != _bulletsRef->end())
		{
			if (_tempCollider.intersects(B->getBulletCollider()))
			{
				//std::cout << "Enemy hit!\n";
				B = _bulletsRef->erase(B);
				return false;
			}
			else
			{
				++B;
			}
		}

		//Check Player collision
		if (_tempCollider.intersects(*_playerCollider))
		{
			std::cout << "Dieded!\n";
		}

		//Move enemy
		_velocity = *_playerPos - _enemyShape.getPosition();
		vectorNormalize(&_velocity);
		_velocity = _velocity * _speed;
		_enemyShape.move(_velocity);
		return true;
	}
}