#include "stdafx.h"

#include "all_in_one.h"

Entity::Entity(Core *core, Vector2 position) : PhysicalBody(core, position)
{
	sprite = TileType::None;

	velocity = Vector2();
	acceleration = Vector2();
	centerHeight = 0.5;
	rotation = 0;
	flying = false;
	ignoresPhysics = false;
}

void Entity::Tick()
{

}

double Entity::GetCenterHeight()
{
	return centerHeight;
}

void Entity::SetCenterHeight(double centerHeight)
{
	this->centerHeight = centerHeight;
}

