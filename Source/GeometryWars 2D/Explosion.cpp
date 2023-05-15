#include "pch.h"
#include "Explosion.h"

namespace GWar
{
	sf::Vector2f Particle::_startPos;
	sf::Color Particle::_explosionColor;

	void Particle::draw(sf::RenderTarget& targetWindow, sf::RenderStates globalTransform) const
	{
		targetWindow.draw(&_particle, 1, sf::Points, globalTransform);
	}
	
	Particle::Particle() :
		_particle{ _startPos, sf::Color::White }
	{
		_particle.color = _explosionColor;

		float x = static_cast<float>(std::rand() % 100);
		float y = static_cast<float>(std::rand() % 100);
		x -= 50;
		y -= 50;
		x /= 10;
		y /= 10;

		_velocity.x = x;
		_velocity.y = y;

		_acceleration = -_velocity / 50.f;
	}
	
	void Particle::update()
	{
		_particle.position = _particle.position + _velocity;
		_velocity += _acceleration;
		_acceleration = -_velocity / 50.f;
	}
	
	void Explosion::draw(sf::RenderTarget& targetWindow, sf::RenderStates globalTransform) const
	{
		for (auto& particle : _particleList)
		{
			targetWindow.draw(particle, globalTransform);
		}
	}

	Explosion::Explosion()
	{
		sf::Uint8 R = std::rand() % 127;
		sf::Uint8 G = std::rand() % 127;
		sf::Uint8 B = std::rand() % 127;

		R += 127;
		G += 127;
		B += 127;

		Particle::_explosionColor = sf::Color(R, G, B, 255);

		for (int i = 0; i < _particleCount; ++i)
		{
			_particleList.emplace_back(Particle{});
		}
		cout << "Explosion!\n";
	}

	void Explosion::update()
	{
		for (auto& particle : _particleList)
		{
			particle.update();
		}
	}

}