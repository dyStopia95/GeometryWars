#include "pch.h"
#include "Bullet.h"

namespace GWar
{
	sf::FloatRect* Bullet::_playAreaRef = nullptr;

	void Bullet::initBullet()
	{
		_bulletShape.setSize(sf::Vector2f(10.f, 6.f));
		_bulletShape.setFillColor(sf::Color(0, 0, 0, 0));
		_bulletShape.setOutlineColor(sf::Color(255, 199, 43, 255));
		_bulletShape.setOutlineThickness(-2.f);
		_bulletShape.setOrigin(5.f, 3.f);
	}

	void Bullet::draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const
	{
		targetWindow.draw(_bulletShape, states);
	}

	Bullet::Bullet(sf::Vector2f* playerPos, sf::Vector2f mouseVector, float* rotateAngle, const sf::Vector2f& playerVelocity)
	{
		//Initialize bullet shape
		initBullet();

		//Move shape to Player position
		_bulletShape.setPosition(*playerPos);

		//Set starting position of the bullet as well as velocity for use in update
		_velocity = mouseVector;
		vectorNormalize(&_velocity);
		_bulletShape.move(_velocity * _startRadius);
		_velocity = _velocity * _speed + playerVelocity;
		_bulletShape.setRotation( - *rotateAngle);
	}

	Bullet::~Bullet()
	{

	}

	sf::FloatRect& Bullet::getBulletCollider()
	{
		return _bulletCollider;
	}

	bool Bullet::updateAndCheckBounds()
	{
		//Update
		_bulletShape.move(_velocity);
		_bulletCollider = _bulletShape.getGlobalBounds();

		//Check Bullet - Boundary Collision
		if (checkBoundaryCollision())
		{
			return true;
		}

		else
			return false;
	}

	bool Bullet::checkBoundaryCollision()
	{
		float bulletTop = _bulletShape.getGlobalBounds().top;
		float bulletBottom = bulletTop + _bulletShape.getGlobalBounds().height;
		float bulletLeft = _bulletShape.getGlobalBounds().left;
		float bulletRight = bulletLeft + _bulletShape.getGlobalBounds().width;

		if
			(
				bulletTop <= _playAreaRef->top ||
				bulletBottom >= _playAreaRef->top + _playAreaRef->height ||
				bulletLeft <= _playAreaRef->left ||
				bulletRight >= _playAreaRef->left + _playAreaRef->width
				)
			return true;

		else
			return false;
	}

	sf::Vector2f Bullet::getBulletVelocity()
	{
		return _velocity;
	}

	sf::Vector2f Bullet::getBulletPos()
	{
		return _bulletShape.getPosition();
	}

}