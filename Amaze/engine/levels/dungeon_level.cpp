#include "stdafx.h"

#include "all_in_one.h"

DungeonLevel::DungeonLevel(Core *core) : Level(core)
{
	strcpy(shortName, "dungeon");
	strcpy(fullName, "The Dungeons");

	floorTint = 0x8E4A51;
	wallTint = 0xC64954;
}

void DungeonLevel::SwitchLevel(int id)
{
	if (id == 1) core->SwitchLevel(LevelType::Start, 2);
}

void DungeonLevel::GetLoot(int id)
{
	Level::GetLoot(id);
	if (id == 1) core->GetLoot(ItemType::PowerGlove);
}
