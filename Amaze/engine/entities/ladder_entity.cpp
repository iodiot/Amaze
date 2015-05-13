#include "stdafx.h"

#include "all_in_one.h"

LadderEntity::LadderEntity(Core *core, Vector2 position, bool up)
	: Entity(core, position)
{
	this->up = up;

	sprite = up ? TileType::sLadderUp : TileType::sLadderDown;

	radius = 0.2;
}

void LadderEntity::Collide(PhysicalBody *body)
{
	// Collided with player?
	if (dynamic_cast<Player*>(body))
	{
		Sound::Play(SoundType::Ladder);
		core->level->SwitchLevel(id);
	}
}