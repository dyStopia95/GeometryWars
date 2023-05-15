#pragma once

namespace GWar
{
	float getMagnitude(const sf::Vector2f* v);
	bool isUnitVector(const sf::Vector2f* v); //Returns true for Zero vectors as well
	void normalizeDiagonal(sf::Vector2f* v); //Quick normalization for player movement using magic values
	void vectorNormalize(sf::Vector2f* v);
	float getAngle(sf::Vector2f* v);
	sf::Vector2f getNormalVector(const sf::Vector2f& v, int z);
	float getDotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float magnitudeCrossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
	void pause(float t);
}
