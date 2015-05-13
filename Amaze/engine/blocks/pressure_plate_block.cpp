#include "stdafx.h"

#include "all_in_one.h"

PressurePlateBlock::PressurePlateBlock(Core *core, Vector2 position) : Block(core, position)
{
	this->floor = TileType::fPressurePlateOne;

	blocksMotion = false;
	pressed = false;
}

double PressurePlateBlock::GetFloorHeight()
{
	return pressed ? -0.05 : 0.05;
}

void PressurePlateBlock::Tick()
{
	list<PhysicalBody*> bodies = core->level->GetPhysicalBodiesInRadius(position, 0.7, false, true);
	pressed = !bodies.empty();
	this->floor = pressed ? TileType::fPressurePlateTwo : TileType::fPressurePlateOne;
}