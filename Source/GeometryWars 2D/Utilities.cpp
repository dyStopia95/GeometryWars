#include "pch.h"
#include "Utilities.h"

namespace GWar
{
	float getMagnitude(const sf::Vector2f* v)
	{
		return sqrt(((v->x) * (v->x)) + ((v->y) * (v->y)));
	}

	void vectorNormalize(sf::Vector2f* vectorToNormalize)
	{
		float magnitude = getMagnitude(vectorToNormalize);
		vectorToNormalize->x = vectorToNormalize->x / magnitude;
		vectorToNormalize->y = vectorToNormalize->y / magnitude;
	}

	float getAngle(sf::Vector2f* v)
	{
		float magnitude = getMagnitude(v);
		float angle = static_cast<float> (std::acos(v->x / magnitude) * 180 / 3.141592);
		if (v->y < 0)
			return angle;
		else
			return -angle;
	}

	sf::Vector2f getNormalVector(const sf::Vector2f& v, int z)
	{
		if (z > 0)
			return sf::Vector2f{ v.y, -v.x };
		if (z < 0)
			return sf::Vector2f{ -v.y, v.x };
		else
			return sf::Vector2f{ 0,0 };
	}

	float getDotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	float magnitudeCrossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{
		return (v1.x * v2.y - v1.y * v2.x);
	}

	void pause(float t)
	{
		sf::Clock pauseClock;
		sf::Time pauseTime = sf::seconds(t);
		while (pauseClock.getElapsedTime() < pauseTime);
	}

	bool isUnitVector(const sf::Vector2f* v)
	{
		if ((v->x + v->y == 1.f || v->x + v->y == -1.f))
			return true;
		else if (*v == sf::Vector2f{ 0,0 })
			return true;
		else
			return false;
	}

	void normalizeDiagonal(sf::Vector2f* v)
	{
		v->x = v->x * (0.707106f);
		v->y = v->y * (0.707106f);
	}
}