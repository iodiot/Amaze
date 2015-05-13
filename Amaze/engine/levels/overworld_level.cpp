#include "stdafx.h"

#include "all_in_one.h"

OverworldLevel::OverworldLevel(Core *core) : Level(core)
{
	strcpy(shortName, "overworld");
	strcpy(fullName, "The Island");

	defaultFloor = TileType::fGrass;
	defaultCeil = TileType::None;
	hasSkybox = true;
	floorTint = Color::Green;
}

void OverworldLevel::SwitchLevel(int id)
{
	if (id == 1) core->SwitchLevel(LevelType::Start, 1);
	if (id == 2) core->SwitchLevel(LevelType::Crypt, 1);
	if (id == 3) core->SwitchLevel(LevelType::Temple, 1);
	if (id == 5) core->SwitchLevel(LevelType::Ice, 1);
}


void OverworldLevel::GetLoot(int id)
{
	Level::GetLoot(id);
	if (id == 1) core->GetLoot(ItemType::Cutters);
}
