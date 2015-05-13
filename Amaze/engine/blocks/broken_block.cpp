#include "stdafx.h"

#include "all_in_one.h"

BrokenBlock::BrokenBlock(Core *core, Vector2 position) : Block(core, position)
{
	wall = TileType::wBroken;

	broken = false;
	blocksMotion = true;
}

bool BrokenBlock::Use(PhysicalBody *body, ItemType::e item)
{
	if (!broken)
	{
		Sound::Play(SoundType::Crumble);

		wall = TileType::None;
		blocksMotion = false;

		// Create particles
		for (int i = 0; i < 10; ++i)
		{
			Vector2 p = position;
			p.x += core->NextDouble() - 0.5;
			p.y += core->NextDouble() - 0.5;
			core->level->AddEntity(new ParticleEntity(core, p, core->NextDouble() + 0.5));
		}

		broken = true;

		return true;
	}

	return false;
}