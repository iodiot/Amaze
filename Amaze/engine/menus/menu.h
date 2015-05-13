#ifndef MENU_H
#define MENU_H

#include "item.h"
#include "drawer.h"

class Core;

class Menu
{
protected:
	Core *core;

	static const uint cHighlight = 0xffff80;
	static const uint cDefault = 0xa0a0a0;

public:
	Menu(Core *core);

	virtual void Tick();
	virtual void Draw(Drawer *drawer);
};

class PauseMenu : public Menu
{
private:
	int selected;

public:
	PauseMenu(Core *core);

	virtual void Tick();
	virtual void Draw(Drawer *drawer);
};

class GotLootMenu : public Menu
{
private:
	ItemType::e item;
	int continueDelay;

public:
	GotLootMenu(Core *core, ItemType::e item);

	virtual void Tick();
	virtual void Draw(Drawer *drawer);
};

#endif