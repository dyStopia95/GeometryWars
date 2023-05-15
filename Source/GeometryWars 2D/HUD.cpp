#include "pch.h"
#include "HUD.h"

namespace GWar
{
	HUD::HUD() :
		_background{_mapFrame}
	{
		initPlayArea();

		//Initialize positions of stars
		for (int i = 0; i < starCount; ++i)
		{
			float tempX, tempY;
			tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().width + 50.f))) + _mapFrame.getGlobalBounds().left;
			tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().height + 50.f))) + _mapFrame.getGlobalBounds().top;
			starField1.emplace_back(sf::Vertex{ sf::Vector2f{tempX - 50.f,tempY - 50.f}, sf::Color::White });
		}
		for (int i = 0; i < starCount; ++i)
		{
			float tempX, tempY;
			tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().width + 50.f))) + _mapFrame.getGlobalBounds().left;
			tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().height + 50.f))) + _mapFrame.getGlobalBounds().top;
			starField2.emplace_back(sf::Vertex{ sf::Vector2f{tempX - 50.f,tempY - 50.f}, sf::Color::White });
		}
		for (int i = 0; i < starCount; ++i)
		{
			float tempX, tempY;
			tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().width + 50.f))) + _mapFrame.getGlobalBounds().left;
			tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().height + 50.f))) + _mapFrame.getGlobalBounds().top;
			starField3.emplace_back(sf::Vertex{ sf::Vector2f{tempX - 50.f,tempY - 50.f}, sf::Color::White });
		}
		for (int i = 0; i < starCount; ++i)
		{
			float tempX, tempY;
			tempX = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().width + 50.f))) + _mapFrame.getGlobalBounds().left;
			tempY = static_cast<float>(std::rand() % (static_cast<int>(_mapFrame.getGlobalBounds().height + 50.f))) + _mapFrame.getGlobalBounds().top;
			starField4.emplace_back(sf::Vertex{ sf::Vector2f{tempX - 50.f,tempY - 50.f}, sf::Color::White });
		}
	}

	HUD::~HUD()
	{
	}

	void HUD::initPlayArea()
	{
		_mapFrame.setSize({ 900.f, 700.f });
		_mapFrame.setOutlineThickness(2.f);
		_mapFrame.setFillColor(sf::Color(0, 0, 0, 0));
		_mapFrame.setOutlineColor(sf::Color::Cyan);
	}

	void HUD::centerHUD(const sf::RenderTarget* const targetWindow)
	{
		sf::Vector2f centeringOffset =
		{
			(targetWindow->getSize().x - _mapFrame.getSize().x) / 2.f,
			(targetWindow->getSize().y - _mapFrame.getSize().y) / 2.f
		};

		_mapFrame.move(centeringOffset);
		_background.populateStrips();

	}

	void HUD::drawHUD(sf::RenderTarget* targetWindow, sf::Transform* globalTransform, sf::Transform* st1, sf::Transform* st2, sf::Transform* st3, sf::Transform* st4)
	{
		st1;
		st2;
		st3;
		for (auto& vertex : starField1)
			targetWindow->draw(&vertex, 1, sf::Points, *st1);
		for (auto& vertex : starField2)
			targetWindow->draw(&vertex, 1, sf::Points, *st2);
		for (auto& vertex : starField3)
			targetWindow->draw(&vertex, 1, sf::Points, *st3);
		for (auto& vertex : starField4)
			targetWindow->draw(&vertex, 1, sf::Points, *st4);
		targetWindow->draw(_background, *globalTransform);
		targetWindow->draw(_mapFrame, *globalTransform);
	}

	sf::RectangleShape& HUD::getPlayArea()
	{
		return _mapFrame;
	}

	Background::Background(const sf::RectangleShape& mapRef) :
		_mapRef {mapRef}
	{

	}

	Background::~Background()
	{

	}

	void Background::populateStrips()
	{
		float x, y, bottomMax, rightMax, verticalLength, horizontalLength;
		x = _mapRef.getGlobalBounds().top + _stripWidth + _mapRef.getOutlineThickness();
		y = _mapRef.getGlobalBounds().left;
		verticalLength = _mapRef.getGlobalBounds().height;
		horizontalLength = _mapRef.getGlobalBounds().width;
		bottomMax = x + verticalLength;
		rightMax = y + horizontalLength;

		int i = 1;

		//set Vertical strips
		while (x <= rightMax - _mapRef.getOutlineThickness() - _stripWidth)
		{
			sf::RectangleShape temp;
			temp.setSize(sf::Vector2f{ _stripWidth, verticalLength });
			temp.setPosition(x, y);
			if (i == 3)
			{
				temp.setFillColor(_bgMainColor);
				i = 0;
			}
			else
				temp.setFillColor(_bgSecondaryColor);
			_vetricalStrips.push_back(temp);
			x += 2 * _stripWidth;
			++i;
		}

		//set Horizontal strips
		i = 1;
		x = _mapRef.getGlobalBounds().top;
		y = _mapRef.getGlobalBounds().left + _stripWidth + _mapRef.getOutlineThickness();

		while (y <= bottomMax - _mapRef.getOutlineThickness() - _stripWidth)
		{
			sf::RectangleShape temp;
			temp.setSize(sf::Vector2f{ horizontalLength, _stripWidth });
			temp.setPosition(x, y);
			if (i == 3)
			{
				temp.setFillColor(_bgMainColor);
				i = 0;
			}
			else
				temp.setFillColor(_bgSecondaryColor);
			_vetricalStrips.push_back(temp);
			y += 2 * _stripWidth;
			++i;
		}

	}

	void Background::draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const
	{
		for (auto& I : _vetricalStrips)
			targetWindow.draw(I, states);
		for (auto& I : _horizontalStrips)
			targetWindow.draw(I, states);

	}

}