#include "stdafx.h"

#include "all_in_one.h"

Drawer::Drawer(Core *core, uint *buffer, int width, int height)
{
	this->core = core;
	this->buffer = buffer;
	this->width = width;
	this->height = height;
}

void Drawer::Draw(const SDL_Surface *surface, const SDL_Rect *srs, const SDL_Rect *dest, uint tint, int scale)
{
	const uint* pixels = (uint*) surface->pixels;

	if (!srs)
		srs = &surface->clip_rect;

	if (!dest)
		dest = &surface->clip_rect;

	for (int x = 0; x < srs->w; ++x)
		for (int y = 0; y < srs->h; ++y)	
		{
			int xx = (x + srs->x) % surface->w;
			int yy = (y + srs->y) % surface->h;

			uint c = Color::KillAlpha(pixels[xx + yy * surface->w]);
			if (c == Level::cMagicPink)
				continue;

			c = Color::FastChannelsMul(c, tint);

			int startX = dest->x + x * scale;
			int endX = startX + scale;
			int startY = dest->y + y * scale;
			int endY = startY + scale;

			for (int m = startX; m < endX && m < width; ++m)
				for (int n = startY; n < endY && n < height; ++n)
					buffer[m + n * width] = c;
		} 
}


void Drawer::Draw(const char *text, int x, int y, uint color)
{
	static const char chars[] = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?\"'/\\<>()[]{}"
		"abcdefghijklmnopqrstuvwxyz_               "
		"0123456789+-=*:;                          ";

	static const int rows = 3;
	static const int rowWidth = strlen(chars) / rows;

	int len = strlen(text);
	for (int i = 0; i < len; ++i)
	{
		int n = 0;

		// Special cases
		if (text[i] == Heart || text[i] == Bowl || text[i] == Key)
			n = strchr(chars, ';') - chars + text[i];
		else
			n = strchr(chars, text[i]) - chars;
	
		SDL_Rect srs;
		srs.x = (n % rowWidth) * Consts::CharWidth;
		srs.y = (n / rowWidth) * Consts::CharHeight;
		srs.w = Consts::CharWidth;
		srs.h = Consts::CharHeight;

		SDL_Rect dest;
		dest.x = x + i * Consts::CharWidth;
		dest.y = y;

		Draw(core->art->font, &srs, &dest, color);
	}
}

void Drawer::Draw(const SDL_Surface *surface, int tile, int x, int y, uint tint, int scale)
{
	SDL_Rect srs;
	srs.x = (tile * Consts::TileSize) % surface->w;
	srs.y = ((tile * Consts::TileSize) / surface->w) * Consts::TileSize;
	srs.w = srs.h = Consts::TileSize;

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	Draw(core->art->items, &srs, &dest, tint, scale);
}

void Drawer::Draw(const SDL_Surface *surface, const SDL_Rect *srs, int x, int y, uint tint, int scale)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	Draw(surface, srs, &dest, tint, scale);
}

int Drawer::TextWidth(const char *text)
{
	return strlen(text) * Consts::CharWidth;
}

void Drawer::Fill(int x, int y, int width, int height, uint color)
{
	Color fillColor(color);

	for (int i = x; i < width; ++i)
		for (int j = y; j < height; ++j)
		{
			Color bufferColor(buffer[i + j * this->width]);

			bufferColor.r = fillColor.r + ((fillColor.a * (bufferColor.r - fillColor.r)) >> 8);
			bufferColor.g = fillColor.g + ((fillColor.a * (bufferColor.g - fillColor.g)) >> 8);
			bufferColor.b = fillColor.b + ((fillColor.a * (bufferColor.b - fillColor.b)) >> 8);
			bufferColor.a = 0xff;

			buffer[i + j * this->width] = bufferColor.ToHex();
		}
}

void Drawer::Fill(uint color)
{
	Fill(0, 0, width, height, color);
}
