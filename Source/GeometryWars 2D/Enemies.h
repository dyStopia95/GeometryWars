#pragma once
#include "Bullet.h"

namespace GWar
{
	class Enemies : public sf::Drawable
	{
	private:
		sf::Clock _spawnClock;
		sf::Time _spawnTime = sf::seconds(0.5f);
		bool _isSpawning = true;
		float _currentScale;
		float _speed = 1.f;
		sf::Vector2f _velocity;
		sf::RectangleShape _enemyShape;
		sf::CircleShape _enemyCollider;
		sf::FloatRect _tempCollider;
		void initEnemy();
		virtual void draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const;

	public:
		Enemies();
		~Enemies();
		bool updateAndCheckAliveEnemy();

		static std::vector<Bullet>* _bulletsRef;
		static sf::Vector2f* _playerPos;
		static sf::FloatRect* _playerCollider;
		static sf::Vector2f* _startPos;

	};
}