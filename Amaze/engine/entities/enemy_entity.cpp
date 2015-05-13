#include "stdafx.h"

#include "all_in_one.h"

EnemyEntity::EnemyEntity(Core *core, Vector2 position) : Entity(core, position)
{
	radius = 0.3;
}

void EnemyEntity::Tick()
{
	Vector2 playerDirection = (core->player->position - position);

	if (playerDirection.Length() >= Consts::EventHorizon / 2)
		return;

	velocity = playerDirection.Normalized() * 0.05;
}

bool EnemyEntity::Use(PhysicalBody *body, ItemType::e item)
{
	return true;
}