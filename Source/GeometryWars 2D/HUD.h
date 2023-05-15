#pragma once

namespace GWar
{
	class Background : public sf::Drawable
	{
	private:
		float _bgMainInterval = 5; //Multiple of 5
		float _stripWidth = 6.125;
		sf::Color _bgMainColor{ 64, 13, 217, 75};
		sf::Color _bgSecondaryColor{ 64, 13, 217, 50 };
		std::vector <sf::RectangleShape> _horizontalStrips;
		std::vector <sf::RectangleShape> _vetricalStrips;
		const sf::RectangleShape& _mapRef;
		virtual void draw(sf::RenderTarget& targetWindow, sf::RenderStates states) const;

	public:
		Background(const sf::RectangleShape& mapRef);
		~Background();
		void populateStrips();
	};

	class HUD
	{
	private:
		sf::RectangleShape _mapFrame;
		Background _background;
		int starCount = 50;
		std::vector<sf::Vertex> starField1;
		std::vector<sf::Vertex> starField2;
		std::vector<sf::Vertex> starField3;
		std::vector<sf::Vertex> starField4;

	public:
		HUD();
		~HUD();
		void initPlayArea();
		void centerHUD(const sf::RenderTarget*);
		void drawHUD(sf::RenderTarget*, sf::Transform*, sf::Transform*, sf::Transform*, sf::Transform*, sf::Transform*);
		sf::RectangleShape& getPlayArea();
	};
}