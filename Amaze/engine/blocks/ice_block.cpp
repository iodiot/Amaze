#include "stdafx.h"

#include "all_in_one.h"

IceBlock::IceBlock(Core *core, Vector2 position) : Block(core, position)
{
	this->floor = TileType::fIce;

	blocksMotion = false;
}

double IceBlock::GetFriction(Entity *entity)
{
	Player *player = dynamic_cast<Player*>(entity);
	if (player && player->GetSelectedItem() == ItemType::Skates)
		return 0.5;

	return 0;
}
