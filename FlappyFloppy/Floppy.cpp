#include "headers/Floppy.hpp"

//KONSTRUKTOR DYSKIETKI
Floppy::Floppy(const string & filename) {
	setFloppyTexture(filename);
	this->floppySprite.setPosition(xres / 3.f, yres / 2.f);
	
	buffer.loadFromFile("sounds/boing.wav");
	boing.setBuffer(buffer);

	points = { 0 };

	//SZYBKOŒÆ OPADANIA
	gravity = { 0.5f };
	groundHeight = { yres - floppySide };

	isGrounded = { false };
	keyPressed = { false };
	firstClick = { false };

	velocity = { 0.f,0.f };

	//WYSOKOŒÆ SKOKU
	jumpSpeed = { 9.0f };
}

void Floppy::onKeyDown() {
	if (firstClick) {
		//JEŒLI WCIŒNIÊTO SPACJÊ - WZNIEŒ SIÊ; keyPressed ogranicza skok do pojedynczego
		if (Keyboard::isKeyPressed(Keyboard::Space) && keyPressed == false && y() >= 0.f) {
			if (!isGrounded) {
				keyPressed = true;
				boing.play();
				velocity.y = -jumpSpeed;
			}
		}
		//JEŒLI NIE WCIŒNIÊTO SPACJI, OZNAJMIJ GOTOWOSC DO LOTU
		else if (!Keyboard::isKeyPressed(Keyboard::Space))
			keyPressed = false;
		//JEŒLI DYSKIETKA JEST W LOCIE LUB JEJ PRÊDKOŒÆ JEST UJEMNA(UNOSI SIÊ), DODAJ DO PRÊDKOŒCI SI£Y GRAWITACJI(OPADA) 
		if (y() < groundHeight || velocity.y < 0.f)
			velocity.y += gravity;
		//JEŒLI DYSKIETKA NIE JEST W LOCIE, NIECH ZATRZYMA SIÊ NA ZIEMI 
		else {
			floppySprite.setPosition(x(), groundHeight);
			velocity.y = 0.f;
		}
		//WYKONAJ PRZESUNIÊCIE O 
		floppySprite.move(0.f, velocity.y);
	}
}
//UPADEK
void Floppy::die() {
	jumpSpeed = 0.f;
	isGrounded = true;
	if (y() == groundHeight) {
		setFloppyTexture("images/floppy_dead.png");
	}
}
//RESTART GRY
void Floppy::resurrect() {
	isGrounded = false;
	points = 0;
	jumpSpeed = 9.f;
	floppySprite.setPosition({ xres / 3.f, yres / 2.f });
	firstClick = false;
	setFloppyTexture("images/floppy.png");
}

//GETERY
float Floppy::x() { return floppySprite.getPosition().x; }
float Floppy::y() { return floppySprite.getPosition().y; }
//USTAW GRAFIKE
void Floppy::setFloppyTexture(const string & filename) {
	this->floppyTexture.loadFromFile(filename);
	this->floppySprite.setTexture(floppyTexture);
	this->floppySprite.setScale({ floppyScale,floppyScale });
}

