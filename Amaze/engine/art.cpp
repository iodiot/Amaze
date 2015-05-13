#include "stdafx.h"

#include "all_in_one.h"

Art::Art(Core *core)
{
	this->core = core;
}

Art::~Art()
{
	// Free texs
	SDL_FreeSurface(walls);
	SDL_FreeSurface(items);
	SDL_FreeSurface(font);
	SDL_FreeSurface(floors);
	SDL_FreeSurface(sprites);
	SDL_FreeSurface(skybox);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(gamepanel);
}

SDL_Surface* Art::LoadTex(const char *fileName)
{
	SDL_Surface *s = IMG_Load(fileName);
	if (!s)
	{
		char message[0xff];
		sprintf(message, "Can not load resource file %s", fileName);
		throw RuntimeException(message);
	}

	return s;
}

void Art::Load()
{
	walls = LoadTex("res/tex/walls.png");
	items = LoadTex("res/tex/items.png");
	font = LoadTex("res/tex/font.png");
	floors = LoadTex("res/tex/floors.png");
	sprites = LoadTex("res/tex/sprites.png");
	skybox = LoadTex("res/tex/sky.png");
	logo = LoadTex("res/gui/logo.png");
	gamepanel = LoadTex("res/tex/gamepanel.png");
}

Color::Color(uint hex)
{
	a = hex & Amask;
	a >>= Ashift;

	r = hex & Rmask;
	r >>= Rshift;

	g = hex & Gmask;
	g >>= Gshift;

	b = hex & Bmask;
	b >>= Bshift;
}

uint Color::ToHex()
{
	return (a << Ashift) + (r << Rshift) + (g << Gshift) + (b << Bshift);
}

uint Color::KillAlpha(uint hex)
{
	return hex ^ (hex & Amask);
}

void Color::FastChannelsMul(double x)
{
	uint xx = uint(x * 255.0);
	r = (r * xx) >> 8;
	g = (g * xx) >> 8;
	b = (b * xx) >> 8;
}

void Color::FastChannelsMul(uint x)
{
	Color xx(x);

	r = (r * xx.r) >> 8;
	g = (g * xx.g) >> 8;
	b = (b * xx.b) >> 8;
}

uint Color::FastChannelsMul(uint hex, uint x)
{
	Color c(hex);
	c.FastChannelsMul(x);
	return c.ToHex();
}

uint Color::FastChannelsMul(uint hex, double x)
{
	Color c(hex);
	c.FastChannelsMul(x);
	return c.ToHex();
}

