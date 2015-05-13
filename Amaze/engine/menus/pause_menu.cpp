#include "stdafx.h"

#include "all_in_one.h"

PauseMenu::PauseMenu(Core *core) : Menu(core)
{
	selected = 0;
}

void PauseMenu::Tick()
{
	if (core->input->esc || (core->input->space && selected == 1))
	{
		core->input->esc = false;
		core->SetMenu(0);
		return;
	}

	if (core->input->up)
	{
		--selected;
		if (selected < 0)
			selected = 0;
	}

	if (core->input->down)
	{
		++selected;
		if (selected > 1)
			selected = 1;
	}
}

void PauseMenu::Draw(Drawer *drawer)
{
	SDL_Rect srs; 
	srs.x = srs.y = 0; 
	srs.h = 35;
	srs.w = core->art->logo->w;

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 5;

	drawer->Draw(core->art->logo, &srs, &dest);
	drawer->Draw("Abort game", drawer->width / 2 - 20, drawer->height / 2 - 5, selected == 0 ? Color::Yellow : Color::White);
	drawer->Draw("Continue", drawer->width / 2 - 20, drawer->height / 2 + 5, selected == 1 ? Color::Yellow : Color::White);
}