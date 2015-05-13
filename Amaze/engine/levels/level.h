#ifndef LEVEL_H
#define LEVEL_H

#include "art.h"
#include "geometry.h"

class Core;
class Block;
class Entity;
class PhysicalBody;

struct LevelType
{
	enum e
	{
		None,
		Start,
		Dungeon,
		Overworld,
		Ice,
		Crypt,
		Temple
	};
};

class Level
{
protected:
	Core *core;
	Block **map;
	list<Entity*> entitiesToAdd, entitiesToRemove;

public:
	// Colors (format: bgr)
	static const uint cMagicPink	= 0xff00ff;
	static const uint cBlock			= 0xffffff;
	static const uint cEmpty			= 0x000000;
	static const uint cSpawnPoint = 0x00ffff;
	static const uint cBrokenWall = 0xffff00;
	static const uint cBat				= 0x0000ff;
	static const uint cJail				= 0x4c4c4c;
	static const uint cTorch			= 0x023aff;
	static const uint cLadderDown	= 0x9e009e;
	static const uint cLadderUp		= 0xff66ff;
	static const uint cGrassWall  = 0x9bff93;
	static const uint cFootPath		= 0x003a65;
	static const uint cDoor				= 0xc6c6c6;
	static const uint cBoulder		= 0x0055aa;
	static const uint cChest			= 0x64ffff;
	static const uint cPit				= 0x009300;
	static const uint cLoot				= 0x4dc1c1;
	static const uint cWater			= 0xff0000;
	static const uint cIceOne			= 0x0500ff;
	static const uint cIceTwo			= 0x603f3f;
	static const uint cPressurePlate = 0x809300;
	static const uint cSwitch			= 0xa7ff00;
	static const uint cAltar			= 0x02baff;
	static const uint cGhost			= 0x0600ff;

	int width, height;
	Vector2 startSpawnPosition;

	list<Entity*> entities;

	bool isLoaded;

	// Outlook
	TileType::e defaultFloor, defaultCeil;
	uint floorTint, wallTint;
	bool hasSkybox;

	char shortName[0xff], fullName[0xff];

private:
	void LoadBlocks(const uint *colors);
	void LoadEntities(const uint *colors);

	static void FloodFill(uint *colors, int x, int y, int width, int height, int emptyColor, int fillColor);

public:
	Level(Core *core);
	~Level();

	void Load();

	virtual void Tick();

	virtual uint GetTileTint(TexType::e tex, TileType::e tile);

	Block* GetBlock(int x, int y);

	list<PhysicalBody*> GetPhysicalBodiesInRadius(Vector2 center, 
		double radius, bool includeBlocks = true, bool includeEntities = true);

	void AddEntity(Entity *e);
	void RemoveEntity(Entity *e);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);

	void FindSpawnPosition(int id, Vector2 &position);
};

// Start level
class StartLevel : public Level
{
public:
	StartLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

// Overworld level
class OverworldLevel : public Level
{
public:
	OverworldLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

// Dungeon level
class DungeonLevel : public Level
{
public:
	DungeonLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

// Ice level
class IceLevel : public Level
{
public:
	IceLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

// Crypt level
class CryptLevel : public Level
{
public:
	CryptLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

// Temple level
class TempleLevel : public Level
{
public:
	TempleLevel(Core *core);

	virtual void SwitchLevel(int id);
	virtual void GetLoot(int id);
};

#endif