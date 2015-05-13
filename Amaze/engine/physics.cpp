#include "stdafx.h"

#include "all_in_one.h"

namespace Physics 
{
	void MoveEntities(Level *level)
	{
		static const double eventHorizon = 1;
		static const double lookAhead = 0.3;

		list<Entity*>::iterator it;
		for (it = level->entities.begin(); it != level->entities.end(); ++it) 
		{
			Entity *entity = *it;

			if (entity->ignoresPhysics) continue;

			Block *currentBlock = level->GetBlock(int(entity->position.x), int(entity->position.y));
			if (!currentBlock) continue;

			entity->velocity += entity->acceleration - entity->velocity * currentBlock->GetFriction(entity);
			entity->SetCenterHeight(currentBlock->GetFloorHeight() + 0.5);
			if (entity->velocity.IsZero()) continue;

			list<PhysicalBody*> bodies = level->GetPhysicalBodiesInRadius(entity->position, eventHorizon);
			Vector2 nv = entity->velocity; //.Normalized() * lookAhead;

			// Collision detection
			list<PhysicalBody*>::iterator jt;
			for (jt = bodies.begin(); jt != bodies.end(); ++jt)
			{
				PhysicalBody *body = *jt;

				if (body == entity || !body->Blocks(entity)) continue;

				Rect rect = entity->GetBoundingRect();
				if (rect.Intersects(body->GetBoundingRect())) continue;
				rect.x += nv.x;
				rect.y += nv.y;

				if (rect.Intersects(body->GetBoundingRect()))
				{
					entity->Collide(body);
					body->Collide(entity);

					rect = entity->GetBoundingRect();
					rect.x += nv.x;
					if (rect.Intersects(body->GetBoundingRect()))
						entity->velocity.x = 0;

					rect = entity->GetBoundingRect();
					rect.y += nv.y;
					if (rect.Intersects(body->GetBoundingRect()))
						entity->velocity.y = 0;
				}

				if (entity->velocity.IsZero())
					break;
			}

			entity->position += entity->velocity;
		}
	}
}