#pragma once
#include "Utilities.h"

namespace GWar
{
	class Bullet : public sf::Drawable
	{
	private:
		//Variables
		sf::FloatRect _bulletCollider;
		sf::RectangleShape _bulletShape;
		sf::Vector2f _velocity;
		float _startRadius = 15;
		float _speed = 4;

		//Initializing functions
		void initBullet();
		virtual void draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const;

	public:
		Bullet(sf::Vector2f* playerPos, sf::Vector2f mouseVector, float* rotateAngle, const sf::Vector2f& playerVelocity);
		~Bullet();
		//void setStartPos(sf::Vector2f* playerPos, sf::Vector2f mouseVector, float* rotateAngle);
		sf::FloatRect& getBulletCollider();
		bool updateAndCheckBounds();
		bool checkBoundaryCollision();
		sf::Vector2f getBulletVelocity();
		sf::Vector2f getBulletPos();

		static sf::FloatRect* _playAreaRef;
	};
}