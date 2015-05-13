#include "stdafx.h"

#include "all_in_one.h"

SolidBlock::SolidBlock(Core *core, Vector2 position, TileType::e wall) : Block(core, position)
{
	this->wall = wall;
}