#pragma once
#include "Enemy.h"
#include "Utilities.h"

namespace GWar
{
    /*
    Purple enemy moves along curves that have a chance to change their curvature at set intervals.
    */
    
    class PurpleEnemy final : public Enemy
    {
    private:
        sf::CircleShape _enemyShape;
        sf::Time inflectionTime = sf::seconds(5.f);
        sf::Clock inflectionClock;
        int currentZ;

        void initEnemy();
        void draw(sf::RenderTarget&, sf::RenderStates) const;

    public:
        PurpleEnemy();
        ~PurpleEnemy();

        void update();
    };
}

