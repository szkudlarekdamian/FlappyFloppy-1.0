#pragma once
#include <SFML\Graphics.hpp>
#include "Floppy.hpp"
#include <random>
using namespace sf;
class RAM
{
public:
	Texture RAMTexture;
	Sprite UpperRAMSprite, LowerRAMSprite;
	float velocity;
	int randomInt();
	RAM(const float& xPos);
	void update();
	void setPositionTo(const float& xPos);
};
