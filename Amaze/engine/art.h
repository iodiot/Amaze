#ifndef ART_H
#define ART_H

#include "stdafx.h"

class Core;

struct TexType
{
	enum e
	{
		Floors,
		Sprites,
		Walls,
		Items
	};
};

struct TileType
{
	enum e
	{
		None = -1,

		// Floors
		fCarpet = 0,
		fPit,
		fWaterOne = 8,
		fWaterTwo = 9,
		fWaterThree = 10,
		fGrass = 24,
		fWood = 25,
		fIce = 16,
		fPressurePlateOne = 2,
		fPressurePlateTwo = 3,

		// Sprites
		sJail = 0, 
		sCuttedJail = 1,
		sStoneParticle = 2,
		sBatOne = 32,
		sBatTwo = 33,
		sTorchOne = 3,
		sTorchTwo = 4,
		sBoulderOne = 8,
		sBoulderTwo = 9,
		sBoulderInPit = 10,
		sLadderDown = 11,
		sLadderUp = 12,
		sOpenedChest = 17,
		sClosedChest = 16,
		sBowl = 18,
		sAltar = 20,
		sGhostOne = 38,
		sGhostTwo = 39,

		// Walls
		wMasonry = 0, 
		wBroken = 1,
		wGrass = 8,
		wDoor = 4,
		wSafe = 5,
		wSwitchOne = 2,
		wSwitchTwo = 3,

		// Items
		iPowerGlove = 0,
		iPistol,
		iFlippers,
		iCutters,
		iSkates,
		iKey,
		iPotion
	};
};

class Art
{
private:
	Core *core;

public:
	SDL_Surface *walls;
	SDL_Surface *floors;
	SDL_Surface *sprites;
	SDL_Surface *items;
	SDL_Surface *font;
	SDL_Surface *skybox;
	SDL_Surface *logo;
	SDL_Surface *gamepanel;

private:
	SDL_Surface* LoadTex(const char *fileName);

public:
	Art(Core *core);	
	~Art();

	void Load();
};

struct Color
{
	static const uint Amask = 0xff000000;	
	static const uint Bmask = 0x000000ff;
	static const uint Gmask = 0x0000ff00;
	static const uint Rmask = 0x00ff0000;

	static const uint Ashift = 24;
	static const uint Rshift = 16;
	static const uint Gshift = 8;
	static const uint Bshift = 0;	

	static const uint White		= 0xffffff;
	static const uint Black		= 0x000000;
	static const uint Red			= 0xff0000;
	static const uint Yellow	= 0xffff00;
	static const uint Cyan		= 0x00ffff;
	static const uint Green		= 0x00ff00;
	static const uint Blue		= 0x0000ff;

	uint r, g, b, a;

	Color(uint hex);
	uint ToHex();

	void FastChannelsMul(double x);
	void FastChannelsMul(uint x);

	static uint KillAlpha(uint hex);
	static uint FastChannelsMul(uint hex, uint x);
	static uint FastChannelsMul(uint hex, double x);
};

#endif