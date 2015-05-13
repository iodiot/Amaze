#include "stdafx.h"

#include "all_in_one.h"

StartLevel::StartLevel(Core *core) : Level(core)
{
	strcpy(shortName, "start");
	strcpy(fullName, "The Prison");

	floorTint = 0x9CA09B;
	wallTint = 0xB3CEE2;
}

void StartLevel::SwitchLevel(int id)
{
	if (id == 1) core->SwitchLevel(LevelType::Overworld, 1);
	if (id == 2) core->SwitchLevel(LevelType::Dungeon, 1);
}

void StartLevel::GetLoot(int id)
{
	Level::GetLoot(id);
}