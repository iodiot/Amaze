#include "stdafx.h"

#include "all_in_one.h"

IceLevel::IceLevel(Core *core) : Level(core)
{
	strcpy(shortName, "ice");
	strcpy(fullName, "The Frost Cave");

	floorTint = 0xB8DBE0;
	wallTint = 0x6BE8FF;
}

void IceLevel::SwitchLevel(int id)
{
	if (id == 1) core->SwitchLevel(LevelType::Overworld, 5);
}

void IceLevel::GetLoot(int id)
{
	Level::GetLoot(id);
	if (id == 1) core->GetLoot(ItemType::Skates);
}