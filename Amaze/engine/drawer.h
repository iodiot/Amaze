#ifndef DRAWER_H
#define DRAWER_H

#include "stdafx.h"

class Core;

class Drawer
{
private:
	Core *core;

	uint *buffer;

public:
	// Special chars
	static const char Heart = '\2';
	static const char Bowl = '\3';
	static const char Key = '\4';

	int width, height;

public:
	Drawer(Core *core, uint *buffer, int width, int height);
	
	void Draw(const SDL_Surface *surface, const SDL_Rect *srs, const SDL_Rect *dest, uint tint = Color::White, int scale = 1);
	void Draw(const char *text, int x, int y, uint color = Color::White);
	void Draw(const SDL_Surface *surface, int tile, int x, int y, uint tint = Color::White, int scale = 1);
	void Draw(const SDL_Surface *surface, const SDL_Rect *srs, int x, int y, uint tint = Color::White, int scale = 1);

	int TextWidth(const char *text);
	
	void Fill(int x, int y, int width, int height, uint color);
	void Fill(uint color);
};

#endif