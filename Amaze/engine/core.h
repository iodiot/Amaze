#ifndef CORE_H
#define CORE_H

#include "SDL.h"
#include "levels/level.h"
#include "item.h"

class Input;
class Player;
class Level;
class Art;
class Menu;
class Screen;

class Core
{
private:

	Screen *screen;

	LevelType::e newLevel;
	int newLevelSpawnId;
	map<LevelType::e, Level*> levels;

public:
	Input *input;
	Player *player;
	Level *level;
	Art *art;
	Menu *menu;

	uint ticks;

public:
	Core(SDL_Surface *screen);
	~Core();

	void Tick();

	void SetMenu(Menu *menu);
	void SwitchLevel(LevelType::e newLevel, int id);
	void GetLoot(ItemType::e item);

	// Random
	int NextInt(int max);
	double NextDouble();
};

class RuntimeException : public exception
{
private:
	char message[0xff];

public:
	RuntimeException(const char *message);
};

#endif