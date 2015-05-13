#include "stdafx.h"

#include "all_in_one.h"

ParticleEntity::ParticleEntity(Core *core, Vector2 position, double centerHeight) : Entity(core, position)
{
	const double g = -9.81 * 0.0005;

	this->centerHeight = centerHeight;

	sprite = TileType::sStoneParticle;

	blocksMotion = false;
	radius = 0.1;
	ttl = 200 + core->NextInt(100);

  velocity = Vector2((core->NextDouble() - 0.5) * 0.05,  (core->NextDouble() - 0.5) * 0.05);
	centerAcceleration = g;
	centerVelocity = 0;
	ignoresPhysics = true;
}

void ParticleEntity::Tick()
{
	const double floorHeight = 0.5;

	if (ttl-- <= 0)
	{
		core->level->RemoveEntity(this);
		return;
	}

	velocity += acceleration;
	position += velocity;

	centerVelocity += centerAcceleration;
	centerHeight += centerVelocity;

	if (centerHeight <= floorHeight)
	{
		velocity *= -0.5;
		centerVelocity *= -0.5;

		centerHeight = floorHeight;
	}
}

