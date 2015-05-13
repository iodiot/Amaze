#include "stdafx.h"

#include "all_in_one.h"

Block::Block(Core *core, Vector2 position) : PhysicalBody(core, position)
{
	wall = TileType::None;
	floor = TileType::None;
	ceil = TileType::None;
}

void Block::Tick()
{
}

double Block::GetFloorHeight()
{
	return 0;
}

double Block::GetFriction(Entity *entity)
{
	return 0.5;
}


