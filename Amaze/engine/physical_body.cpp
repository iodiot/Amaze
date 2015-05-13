#include "stdafx.h"

#include "all_in_one.h"

PhysicalBody::PhysicalBody(Core *core, Vector2 position)
{
	this->core = core;
	this->position = position;

	radius = 0.5;

	blocksMotion = true;
}

Rect PhysicalBody::GetBoundingRect()
{
	return Rect(position.x - radius, position.y - radius, 2.0 * radius, 2.0 * radius);
}

bool PhysicalBody::Use(PhysicalBody *body, ItemType::e item)
{
	return false;
}

void PhysicalBody::Collide(PhysicalBody *body)
{

}

bool PhysicalBody::Blocks( PhysicalBody *body )
{
	return blocksMotion;
}

bool SortPhysicalBodies::operator()(const PhysicalBody* a, const PhysicalBody* b)
{ 
	// Distances from camera position
	double da = fabs(a->position.x - center.x) + fabs(a->position.y - center.y);
	double db = fabs(b->position.x - center.x) + fabs(b->position.y - center.y);

	return reverseOrder ? da > db : da <= db;
}

SortPhysicalBodies::SortPhysicalBodies(Vector2 center, bool reverseOrder)
{
	this->center = center;
	this->reverseOrder = reverseOrder;
}