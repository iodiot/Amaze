#include "stdafx.h"

#include "all_in_one.h"

GhostEntity::GhostEntity(Core *core, Vector2 position) : EnemyEntity(core, position)
{
	sprite = TileType::sGhostOne;
}