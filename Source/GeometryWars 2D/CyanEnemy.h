#pragma once
#include "Enemy.h"
#include "Utilities.h"

namespace GWar
{
	/*
	Cyan Enemy simply follows the player.
	velocity vector of Cyan enemy updates to direction to player, normalized and multiplied by set speed.
	*/
	
	class CyanEnemy final : public Enemy
	{
	private:
		sf::CircleShape _enemyShape;
		void initEnemy();
		void draw(sf::RenderTarget&, sf::RenderStates) const;

	public:
		CyanEnemy();
		~CyanEnemy();

		void update();
	};
}

