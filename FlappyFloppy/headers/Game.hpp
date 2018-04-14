#pragma once
//Biblioteki SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//Moje naglowki
//--KLASA DYSKIETKI
#include "Floppy.hpp"
//--KLASA RAMU
#include "RAM.hpp"
class Game {
public:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	float velocity;
	Game();
	sf::Text createText(const std::string& content, const uint8_t& fontSize, const sf::Color& fontColor, const sf::Vector2f& textPosition);
	void update();

	void executeGame();
};

string floatToString(float numberToConvert);
bool intersects(const Floppy& f, const RAM& r);
void checkPoints(Floppy& f, const RAM& r);
void centerText(Text& text, const float& offset);
