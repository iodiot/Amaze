#ifndef ENTITY_H
#define ENTITY_H

#include "art.h"
#include "geometry.h"
#include "physical_body.h"

class Core;

class Entity : public PhysicalBody
{
protected:	
	double centerHeight;

public:
	TileType::e sprite;

	Vector2 acceleration;
	Vector2 velocity;	
	double rotation;
	bool flying;
	bool ignoresPhysics;

protected:
	Entity(Core *core, Vector2 position);

public:
	virtual void Tick();
	
	virtual double GetCenterHeight();
	virtual void SetCenterHeight(double centerHeight);
};

class Player : public Entity
{
public:
	int health;
	int bowls;
	int potions;
	int ammo;

	// Items and slots
	static const uint SlotsCount = 8;
	ItemType::e slots[SlotsCount];
	int selectedSlot;

private:
	double rotationAcceleration;
	double rotationSpeed;

	// Bobbing
	double bob;
	double bobPhase;
	double bobbing;	
	
	bool canUse;

	void UseSelectedItem();

public:
	Player(Core *core, Vector2 position);	

	virtual void Tick();

	void AddLoot(ItemType::e item);

	ItemType::e GetSelectedItem();
	virtual double GetCenterHeight();
};

class EnemyEntity : public Entity
{
protected:
	int health;

public:
	EnemyEntity(Core *core, Vector2 position);

	virtual void Tick();
	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

class GhostEntity : public EnemyEntity
{
public:
	GhostEntity(Core *core, Vector2 position);
};

class BatEntity : public Entity
{
private:
	int animAge;
	int actionAge;
public:
	BatEntity(Core *core, Vector2 position);	

	virtual void Tick();
};

class JailEntity : public Entity
{
private:
	bool cutted;

public:
	JailEntity(Core *core, Vector2 position);

	virtual void Tick();
	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

class TorchEntity : public Entity
{
private:
	void FindPlaceToAttach(Vector2 &p);
	bool IsSolidBlock(int x, int y);

public:
	TorchEntity(Core *core, Vector2 position);

	virtual void Tick();
};

class ParticleEntity : public Entity
{
private:
	int ttl;
	double centerAcceleration, centerVelocity;

public:
	ParticleEntity(Core *core, Vector2 position, double centerHeight);

	virtual void Tick();
};

class BoulderEntity : public Entity
{
private:
	bool inPit;

public:
	BoulderEntity(Core *core, Vector2 position);

	virtual void Tick();
	virtual bool Use(PhysicalBody *body, ItemType::e item);
	virtual void Collide(PhysicalBody *body);
};

class LadderEntity : public Entity
{
private:
	bool up;

public:
	LadderEntity(Core *core, Vector2 position, bool up);
	void Collide(PhysicalBody *body);
};

class ChestEntity : public Entity
{
private:
	bool opened;

public:
	ChestEntity(Core *core, Vector2 position);
	virtual bool Use(PhysicalBody *body, ItemType::e item);
};

class LootEntity : public Entity
{
public:
	LootEntity(Core *core, Vector2 position);
	void Collide(PhysicalBody *body);
};

class AltarEntity : public Entity
{
public:
	AltarEntity(Core *core, Vector2 position);
	void Collide(PhysicalBody *body);
};

#endif