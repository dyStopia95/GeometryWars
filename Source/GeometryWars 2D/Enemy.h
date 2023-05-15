#pragma once
#include "Bullet.h"
#include "Utilities.h"
#include "Explosion.h"

namespace GWar
{
	class Enemy : public sf::Drawable
	{
	private:
		
	protected:
		bool _isSpawning = true;
		float _currentScale = 0.f;
		float _speed = 1;
		sf::Clock _spawnClock;
		sf::Time _spawnTime = sf::seconds(0.5f);
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration { 0, 0};
		sf::FloatRect _enemyCollider;

		virtual void initEnemy() = 0;
		virtual void updateVelocity();
		void spawningUpdate(sf::Transformable&);
		void checkBounds();

	public:
		Enemy() {};
		virtual ~Enemy();

		virtual void update() = 0;
		virtual bool checkBulletCollision();
		bool checkPlayerCollision();
		void setExplosion();

		static std::vector<Bullet>* _bulletsRef;
		static sf::Vector2f* _playerPos;
		static sf::Vector2f* _startPos;
		static sf::FloatRect* _playerCollider;
		static sf::FloatRect _playAreaCollider;
	};
}

