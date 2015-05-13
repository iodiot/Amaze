#include "stdafx.h"

#include "all_in_one.h"

PitBlock::PitBlock(Core *core, Vector2 position) : Block(core, position)
{
	floor = TileType::fPit;

	empty = true;
}

void PitBlock::Collide(PhysicalBody *body)
{
	if (!empty) return;

	bool isBoulder = dynamic_cast<BoulderEntity*>(body) != 0;

	if (isBoulder)
	{
		blocksMotion = false;
		empty = false;
	}
}