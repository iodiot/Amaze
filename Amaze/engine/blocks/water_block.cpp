#include "stdafx.h"

#include "all_in_one.h"

WaterBlock::WaterBlock(Core *core, Vector2 position) : Block(core, position)
{
	this->floor = TileType::fWaterOne;
}

void WaterBlock::Tick()
{
	if (core->ticks % 50 == 0)
	{
		int r = core->NextInt(3);
		if (r == 0)
			floor = TileType::fWaterOne;
		else if (r == 1)
			floor = TileType::fWaterTwo;
		else 
			floor = TileType::fWaterThree;
	}
}

bool WaterBlock::Blocks(PhysicalBody *body)
{
	Player *player = dynamic_cast<Player*>(body);
	if (player)
		return player->GetSelectedItem() != ItemType::Flippers;

	return blocksMotion;
}

double WaterBlock::GetFloorHeight()
{
	return -0.5;
}

double WaterBlock::GetFriction(Entity *entity)
{
	return 0.7;
}
