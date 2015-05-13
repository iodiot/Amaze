#include "stdafx.h"

#include "all_in_one.h"

Level::Level(Core *core)
{
	this->core = core;

	width = height = -1;
	map = 0;

	strcpy(shortName, "");
	strcpy(fullName, "");

	defaultFloor = TileType::fCarpet;
	defaultCeil = TileType::fCarpet;
	floorTint = Color::White;
	wallTint = Color::White;
	hasSkybox = false;

	isLoaded = false;
}

Level::~Level()
{
	if (!isLoaded) return;

	// Free blocks
	if (map)
	{
		for (int x = 0; x < width; ++x)
			for (int y = 0; y < height; ++y)
				if (map[x + y * width])
					delete map[x + y * width];

		delete[] map;
	}

	// Free entities
	list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it)
		if (*it != core->player)
			delete *it;	
}

void Level::Load()
{
	if (isLoaded) return;

	char filePath[0xff];

	sprintf(filePath, "res/level/%s.png", shortName);

	SDL_Surface *tex = IMG_Load(filePath);

	width = tex->w;
	height = tex->h;

	const int size = width * height;
	
	uint *colors = new uint[size];
	memcpy(colors, tex->pixels, sizeof(uint) * size);

	FloodFill(colors, 0, 0, width, height, colors[0], cMagicPink);

	LoadBlocks(colors);
	LoadEntities(colors);

	delete[] colors;

	SDL_FreeSurface(tex);

	isLoaded = true;
}

void Level::FloodFill(uint *colors, int x, int y, int width, int height, int emptyColor, int fillColor)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	if (colors[x + y * width] == emptyColor)
	{
		colors[x + y * width] = fillColor;
		FloodFill(colors, x - 1, y, width, height, emptyColor, fillColor);
		FloodFill(colors, x + 1, y, width, height, emptyColor, fillColor);
		FloodFill(colors, x, y - 1, width, height, emptyColor, fillColor);
		FloodFill(colors, x, y + 1, width, height, emptyColor, fillColor);
	}
}

void Level::LoadBlocks(const uint *colors)
{
	map = new Block*[width * height];

	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)
		{
			int n = x + y * width;

			uint a = Color(colors[n]).a;
			uint c = Color::KillAlpha(colors[n]);

			if (c == cMagicPink)
			{
				map[n] = 0;
				continue;
			}

			Vector2 position(x + 0.5, y + 0.5);

			if (c == cBlock)
				map[n] = new SolidBlock(core, position, TileType::wMasonry);
			else if (c == cGrassWall)
				map[n] = new SolidBlock(core, position, TileType::wGrass);
			else if (c == cBrokenWall)
				map[n] = new BrokenBlock(core, position);
			else if (c == cFootPath)
				map[n] = new HollowBlock(core, position, TileType::fWood);
			else if (c == cDoor)
				map[n] = new DoorBlock(core, position);
			else if (c == cPit)
				map[n] = new PitBlock(core, position);
			else if (c == cWater)
				map[n] = new WaterBlock(core, position);
			else if (c == cIceOne || c == cIceTwo)
				map[n] = new IceBlock(core, position);
			else if (c == cPressurePlate)
				map[n] = new PressurePlateBlock(core, position);
			else if (c == cSwitch)
				map[n] = new SwitchBlock(core, position);
			else
				map[n] = new HollowBlock(core, position);

			if (map[n])
				map[n]->id = 0xff - a;

			if (c == cSpawnPoint)
				startSpawnPosition = Vector2(x, y);
		}
}

void Level::LoadEntities(const uint *colors)
{
	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)
		{
			int n = x + y * width;

			uint a = Color(colors[n]).a;
			uint c = Color::KillAlpha(colors[n]);

			Vector2 centerPosition(x + 0.5, y + 0.5);

			Entity *e = 0;

			if (c == cBat)
				e = new BatEntity(core, centerPosition);
			else if (c == cJail)
				e = new JailEntity(core, centerPosition);
			else if (c == cTorch)
				e = new TorchEntity(core, Vector2(x, y));
			else if (c == cBoulder)
				e = new BoulderEntity(core, centerPosition);
			else if (c == cLadderUp)
			{
				e = new LadderEntity(core, centerPosition, true);
				GetBlock(x, y)->ceil = TileType::fPit;
			}
			else if (c == cLadderDown)
			{
				e = new LadderEntity(core, centerPosition, false);
				GetBlock(x, y)->floor = TileType::fPit;
			}
			else if (c == cChest)
				e = new ChestEntity(core, centerPosition);
			else if (c == cLoot)
				e = new LootEntity(core, centerPosition);
			else if (c == cAltar)
				e = new AltarEntity(core, centerPosition);
			else if (c == cGhost)
				e = new GhostEntity(core, centerPosition);

			if (e)
			{
				e->id = 0xff - a;
				entities.push_back(e);
			}
		}
}

