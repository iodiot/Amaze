#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Core;

class Input
{
private:
	Core *core;

public:
	bool up, down, space, esc, left, right;
  bool turnLeft, turnRight;

	static const int DigitsCount = 8;

	bool digits[DigitsCount];

public:
	Input(Core *core);

	void Tick(SDL_KeyboardEvent event, bool keyDown);
};

#endif