#include "stdafx.h"

#include "all_in_one.h"

AltarEntity::AltarEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sAltar;
	radius = 0.3;
}

void AltarEntity::Collide(PhysicalBody *body)
{
}