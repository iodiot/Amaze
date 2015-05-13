#include "stdafx.h"

#include "all_in_one.h"

DoorBlock::DoorBlock(Core *core, Vector2 position) : Block(core, position)
{
	wall = TileType::wDoor;

	openess = 0;
	open = false;
}

void DoorBlock::Tick()
{
	openess += open ? 0.2 : -0.2;
	if (openess <= 0) openess = 0;
	if (openess > 0.9) openess = 0.9;
}

Rect DoorBlock::GetBoundingRect()
{
	if (core->level->GetBlock(int(position.x), int(position.y) - 1)->wall == TileType::None)
		return Rect(position.x - radius, position.y - 0.1, 0.2, 1 - openess);
	else
		return Rect(position.x - 0.1, position.y - radius, 0.2, 1 - openess);
}

bool DoorBlock::Use(PhysicalBody *body, ItemType::e item)
{
	open = !open;
	return true;
}