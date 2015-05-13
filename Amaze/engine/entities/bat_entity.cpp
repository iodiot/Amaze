#include "stdafx.h"

#include "all_in_one.h"

BatEntity::BatEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sBatOne;

	animAge = 0;
	actionAge = 0;

	radius = 0.3;
}

void BatEntity::Tick()
{
	if (animAge++ > 7) {
		sprite = (sprite == TileType::sBatOne) ? TileType::sBatTwo : TileType::sBatOne;
		animAge = 0;
	}

	acceleration.x = .01 * cos(core->ticks * .05);
	acceleration.y = -.01 * sin(core->ticks * .05);

	//return; 

	if (actionAge++ > core->NextInt(200) + 50) {
		acceleration.x = (core->NextDouble() - .5) / 40;
		acceleration.y = (core->NextDouble() - .5) / 40;
		actionAge = 0;
	}
}