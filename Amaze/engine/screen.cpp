#include "stdafx.h"

#include "all_in_one.h"

Screen::Screen(Core *core, SDL_Surface *screen)
{
	this->core = core;
	this->screen = screen;

	width = Consts::ScreenWidth / Consts::PixelSize;
	height = Consts::ScreenHeight / Consts::PixelSize;

	buffer = new uint[width * height];

	renderer = new Renderer(core, buffer, width, height - core->art->gamepanel->h);
	drawer = new Drawer(core, buffer, width, height);

	frameCounter = 0;
	frameRate = 0;
	previousTime = 0;
	elapsedTime = 0;

	strcpy(message, "");
	showMessageTime = 0;
}

Screen::~Screen()
{
	delete[] buffer;

	delete renderer;
	delete drawer;
}

void Screen::Draw()
{
	CalculateFps();

	// Reset screen buffer
	memset(buffer, 0, width * height * sizeof(uint));

	DrawSkybox();
	renderer->Render();
	DrawHud();

	if (core->menu)
		core->menu->Draw(drawer);

	// Debug
	sprintf(debug, "fps: %d", frameRate);
	drawer->Draw(debug, 10, 10, 0xffffff);

	if (showMessageTime)
	{
		drawer->Fill(0, 0, width, height - core->art->gamepanel->h, Color::Black);
		drawer->Draw(message, width / 2 - drawer->TextWidth(message) / 2, (height - core->art->gamepanel->h) / 2, 0xffff80);
		--showMessageTime;
	}

	BufferToScreen();
}

void Screen::DrawSkybox()
{
	if (!core->level->hasSkybox)
		return;

	double phi = phi = core->player->rotation / (2.0 * M_PI);

	SDL_Rect srs;
	srs.x = int(double(core->art->skybox->w) * phi) + core->ticks / 100; 
	srs.x %= core->art->skybox->w;
	srs.y = 0;
	srs.h = core->art->skybox->h;
	srs.w = width;

	drawer->Draw(core->art->skybox, &srs, 0, 0, Color::White, 2); 
}

void Screen::DrawHud()
{
	const int panelX = 0;
	const int panelY = height - core->art->gamepanel->h;

	char str[0xff];

	// Current weapon
	if (core->player->GetSelectedItem() != ItemType::None)
	{
		ItemType::e item = core->player->GetSelectedItem();
		int tile = int(ItemType::GetTile(item));
		uint tint = ItemType::GetTint(item);

		int shift = abs(int((core->player->GetCenterHeight() - 0.5) * 30.0));

		SDL_Rect srs;
		srs.x = tile * Consts::TileSize + 1;
		srs.y = (1 + core->input->space) * Consts::TileSize + 1;
		srs.w = srs.h = 16 - 1;
		drawer->Draw(core->art->items, &srs, width / 2, height / 2 - 14 + shift, tint, 3);	
	}

	// Gamepanel
	SDL_Rect dest; dest.x = panelX; dest.y = panelY;
	drawer->Draw(core->art->gamepanel, 0, &dest, 0x7f7f7f);

	// Keys
	sprintf(str, "%c", Drawer::Key);
	drawer->Draw(str, panelX + 3, panelY + 4, Color::Cyan);
	sprintf(str, "%d/4", 0);
	drawer->Draw(str, panelX + 10, panelY + 4);

	// Bowls
	sprintf(str, "%c", Drawer::Bowl);
	drawer->Draw(str, panelX + 3, panelY + 12, Color::Yellow);
	sprintf(str, "%d", core->player->bowls);
	drawer->Draw(str, panelX + 10, panelY + 12);

	// Health
	sprintf(str, "%c", Drawer::Heart);
	drawer->Draw(str, panelX + 3, panelY + 20, Color::Red);
	sprintf(str, "%d", core->player->health);
	drawer->Draw(str, panelX + 10, panelY + 20);

	// Slots with items
	for (int i = 0; i < Player::SlotsCount; ++i)
	{
		// Selected slot
		if (i == core->player->selectedSlot)
		{
			SDL_Rect srs;
			srs.x = 0; srs.y = 48;
			srs.w = srs.h = 16 + 1;
			drawer->Draw(core->art->items, &srs, panelX + 30 + 16 * i, panelY + 2);
		}

		if (core->player->slots[i] != ItemType::None)
		{
			ItemType::e item = core->player->slots[i];
			int tile = int(ItemType::GetTile(item));
			uint tint = ItemType::GetTint(item);

			drawer->Draw(core->art->items, tile, panelX + 30 + 16 * i, panelY + 2, tint);

			if (item == ItemType::Pistol)
			{
				sprintf(str, "%2d", core->player->ammo);
				drawer->Draw(str, panelX + 30 + 16 * i + 4, panelY + 10);
			}
			else if (item == ItemType::Potion)
			{
				sprintf(str, "%2d", core->player->potions);
				drawer->Draw(str, panelX + 30 + 16 * i + 4, panelY + 10);
			}
		}
	}

	// Weapon name
	drawer->Draw(ItemType::GetName(core->player->GetSelectedItem()), drawer->width / 2, drawer->height - 9);
}

void Screen::CalculateFps()
{
	++frameCounter;

	if (elapsedTime >= 1000)
	{
		frameRate = frameCounter;
		frameCounter = 0;
		elapsedTime = 0;
		previousTime = SDL_GetTicks();
	}
	else
	{
		int t = SDL_GetTicks();
		elapsedTime += t - previousTime;
		previousTime = t;
	}
}

void Screen::BufferToScreen()
{
	uint *pixels = (uint*)screen->pixels;

	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)	
		{
			uint c = buffer[x + y * width];

			// Big pixels
			int startX = x * Consts::PixelSize;
			int endX = startX + Consts::PixelSize;
			int startY = y * Consts::PixelSize;
			int endY = startY + Consts::PixelSize;

			for (int m = startX; m < endX; ++m)
				for (int n = startY; n < endY; ++n)
					pixels[m + n * screen->w] = c;
		}
}

void Screen::ShowMessage(const char *message, int showTime)
{
	strcpy(this->message, message);
	showMessageTime = showTime;
}