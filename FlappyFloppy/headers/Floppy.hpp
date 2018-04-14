#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr float xres{ 800 }, yres{ 600 };
//	sta³e dla dyskietki
constexpr float floppyScale{ 0.25f };
constexpr float floppySide{ 256.0f * floppyScale };

using namespace sf;
using namespace std;
class Floppy
{
public:
	Texture floppyTexture;
	Sprite floppySprite;
	Sound boing;
	SoundBuffer buffer;
	//
	float jumpSpeed, gravity, groundHeight;
	float points, flyTime;
	bool keyPressed, firstClick;
	Vector2f velocity;
	//
	Floppy(const string& filename);
	//
	void onKeyDown();
	void die();
	void resurrect();
	//
	float x();
	float y();
	void setFloppyTexture(const string& filename);
	static bool isGrounded;
};

