#include "stdafx.h"

#include "all_in_one.h"

Core::Core(SDL_Surface *screen)
{
	// Randomize
	srand((unsigned)time(0)); 

	art = new Art(this);
	art->Load();

	this->screen = new Screen(this, screen);

	input = new Input(this);

	// Create levels
	levels[LevelType::Start] = new StartLevel(this);
	levels[LevelType::Dungeon] = new DungeonLevel(this);
	levels[LevelType::Overworld] = new OverworldLevel(this);
	levels[LevelType::Ice] = new IceLevel(this);
	levels[LevelType::Crypt] = new CryptLevel(this);
	levels[LevelType::Temple] = new TempleLevel(this);

	level = levels[LevelType::Start];
	level->Load();

	player = new Player(this, level->startSpawnPosition);
	//level->FindSpawnPosition(1, player->position);
	level->AddEntity(player);
	player->AddLoot(ItemType::PowerGlove);
	player->AddLoot(ItemType::Pistol);
	player->AddLoot(ItemType::Flippers);
	player->AddLoot(ItemType::Cutters);
	player->AddLoot(ItemType::Skates);
	player->AddLoot(ItemType::Key);
	player->AddLoot(ItemType::Potion);

	ticks = 0;
	menu = 0;

	newLevel = LevelType::None;
}

Core::~Core()
{
	// Free levels
	map<LevelType::e, Level*>::iterator it;
	for (it = levels.begin(); it != levels.end(); ++it)
		delete it->second;

	delete art;
	delete input;
	delete screen;
	delete player;
	if (menu)
		delete menu;
}

void Core::Tick()
{
	if (input->esc && !menu)
	{
		SetMenu(new PauseMenu(this));
		input->esc = false;
	}

	if (!menu)
	{
		level->Tick();
		++ticks;
	}
	else
		menu->Tick();

	screen->Draw();

	// Switch level if needed
	if (newLevel != LevelType::None)
	{
		level = levels[newLevel];
		if (!level->isLoaded)
		{
			level->Load();
			level->AddEntity(player);
		}
		level->FindSpawnPosition(newLevelSpawnId, player->position);

		newLevel = LevelType::None;

		char message[0xff];
		sprintf(message, "Entering %s!", level->fullName);
		screen->ShowMessage(message, 50);
	}
}

int Core::NextInt(int max)
{
	return rand() % max;
}

double Core::NextDouble()
{
	return (double)NextInt(RAND_MAX) / (double)RAND_MAX;
}

void Core::SetMenu(Menu *menu)
{
	if (this->menu)
		delete this->menu;

	this->menu = menu;

	input->space = false;
}

void Core::SwitchLevel(LevelType::e newLevel, int id)
{
	this->newLevel = newLevel;
	newLevelSpawnId = id;
}

void Core::GetLoot(ItemType::e item)
{
	SetMenu(new GotLootMenu(this, item));
	player->AddLoot(item);
}

RuntimeException::RuntimeException(const char *message)
{
	strcpy(this->message, message);
}