#include "headers/RAM.hpp"
#include <iostream>
  
int RAM::randomInt()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> d(110, 302);
	return d(mt);
}

RAM::RAM(const float& xPos){
	float firstRandom = randomInt();
	RAMTexture.loadFromFile("images/RAM.png");
	UpperRAMSprite.setTexture(RAMTexture);
	LowerRAMSprite.setTexture(RAMTexture);
	setPositionTo(xPos);
	velocity = 1.5f;
}

void RAM::update() {
	if (!Floppy::isGrounded) {
		UpperRAMSprite.move({ -velocity,0.f });
		LowerRAMSprite.move({ -velocity,0.f });
		if (UpperRAMSprite.getPosition().x <= -83.f) {
			setPositionTo(800.f);
		}
	}
}

void RAM::setPositionTo(const float & xPos){
	float firstRandom = randomInt();
	UpperRAMSprite.setPosition({ xPos, 100.f - firstRandom });
	LowerRAMSprite.setPosition({ xPos, 600.f - firstRandom });
}
