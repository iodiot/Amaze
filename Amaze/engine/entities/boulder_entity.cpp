#include "stdafx.h"

#include "all_in_one.h"

BoulderEntity::BoulderEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sBoulderOne;

	radius = 0.4;
	inPit = false;
}

void BoulderEntity::Tick()
{
}

bool BoulderEntity::Use(PhysicalBody *body, ItemType::e item)
{
	if ((item == ItemType::None || item == ItemType::PowerGlove) && !inPit)
	{
		Sound::Play(SoundType::Roll);
		Vector2 direction = (position - body->position).Normalized();
		velocity = direction; 

		return true;
	}

	return false;
}

void BoulderEntity::Collide(PhysicalBody *body)
{
	bool isPit = dynamic_cast<PitBlock*>(body) != 0;

	if (isPit)
	{
		inPit = true;
		sprite = TileType::sBoulderInPit;
		position = body->position;
		blocksMotion = false;
	}
}