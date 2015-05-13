#include "stdafx.h"

#include "all_in_one.h"

char* ItemType::GetName(e item)
{
	switch (item)
	{
		case PowerGlove: return "Power Glove";
		case Pistol: return "Pistol";
		case Flippers: return "Flippers";
		case Cutters: return "Cutters";
		case Skates: return "Skates";
		case Key: return "Key";
		case Potion: return "Potion";
		default: return "";
	}
}

uint ItemType::GetTint( e item )
{
	switch (item)
	{
		case PowerGlove: return 0xFFC363;
		case Pistol: return 0xEAEAEA;
		case Flippers: return 0x7CBBFF;
		case Cutters: return 0xCCCCCC;
		case Skates: return 0xAE70FF;
		case Key: return 0xFF4040;
		case Potion: return 0x4AFF47;
		default: return Color::White;
	}
}

TileType::e ItemType::GetTile( e item )
{
	switch (item)
	{
		case PowerGlove: return TileType::iPowerGlove;
		case Pistol: return TileType::iPistol;
		case Flippers: return TileType::iFlippers;
		case Cutters: return TileType::iCutters;
		case Skates: return TileType::iSkates;
		case Key: return TileType::iKey;
		case Potion: return TileType::iPotion;
		default: return TileType::None;
	}
}

char* ItemType::GetDescription( e item )
{
	switch (item)
	{
		case PowerGlove: return "Smaaaash!!";
		case Pistol: return "Pew, pew, pew!";
		case Flippers: return "Splish splash!";
		case Cutters: return "Snip, snip!";
		case Skates: return "Sharp!";
		case Key: return "How did you get this?";
		case Potion: return "Healthy!";
		default: return "";
	}
}

