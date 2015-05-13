#include "stdafx.h"

#include "all_in_one.h"

Input::Input(Core *core)
{
	this->core = core;

	turnLeft = turnRight = false;
	up = down = space = esc = false;
	left = right = false;

	for (int i = 0; i < DigitsCount; ++i)
		digits[i] = false;
}

void Input::Tick(SDL_KeyboardEvent event, bool keyDown)
{
	switch(event.keysym.sym)
	{
		case SDLK_UP:
		case SDLK_w: up = keyDown; break;

		case SDLK_DOWN:
		case SDLK_s: down = keyDown; break;

		case SDLK_LEFT: turnLeft = keyDown; break;
		case SDLK_RIGHT: turnRight = keyDown; break;

		case SDLK_a: left = keyDown; break;
		case SDLK_d: right = keyDown; break;

		case SDLK_SPACE: space = keyDown; break;
		case SDLK_ESCAPE: esc = keyDown; break;

		case SDLK_1: digits[0] = keyDown; break;
		case SDLK_2: digits[1] = keyDown; break;
		case SDLK_3: digits[2] = keyDown; break;
		case SDLK_4: digits[3] = keyDown; break;
		case SDLK_5: digits[4] = keyDown; break;
		case SDLK_6: digits[5] = keyDown; break;
		case SDLK_7: digits[6] = keyDown; break;
		case SDLK_8: digits[7] = keyDown; break;
	}
}