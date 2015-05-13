#ifndef ITEM_H
#define ITEM_H

#include "stdafx.h"
#include "art.h"

struct ItemType
{
	enum e
	{
		None,
		PowerGlove,
		Pistol,
		Flippers,
		Cutters,
		Skates,
		Key,
		Potion
	};

	static TileType::e	GetTile(ItemType::e item);
	static uint					GetTint(ItemType::e item);
	static char*				GetName(ItemType::e item);
	static char*				GetDescription(ItemType::e item);
};

#endif