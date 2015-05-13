#include "stdafx.h"

#include "all_in_one.h"

LootEntity::LootEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sBowl;

	radius = 0.1;
}

void LootEntity::Collide(PhysicalBody *body)
{
	Player *player = dynamic_cast<Player*>(body);
	if (player)
	{
		Sound::Play(SoundType::Pickup);
		++player->bowls;
		core->level->RemoveEntity(this);
	}
}

