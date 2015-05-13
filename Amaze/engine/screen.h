#ifndef SCREEN_H
#define SCREEN_H

#include "stdafx.h"

class Core;
class Renderer;
class Drawer;

class Screen
{
private:
	Core *core;
	Renderer *renderer;

	// Screen buffer
	SDL_Surface *screen;
	uint *buffer;

	// Fps
	uint previousTime;
	uint elapsedTime;
	int frameCounter;
	int frameRate;

	char debug[0xff];

	char message[0xff];
	int showMessageTime;

private:
	void CalculateFps();
	void DrawSkybox();
	void DrawHud();

public:
	Drawer *drawer;
	int width, height;

public:
	Screen(Core *core, SDL_Surface *screen);
	~Screen();

	void Draw();
	void ShowMessage(const char *message, int showTime);

	void BufferToScreen();
};

#endif