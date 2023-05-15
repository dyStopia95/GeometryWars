#pragma once

namespace GWar
{
	class Particle : public sf::Drawable
	{
	private:
		sf::Vertex _particle;
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

	public:
		Particle();
		void update();

		static sf::Vector2f _startPos;
		static sf::Color _explosionColor;
	};

	class Explosion : public sf::Drawable
	{
	private:
		std::vector<Particle> _particleList;
		int _particleCount = 50;

		void draw(sf::RenderTarget&, sf::RenderStates) const;

	public:
		sf::Clock _explosionClock;
		Explosion();
		void update();

	};
}
