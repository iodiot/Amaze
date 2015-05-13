#ifndef BLOCK_H
#define BLOCK_H

#include "art.h"
#include "physical_body.h"

class Core;

class Block : public PhysicalBody
{
public:
	TileType::e wall, floor, ceil;

public:
	Block(Core *core, Vector2 position);

	virtual void Tick();
	
	virtual double GetFloorHeight();
	virtual double GetFriction(Entity *entity);
};

class HollowBlock : public Block
{
public:
	HollowBlock(Core *core, Vector2 position, TileType::e floor = TileType::None, TileType::e ceil = TileType::None);
};

class SolidBlock : public Block
{
public:
	SolidBlock(Core *core, Vector2 position, TileType::e wall);
};

class BrokenBlock : public Block
{
private:
	bool broken;

public:
	BrokenBlock(Core *core, Vector2 position);

	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

class DoorBlock : public Block
{
public:
	double openess;
	bool open;

public:
	DoorBlock(Core *core, Vector2 position);

	virtual void Tick();
	virtual Rect GetBoundingRect();
	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

class PitBlock : public Block
{
private:
	bool empty;

public:
	PitBlock(Core *core, Vector2 position);

	virtual void Collide(PhysicalBody *body);
};

class WaterBlock : public Block
{
public:
	WaterBlock(Core *core, Vector2 position);

	virtual void Tick();
	virtual bool Blocks(PhysicalBody *body);

	virtual double GetFloorHeight();
	virtual double GetFriction(Entity *entity);
};

class IceBlock : public Block
{
public:
	IceBlock(Core *core, Vector2 position);

	virtual double GetFriction(Entity *entity);
};

class PressurePlateBlock : public Block
{
private:
	bool pressed;

public:
	PressurePlateBlock(Core *core, Vector2 position);

	virtual void Tick();

	virtual double GetFloorHeight();
};

// Switch block
class SwitchBlock : public Block
{
private:
	bool pressed;

public:
	SwitchBlock(Core *core, Vector2 position);

	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

#endif