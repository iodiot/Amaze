#include "stdafx.h"

#include "all_in_one.h"

GotLootMenu::GotLootMenu(Core *core, ItemType::e item) : Menu(core)
{
	this->item = item;
	continueDelay = 25;
}

void GotLootMenu::Tick()
{
	if (core->input->space && !continueDelay)
		core->SetMenu(0);
}

void GotLootMenu::Draw(Drawer *drawer)
{
	drawer->Fill(0x55000000);

	// Icon
 	drawer->Draw(core->art->items, int(ItemType::GetTile(item)), drawer->width / 2 - Consts::TileSize * 3 / 2, 1, ItemType::GetTint(item), 3);

	// Name
	char str[0xff];
	sprintf(str, "You found the %s!", ItemType::GetName(item));
	drawer->Draw(str, drawer->width / 2 - drawer->TextWidth(str) / 2 + 2, 50, cHighlight);

	// Description
	strcpy(str, ItemType::GetDescription(item));
	drawer->Draw(str, drawer->width / 2 - drawer->TextWidth(str) / 2, 60, cDefault);

	// Continue
	if (continueDelay > 0) --continueDelay;
	if (!continueDelay)
	{
		strcpy(str, "-> Continue");
		drawer->Draw(str, drawer->width / 2 - drawer->TextWidth(str) / 2 + 2, 80, cHighlight);
	}
}
