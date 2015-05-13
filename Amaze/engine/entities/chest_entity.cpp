#include "stdafx.h"

#include "all_in_one.h"

ChestEntity::ChestEntity(Core *core, Vector2 position)
	: Entity(core, position)
{
	opened = false;
	sprite = TileType::sClosedChest;

	radius = 0.3;
	blocksMotion = true;
}

bool ChestEntity::Use(PhysicalBody *body, ItemType::e item)
{
	if (!opened)
	{
		Sound::Play(SoundType::Treasure);
		opened = true;
		sprite = TileType::sOpenedChest;

		core->level->GetLoot(id);

		return true;
	}

	return false;
}

