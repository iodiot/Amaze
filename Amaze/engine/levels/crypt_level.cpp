#include "stdafx.h"

#include "all_in_one.h"


CryptLevel::CryptLevel(Core *core) : Level(core) 
{
	strcpy(shortName, "crypt");
	strcpy(fullName, "The Crypt");

	floorTint = 0x404040;
	wallTint = 0x404040;
}

void CryptLevel::SwitchLevel(int id) 
{
	if (id == 1) core->SwitchLevel(LevelType::Overworld, 2);
}

void CryptLevel::GetLoot(int id) 
{
	Level::GetLoot(id);
	if (id == 1) core->GetLoot(ItemType::Flippers);
}