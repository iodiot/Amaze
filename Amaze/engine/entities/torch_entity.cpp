#include "stdafx.h"

#include "all_in_one.h"

TorchEntity::TorchEntity(Core *core, Vector2 position) : Entity(core, position)
{
	sprite = TileType::sTorchOne;

	FindPlaceToAttach(this->position);
	blocksMotion = false;
}

bool TorchEntity::IsSolidBlock(int x, int y)
{
	Block *b = core->level->GetBlock(x, y);
	if (!b) return false;

	return (dynamic_cast<SolidBlock*>(b) != 0);
}

void TorchEntity::FindPlaceToAttach(Vector2 &p)
{
	static const double d = 1.0 / 30.0;

	int x = int(p.x);
	int y = int(p.y);

	if (IsSolidBlock(x - 1, y))
	{
		p.x += d;
		p.y += 0.5;
	}
	else if (IsSolidBlock(x + 1, y))
	{
		p.x += 1 - d;
		p.y += 0.5;
	}
	else if (IsSolidBlock(x, y - 1))
	{
		p.x += 0.5;
		p.y += d;
	}
	else if (IsSolidBlock(x, y + 1))
	{
		p.x += 0.5;
		p.y += 1 - d;
	}
}

void TorchEntity::Tick()
{
	if (core->NextInt(10) == 5)
		sprite = (sprite == TileType::sTorchOne) ? TileType::sTorchTwo : TileType::sTorchOne;
}

