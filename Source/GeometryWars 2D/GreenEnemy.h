#pragma once
#include "pch.h"
#include "Enemy.h"
#include "Utilities.h"

namespace GWar
{
	/*
	Green Enemy dodges bullets.
	split direction vector of Enemy to bullet into components parallel and perpendicular to bullet velocity.
	magnitude of the component perpendicular to bullet velocity is the distance of closest approach of the bullet.
	if magnitude is below a certain value, it is considered head-on and Green enemy does not dodge.
	if magnitude is greater than a certain value, it is considered too far away to be a threat and is ignored.
	between these values, Green enemy dodges in the opposite direction of the component of direction vector perpendicular to bullet velocity.
	*/
	
	class GreenEnemy final : public Enemy
	{
	private:
		sf::RectangleShape _enemyShape;
		sf::CircleShape _innerShape;
		sf::Clock dodgeClock;
		sf::Time dodgeDuration = sf::seconds(0.1f);
		bool isDodging = false;
		int currentZ = 1;

		void draw(sf::RenderTarget&, sf::RenderStates) const;
		void initEnemy();
		void moveShapes();

	public:
		GreenEnemy();
		~GreenEnemy();

		bool checkBulletCollision();
		void update();
	};
}
