#include "stdafx.h"

#include "all_in_one.h"

TempleLevel::TempleLevel(Core *core) : Level(core)
{
	strcpy(shortName, "temple");
	strcpy(fullName, "The Temple");

	floorTint = 0x8A6496;
	wallTint = 0xCFADDB;
}

void TempleLevel::GetLoot(int id)
{
	Level::GetLoot(id);
	if (id == 1) core->GetLoot(ItemType::Skates);
}

void TempleLevel::SwitchLevel(int id)
{
	if (id == 1) core->SwitchLevel(LevelType::Overworld, 3);
}