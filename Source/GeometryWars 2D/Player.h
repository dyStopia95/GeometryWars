#pragma once
#include "Bullet.h"
#include "Utilities.h"

namespace GWar
{
	class Player : public sf::Drawable
	{
	private:
		std::vector<Bullet> _bullets;
		sf::Clock _fireClock;
		sf::Vector2f _velocity = { 0.f , 0.f };
		float _speed = 1.5;
		float _mouseAngle;
		sf::CircleShape _playerShape;
		sf::Vector2f _globalCoord;
		sf::Vector2f _localCoord;
		sf::Vector2f _mouseVector;
		sf::Event _playerInput;
		sf::CircleShape _mousePointer;
		sf::Time _fireInterval = sf::seconds(0.075f);
		const sf::RectangleShape& _playAreaRef;
		sf::FloatRect _playerCollider;
		sf::FloatRect _playAreaCollider;

		//sf::Vector2<float> test = globalCoord * speed;
		void initPlayer();
		void initMousePointer();
		virtual void draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const;
		void checkBounds();

	public:
		Player(sf::RectangleShape&);
		~Player();
		void centerPlayer(const sf::RenderTarget*);
		void getInputs();
		void updatePlayer(sf::Vector2f*);
		std::vector<Bullet>& getBulletList();
		sf::Vector2f* getPlayerVelocity();
		sf::Vector2f* getPlayerPos();
		sf::FloatRect* getPlayerCollider();
		sf::CircleShape getPlayerShapeCopy();
	};
}

