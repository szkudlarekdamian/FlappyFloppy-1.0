#include "headers/Game.hpp"
//Biblioteki podstawowe
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;
using namespace sf;

bool Floppy::isGrounded = false;

//KONSTRUKTOR GRY, USTAWIA TLO I CZCIONKE
Game::Game() {
	font.loadFromFile("Lato-Regular.ttf");

	backgroundTexture.loadFromFile("images/BGRD.jpg");
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin({ 864.f,0.f });
	velocity = 1.5f;
}
//FUNKCJA DO TWORZENIA TEKSTU
sf::Text Game::createText(const std::string& content, const uint8_t& fontSize, const sf::Color& fontColor = {0,0,0}, const sf::Vector2f& textPosition = { 0.f,0.f }) {
	sf::Text defaultText(content, font, fontSize);
	defaultText.setFillColor(fontColor);
	defaultText.setPosition(textPosition);
	return defaultText;
}
//ANIMACJA T£A
void Game::update() {
	if (!Floppy::isGrounded) {
		backgroundSprite.move({ -velocity,0.f });
		if (backgroundSprite.getPosition().x <= 0.f)
			backgroundSprite.setPosition({ 864.f,0.f });
	}
}
//ZAMIANA FLOAT NA STRING
string floatToString(float numberToConvert) {
	std::ostringstream stream;
	stream << numberToConvert;
	return string(stream.str());
}
//FUNKCJA SPRAWDZAJACA CZY NAST¥PI£O PRZECIÊCIE DYSKIETYKI Z RAMEM
bool intersects(const Floppy& f, const RAM& r) {
	if (f.floppySprite.getGlobalBounds().intersects(r.UpperRAMSprite.getGlobalBounds()) || f.floppySprite.getGlobalBounds().intersects(r.LowerRAMSprite.getGlobalBounds()))
		return true;
	return false;
}
//DODAWANIE PUNKTOW PO PRZEJSCIU PRZESZKODY
void checkPoints(Floppy& f, const RAM& r) {
	if ((int)(r.UpperRAMSprite.getPosition().x + r.UpperRAMSprite.getLocalBounds().width) == (int)(f.x()))
		f.points++;
}
//FUNKCJA WYŒRODKOWUJ¥CA TEKST +/- OFFSET W PIONIE
void centerText(Text & text, const float & offset = 0.f){
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	text.setPosition({ xres / 2.f, yres / 2.f + offset});
}
//GLOWNA FUNKCJA GRY 
void Game::executeGame() {
	//inicjalizacja okna
	RenderWindow window(sf::VideoMode((uint16_t)xres, (uint16_t)yres), "Flappy Floppy");
	window.setFramerateLimit(60);	
	//inicjalizacja j¹dra gry
	Game game;
	//Wychwytywanie eventów
	Event event;
	while (window.pollEvent(event)) {
		//Wyjscie z gry
		if (event.type == Event::Closed)
			window.close();
	}
	//inicjalizacja postaci
	Floppy floppy("images/floppy.png");
	//inicjalizacja przeszkod
	RAM dice(450.f);
	RAM dice2(717.f);
	RAM dice3(984.f);
	//inicjalizacja tekstów w grze
	Text points = game.createText("", 90, { Color(255,255,255) }, { 20.f,20.f });
	Text over = game.createText("YOU LOSE", 140, { Color(190,10,0,0) });
	Text instructions = game.createText("PRESS SPACE", 88, { Color::White }, { xres/2 - 88.f*3.f,yres/2.f - 88.f });
	Text instructionsEnd = game.createText("Backspace - restart\nEsc - quit", 44, { Color(255,255,255,0) }, { xres / 2.f - 44.f * 3.f,yres/2.f+44.f });
	centerText(over);
	centerText(instructions);
	centerText(instructionsEnd, 150.f);

	RectangleShape klawisz;
	klawisz.setSize({ 50.f,50.f });
	klawisz.setPosition({ 300.f,300.f });
	klawisz.setFillColor({ Color::White });

	String slowo = "ANALNE IGRASZKI";
	String zakodowane;

	for (short i = 0; i <= slowo.getSize(); i++){
		if(isalnum(slowo[i]))zakodowane += '_';
		else zakodowane += ' ';
	}
	//PÊTLA G£ÓWNA OKNA
	while (window.isOpen()){
		//Update punktow
		//points.setString({ floatToString(floppy.points) });
		//Po wcisnieciu spacji gra sie rozpoczyna
		if (Keyboard::isKeyPressed(Keyboard::Space))
			floppy.firstClick = true;
		
		
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			
			for (short i = 0; i <= slowo.getSize(); i++) {
				cout <<zakodowane[i]<<",";
				if (slowo[i] == 'A') {
					zakodowane[i] = 'A';
				}
			}
		}
		points.setString(zakodowane);
		//Wykonanie skoku
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (klawisz.getGlobalBounds().contains({(Vector2f)Mouse::getPosition(window)}))
				cout << "Klik " << Mouse::getPosition(window).x << "," << Mouse::getPosition(window).y << "\n";
		}
		floppy.onKeyDown();
		//Czy gra zosta³a rozpoczêta?
		if (floppy.firstClick) {
			instructions.setColor({ 0,0,0,0 });
			game.update();
			dice.update();
			dice2.update();
			dice3.update();
		}
		//Zliczanie punktów
		checkPoints(floppy, dice);
		checkPoints(floppy, dice2);
		checkPoints(floppy, dice3);
		//Warunek przegrania
		if (intersects(floppy, dice) || intersects(floppy, dice2) || intersects(floppy, dice3) || floppy.floppySprite.getPosition().y >= floppy.groundHeight) {
			floppy.die();
			instructionsEnd.setColor({ Color(255,255,255,255) });
			over.setColor({ Color(230,10,0,255) });
		}
		//restart gry
		if(floppy.isGrounded)
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				instructions.setColor({ 255,255,255,255 });
				floppy.resurrect();
				dice.setPositionTo(450.f);
				dice2.setPositionTo(717.f);
				dice3.setPositionTo(984.f);
				backgroundSprite.setPosition({ 864.f,0.f });
				over.setColor({ Color(0,0,0,0) });
				instructionsEnd.setColor({ Color(255,255,255, 0) });
			}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
		//Rozpoczêcie rysowania
		window.clear();
		
		//Rysowanie t³a
		window.draw(game.backgroundSprite);
		//Rysowanie przeszkód
		window.draw(dice.UpperRAMSprite);
		window.draw(dice.LowerRAMSprite);
		window.draw(dice2.UpperRAMSprite);
		window.draw(dice2.LowerRAMSprite);
		window.draw(dice3.UpperRAMSprite);
		window.draw(dice3.LowerRAMSprite);
		//Rysowanie punktów
		window.draw(points);
		//Rysowanie dyskietki
		window.draw(floppy.floppySprite);
		//Rysowanie konca gry
		window.draw(over);
		window.draw(instructions);
		window.draw(instructionsEnd);
		window.draw(klawisz);
		//Wyœwietlenie zebranych obiektów
		window.display();		
	}
	//--KONIEC PÊTLI G£ÓWNEJ OKNA
}