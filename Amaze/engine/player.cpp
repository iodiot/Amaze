#include "stdafx.h"

#include "all_in_one.h"

Player::Player(Core *core, Vector2 position) : Entity(core, position)
{
	rotationAcceleration = 0;
	rotationSpeed = 0;

	bob = 0;
	bobPhase = 0;
	centerHeight = 0.5;

	radius = 0.3;
	rotation = 5;

	health = 20;
	bowls = 0;

	for (int i = 0; i < SlotsCount; ++i)
		slots[i] = ItemType::None;
	selectedSlot = -1;

	canUse = true;

	potions = 0;
	ammo = 0;
}

void Player::Tick()
{
	static const double effort = 0.03;
	static const double rotationEffort = 0.02;
	static const double rotationFriction = 0.25;
	static const double eps = 0.000001;

	// View bobbing
	bob *= 0.6;
	bob += velocity.Length() * 2 + 0.1;
	bobPhase += (velocity.Length() * 15 + 0.5);
	bobbing = sin(bobPhase * 0.1) * 0.1 * bob + 0.1 * bob;

	// Acceleration from inputs
	acceleration = Vector2();
	if (core->input->up && !core->input->down) acceleration += Vector2(cos(rotation), sin(rotation));
	if (core->input->down && !core->input->up) acceleration -= Vector2(cos(rotation), sin(rotation));
	if (core->input->right && !core->input->left) acceleration += Vector2(-sin(rotation), cos(rotation));
	if (core->input->left && !core->input->right) acceleration += Vector2(sin(rotation), -cos(rotation));

	acceleration.Normalize(effort);

	// Rotation
	rotationAcceleration = 0;
	if (core->input->turnLeft) rotationAcceleration = -rotationEffort;
	if (core->input->turnRight) rotationAcceleration = rotationEffort;

	rotationSpeed += rotationAcceleration - rotationSpeed * rotationFriction;
	if (fabs(rotationSpeed) < eps) 
		rotationSpeed = 0;
	else 
	{
		rotation += rotationSpeed;
		if (rotation < 0) rotation = 2 * M_PI + rotation;
		if (rotation > 2 * M_PI) rotation = rotation - 2 * M_PI;
	}

	// Use bodies before
	if (!core->input->space)
		canUse = true;
	if (core->input->space && canUse)
	{
		canUse = false;

		UseSelectedItem();

		static const double minDot = 0.5;
		static const double effectiveRange = 1.5;

		list<PhysicalBody*> bodies = core->level->GetPhysicalBodiesInRadius(position, effectiveRange);
		bodies.sort(SortPhysicalBodies(position));

		Vector2 playerDirection = Vector2(cos(rotation), sin(rotation)).Normalized();

		list<PhysicalBody*>::iterator it;
		for (it = bodies.begin(); it != bodies.end(); ++it)
		{
			PhysicalBody *body = *it;

			Vector2 bodyDirection = (body->position - position).Normalized();
			double dot = playerDirection.Dot(bodyDirection);
			if (dot >= minDot)
				if (body->Use(this, selectedSlot >= 0 ? slots[selectedSlot] : ItemType::None))
					break;
		}
	}

	// Selected slot
	for (int i = 0; i < SlotsCount; ++i)
		if (core->input->digits[i])
		{
			selectedSlot = i;
			break;
		}
}

void Player::AddLoot(ItemType::e item)
{
	if (item == ItemType::Pistol)
		ammo += 20;
	else if (item == ItemType::Potion)
		++potions;

	// Slot with such item exists?
	for (int i = 0; i < SlotsCount; ++i)
		if (slots[i] == item)
		{
			selectedSlot = i;
			return;
		}

	// Find free slot
	for (int i = 0; i < SlotsCount; ++i)
		if (slots[i] == ItemType::None)
		{
			slots[i] = item;
			selectedSlot = i;
			return;
		}
}

ItemType::e Player::GetSelectedItem()
{
	return selectedSlot >= 0 ? slots[selectedSlot] : ItemType::None;
}

double Player::GetCenterHeight()
{
	return centerHeight + bobbing;
}

void Player::UseSelectedItem()
{
	ItemType::e item = GetSelectedItem();

	if (item == ItemType::Pistol)
	{
		--ammo;
		if (!ammo)
			slots[selectedSlot] = ItemType::None;
	}
	else if (item == ItemType::Potion)
	{
		health += 10;
		--potions;
		if (!potions)
			slots[selectedSlot] = ItemType::None;
	}
}