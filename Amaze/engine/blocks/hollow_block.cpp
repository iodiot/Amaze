#include "stdafx.h"

#include "all_in_one.h"

HollowBlock::HollowBlock(Core *core, Vector2 position, TileType::e floor, TileType::e ceil) 
	: Block(core, position)
{
	wall = TileType::None;

	this->floor = floor;
	this->ceil = ceil;

	blocksMotion = false;
}