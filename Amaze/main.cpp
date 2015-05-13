#include "stdafx.h"

#include "all_in_one.h"

static Core *core;
static SDL_Surface* screen = 0;

void Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(Consts::ScreenWidth, Consts::ScreenHeight,
		32, SDL_SWSURFACE | SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_AudioSpec fmt;
	fmt.freq = 22050;
	fmt.format = AUDIO_S16;
	fmt.channels = 2;
	fmt.samples = 512;        /* A good value for games */
	fmt.callback = MixAudio;
	fmt.userdata = NULL;

	SDL_OpenAudio(&fmt, 0);
	SDL_PauseAudio(0);

	core = new Core(screen);
}

void DeInitialize()
{
	delete core;

	SDL_CloseAudio();

	SDL_Quit();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE	hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const uint targetFps = 60;
	const uint frameDuration = 1000 / targetFps;

	Initialize();

	bool running = true;

	while (running)
	{
		uint beforeTick = SDL_GetTicks();

		SDL_LockSurface(screen);

		core->Tick();

		SDL_UnlockSurface(screen);

		SDL_Flip(screen);

		// Limit framerate
		int delay = (beforeTick + frameDuration) - SDL_GetTicks();
		if (delay > 0) 
			SDL_Delay(delay);

		SDL_Event event; 
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				core->input->Tick(event.key, true);
				break;
			case SDL_KEYUP:
				core->input->Tick(event.key, false);
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}
	}

	DeInitialize();

	return 0;
}