Block* Level::GetBlock(int x, int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return 0;

	return map[x + y * width];
}

void Level::Tick()
{
	Physics::MoveEntities(this);

	list<Entity*>::iterator it;

	// Update entities
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		Entity *e = *it;
		e->Tick();
	}

	// Update blocks
	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)
		{
			Block *b = GetBlock(x, y);
			if (b != NULL)
				b->Tick();
		}

	// Add entities
	for (it = entitiesToAdd.begin(); it != entitiesToAdd.end(); ++it)
		entities.push_back(*it);
	entitiesToAdd.clear();

	// Remove entities
	for (it = entitiesToRemove.begin(); it != entitiesToRemove.end(); ++it)
	{
		Entity *e = *it;

		entities.remove(e);
		delete e;
	}
	entitiesToRemove.clear();
}

uint Level::GetTileTint(TexType::e tex, TileType::e tile)
{
	if (tex == TexType::Walls)
		switch (tile)
		{
			case TileType::wGrass: return 0x00ff00;
			case TileType::wDoor: return 0xeeeeee;
			default: return wallTint;
		}

	if (tex == TexType::Floors)
		switch (tile)
		{
			case TileType::fGrass: return 0x00ff00;
			case TileType::fWood: return 0xdb8e53;
			case TileType::fWaterOne:
			case TileType::fWaterTwo:
			case TileType::fWaterThree: return Color::Blue;
			case TileType::fIce: return 0x8080ff;
			default: return floorTint;
		}

	if (tex == TexType::Sprites)
		switch (tile)
		{
			case TileType::sJail:
			case TileType::sCuttedJail: return 0x808080;
			case TileType::sTorchOne:
			case TileType::sTorchTwo: return 0xffff55;
			case TileType::sLadderDown:
			case TileType::sLadderUp: return 0xdb8e53;
			case TileType::sBoulderOne:
			case TileType::sBoulderTwo:
			case TileType::sBoulderInPit: return 0xafa293;
			case TileType::sBatOne:
			case TileType::sBatTwo: return 0x82666e;
			case TileType::sOpenedChest:
			case TileType::sClosedChest: return 0xffff00;
			case TileType::sBowl: return Color::Yellow;
			case TileType::sAltar: return Color::White;
			case TileType::sGhostOne:
			case TileType::sGhostTwo: return Color::White;
			default: return wallTint;
		}

	return Color::White;
}

void Level::AddEntity(Entity *e)
{
	entitiesToAdd.push_back(e);
}

void Level::RemoveEntity(Entity *e)
{
	entitiesToRemove.push_back(e);
}

list<PhysicalBody*> Level::GetPhysicalBodiesInRadius(Vector2 center, 
	double radius, bool includeBlocks, bool includeEntities)
{
	list<PhysicalBody*> result;

	// Blocks
	if (includeBlocks)
		for (int x = int(center.x - radius); x <= int(center.x + radius); ++x)
			for (int y = int(center.y - radius); y <= int(center.y + radius); ++y)
			{
				Block *b = GetBlock(x, y);
				if (!b) continue;

				bool isHollow = dynamic_cast<HollowBlock*>(b) != 0;
				
				if (!isHollow)
					result.push_back(b);
			}

	// Entities
	if (includeEntities)
	{
		list<Entity*>::iterator it;
		for (it = entities.begin(); it != entities.end(); ++it)
		{
			Entity *e = *it;

			double d = fabs(e->position.x - center.x) + fabs(e->position.y - center.y);
			if (d <= radius)
				result.push_back(e);
		}
	}

	return result;
}

void Level::SwitchLevel(int id)
{

}

void Level::FindSpawnPosition(int id, Vector2 &position)
{
	list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		Entity *e = *it;

		if (dynamic_cast<LadderEntity*>((e)))
			if (e->id == id)
			{
				position = e->position;
				return;
			}
	}
}

void Level::GetLoot(int id)
{
	if (id == 20) core->GetLoot(ItemType::Pistol);
	if (id == 21) core->GetLoot(ItemType::Potion);
}
