#include "stdafx.h"

#include "all_in_one.h"

JailEntity::JailEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sJail;

	radius = 0.3;
	cutted = false;
}

void JailEntity::Tick()
{
}

bool JailEntity::Use(PhysicalBody *body, ItemType::e item)
{
	if (item == ItemType::Cutters && !cutted)
	{
		Sound::Play(SoundType::Cut);
		cutted = true;
		sprite = TileType::sCuttedJail;
		blocksMotion = false;

		return true;
	}

	return false;
}