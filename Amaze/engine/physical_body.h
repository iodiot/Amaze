#ifndef PHYSICAL_BODY_H
#define PHYSICAL_BODY_H

#include "geometry.h"
#include "item.h"

class Core;

class PhysicalBody
{
protected:
	Core *core;
	bool blocksMotion;

public:
	double radius;
	Vector2 position;
	int id;

public:
	PhysicalBody(Core *core, Vector2 position);

	virtual bool Use(PhysicalBody *body, ItemType::e item);
	virtual void Collide(PhysicalBody *body);
	virtual bool Blocks(PhysicalBody *body);

	virtual Rect GetBoundingRect();
};

struct SortPhysicalBodies
{
	Vector2 center;
	bool reverseOrder;

	SortPhysicalBodies(Vector2 center, bool reverseOrder = false);

	bool operator()(const PhysicalBody *a, const PhysicalBody *b);
};

#endif