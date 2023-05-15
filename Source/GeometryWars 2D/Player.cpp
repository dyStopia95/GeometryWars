#include "pch.h"
#include "Player.h"

namespace GWar
{
	void Player::initPlayer()
	{
		_playerShape.setRadius( 10.f );
		_playerShape.setOrigin( 10.f , 10.f );
		_playerShape.setPosition( 0 , 0 );
		_playerShape.setFillColor(sf::Color( 0 , 0 , 0 , 0 ));
		_playerShape.setOutlineColor(sf::Color::White);
		_playerShape.setOutlineThickness( -2.f );		
	}

	void Player::initMousePointer()
	{
		_mousePointer.setRadius(4.f);
		_mousePointer.setOrigin(-20.f, 4.f);
		_mousePointer.setFillColor(sf::Color(0, 0, 0, 0));
		_mousePointer.setOutlineColor(sf::Color::White);
		_mousePointer.setOutlineThickness(-2.f);
	}

	void Player::draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const
	{
		//Draw Bullets
		for (const Bullet& B : _bullets)
			targetWindow.draw(B, states);

		//Draw Player and Bullet pointer
		targetWindow.draw(_playerShape, states);
		targetWindow.draw(_mousePointer, states);
	}


	void Player::checkBounds()
	{
		if (_playerCollider.top <= _playAreaCollider.top + 3.f && _velocity.y < 0)
			_velocity.y = 0;
		if ((_playerCollider.top + _playerShape.getRadius() * 2 >= _playAreaCollider.top + _playAreaCollider.height - 3.f) && _velocity.y > 0)
			_velocity.y = 0;
		if (_playerCollider.left <= _playAreaCollider.left + 3.f && _velocity.x < 0)
			_velocity.x = 0;
		if ((_playerCollider.left + _playerShape.getRadius() * 2 >= _playAreaCollider.left + _playAreaCollider.width - 3.f) && _velocity.x > 0)
			_velocity.x = 0;
	}

	std::vector<Bullet>& Player::getBulletList()
	{
		return _bullets;
	}

	sf::FloatRect* Player::getPlayerCollider()
	{
		return &_playerCollider;
	}

	sf::CircleShape Player::getPlayerShapeCopy()
	{
		return _playerShape;
	}

	Player::Player(sf::RectangleShape& _mapFrame) :
		_playAreaRef{ _mapFrame }
	{
		initPlayer();
		initMousePointer();
		_bullets.reserve(1000);
	}

	Player::~Player()
	{
	}

	void Player::centerPlayer(const sf::RenderTarget* window)
	{
		sf::Vector2<float> windowCenter = { static_cast<float>(window->getSize().x)/2, static_cast<float>(window->getSize().y)/2};
		_playerShape.move(windowCenter);
		_mousePointer.move(windowCenter);

		//Initialize local coordinate of player to match window
		_localCoord = _playerShape.getPosition();

		//Set Playarea collider (put here because HUD Center() shifts play area
		_playAreaCollider = _playAreaRef.getGlobalBounds();
		Bullet::_playAreaRef = &_playAreaCollider;
	}

	void Player::getInputs()
	{
		_velocity = sf::Vector2f(0.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			_velocity = _velocity + sf::Vector2f{ -1.f, 0.f };
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_velocity = _velocity + sf::Vector2f{ 1.f, 0.f };
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_velocity = _velocity + sf::Vector2f{ 0.f,-1.f };
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			_velocity = _velocity + sf::Vector2f{ 0.f,1.f };
		}

		//Check if velocity is diagonal. Normalize if yes
		if (!isUnitVector(&_velocity))
		{
			normalizeDiagonal(&_velocity);
		}

		//Check boundary collisions
		checkBounds();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(_fireClock.getElapsedTime() > _fireInterval)
			{
				_fireClock.restart();
				_bullets.emplace_back(Bullet{ &_globalCoord, _mouseVector, &_mouseAngle, _velocity});
			}
		}
	}

	void Player::updatePlayer(sf::Vector2f* mouseCoord)
	{
		_globalCoord = _playerShape.getPosition();

		_playerCollider = _playerShape.getGlobalBounds();

		getInputs();

		//Update player global coordinates
		_velocity = _velocity * _speed;		

		// Update local coordinates within player class to reflect draw transforms in game class (for use by bullet pointer)
		_localCoord = _localCoord + _velocity/2.f;	

		//Get vector to cursor
		_mouseVector = *mouseCoord - _localCoord;
		_mouseAngle = getAngle(&_mouseVector);

		//Rotate bullet pointer
		_mousePointer.setRotation(-_mouseAngle);
		_playerShape.move(_velocity);
		_mousePointer.move(_velocity);

		//Update Bullets
		auto B = _bullets.begin();

		while (B != _bullets.end())
		{
			if (B->updateAndCheckBounds())
				B = _bullets.erase(B);
			else
				++B;
		}
	}

	sf::Vector2f* Player::getPlayerVelocity()
	{
		return &_velocity;
	}

	sf::Vector2f* Player::getPlayerPos()
	{
		return &_globalCoord;
	}

}