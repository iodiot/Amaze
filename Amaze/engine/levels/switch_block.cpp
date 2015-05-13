#include "stdafx.h"

#include "all_in_one.h"

SwitchBlock::SwitchBlock(Core *core, Vector2 position) : Block(core, position)
{
	wall = TileType::wSwitchOne;
}

bool SwitchBlock::Use(PhysicalBody *body, ItemType::e item)
{
	pressed = !pressed;
	wall = pressed ? TileType::wSwitchTwo : TileType::wSwitchOne;
	return true;
}