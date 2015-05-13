#include "stdafx.h"

#include "all_in_one.h"

Renderer::Renderer(Core *core, uint *buffer, int width, int height)
{
	this->core = core;
	this->buffer = buffer;
	this->width = width;
	this->height = height;

	nearPlaneDistance = width * 0.5 / tan(Consts::Fov * 0.5);

	zBuffer = new double[width];
}

Renderer::~Renderer()
{
	delete[] zBuffer;
}

void Renderer::Render()
{
	// Reset zBuffer
	for (int i = 0; i < width; ++i)
		zBuffer[i] = DBL_MAX;

	// Set camera
	cameraPosition = core->player->position;
	cameraRotation = M_PI_2 - core->player->rotation;
	cameraShift = int((core->player->GetCenterHeight() - 0.5) * 50.0);

	RenderFloors();
	RenderWalls();
	RenderEntities();
}

void Renderer::RenderWalls()
{
	list<PhysicalBody*> bodies = core->level->GetPhysicalBodiesInRadius(cameraPosition, Consts::EventHorizon, true, false);
	bodies.sort(SortPhysicalBodies(cameraPosition));

	list<PhysicalBody*>::iterator  it;
	for (it = bodies.begin(); it != bodies.end(); ++it)
	{
		Block *block = (Block*) *it;
		if (!block || block->wall == TileType::None) continue;

		DoorBlock *door = dynamic_cast<DoorBlock*>(block);

		int x = int(block->position.x);
		int y = int(block->position.y);

		if (door)
		{
			if (core->level->GetBlock(x, y - 1)->wall == TileType::None)
			{
				double a = x - door->openess;
				double b = y + 0.3;

				RenderWall(Vector2(a, b + 0.2), Vector2(a + 1, b + 0.2), block->wall, 1, 0);
				RenderWall(Vector2(a + 1, b + 0.2), Vector2(a + 1, b), block->wall, 0.4, 0.6);
				RenderWall(Vector2(a + 1, b), Vector2(a, b), block->wall);
			}
			else
			{
				double a = x + 0.3;
				double b = y - door->openess;

				RenderWall(Vector2(a, b), Vector2(a, b + 1), block->wall, 1, 0);
				RenderWall(Vector2(a, b + 1), Vector2(a + 0.2, b + 1), block->wall, 0.4, 0.6);
				RenderWall(Vector2(a + 0.2, b + 1), Vector2(a + 0.2, b), block->wall);
			}
		} 
		else
		{
			RenderWall(Vector2(x + 1, y), Vector2(x, y), block->wall);
			RenderWall(Vector2(x + 1, y + 1), Vector2(x + 1, y), block->wall);
			RenderWall(Vector2(x, y + 1), Vector2(x + 1, y + 1), block->wall);
			RenderWall(Vector2(x, y), Vector2(x, y + 1), block->wall);
		}
	}
}

void Renderer::RenderFloors()
{
	static const double floorsDepthFactor = 0.46;

	const double rCos = cos(cameraRotation);
	const double rSin = sin(cameraRotation);

	for (int y = 0; y < height; ++y) 
	{
		bool floor = (y >= height / 2 + cameraShift);

		double zz = floorsDepthFactor * nearPlaneDistance / (y - height * 0.5 + 0.1 - cameraShift);
		if (!floor)
			zz *= -1.0;

		for (int x = 0; x < width; ++x)
		{
			// Unproject
			double xx = zz * (width * 0.5 - x) / nearPlaneDistance;

			Vector2 v;

			v.x = xx * rCos + zz * rSin + cameraPosition.x;
			v.y = - xx * rSin + zz * rCos + cameraPosition.y;

			Block *b = core->level->GetBlock(int(v.x), int(v.y));
			if (b == 0) continue;

			TileType::e tt = floor ? b->floor : b->ceil;
			if (tt == TileType::None) 
				tt = floor ? core->level->defaultFloor : core->level->defaultCeil;
			if (tt == TileType::None) continue;

			uint tint = core->level->GetTileTint(TexType::Floors, tt);

			int texX = int(v.x * double(Consts::TileSize)) % Consts::TileSize;
			int texY = int(v.y * double(Consts::TileSize)) % Consts::TileSize;

			PixelShader(buffer[x + y * width], GetTexel(core->art->floors, tt, texX, texY), fabs(zz), tint); 
		}
	}
}

void Renderer::PixelShader(uint &pixel, uint texColor, double depth, uint tint)
{
	// Is transparent?
	if (Color::KillAlpha(texColor) == Level::cMagicPink)
		return;

	Color finalColor(texColor);

	// Add some tint
	finalColor.FastChannelsMul(tint);

	// Fast fog
	const double fogStart = .2;
	const double fogEnd = 6;

	double fog = (depth - fogStart) / (fogEnd - fogStart);

	if (fog > 0)
	{
		if (fog > 1)
			fog = 1;

		fog = 1 - fog;

		finalColor.FastChannelsMul(fog);// - fog * (1 - fog) * core->NextDouble());
	}

	pixel = finalColor.ToHex();
}

void Renderer::RenderWall(Vector2 v1, Vector2 v2, TileType::e tile, double texCoord1, double texCoord2)
{
	if (tile == TileType::None) return;

	static const double zClip = 0.2;
	static const double eps = 0.000001;

	uint tint = core->level->GetTileTint(TexType::Walls, tile);

	// Obscure walls parallel to OX 
	bool side = fabs((v2 - v1).y) >= eps;
	if (!side) 
		tint = Color::FastChannelsMul(tint, 0.7);

	// Translate input vectors into view frame
	v1 -= cameraPosition;
	v2 -= cameraPosition;

	// Rotate input vectors
	v1.Rotate(cameraRotation);
	v2.Rotate(cameraRotation);

	double x1 = v1.x;
	double z1 = v1.y;
	double x2 = v2.x;
	double z2 = v2.y;

	// Near plane clipping
	if (z1 < zClip && z2 < zClip) return;

	if (z1 < zClip) {
		double p = (zClip - z1) / (z2 - z1);
		z1 = zClip;
		x1 = x1 + (x2 - x1) * p;
		texCoord1 = texCoord1 + (texCoord2 - texCoord1) * p;
	}

	if (z2 < zClip) {
		double p = (zClip - z1) / (z2 - z1);
		z2 = zClip;
		x2 = x1 + (x2 - x1) * p;
		texCoord2 = texCoord1 + (texCoord2 - texCoord1) * p;
	}

	// Projection
	int startX = width / 2 - int(nearPlaneDistance * x1 / z1);
	int endX = width / 2 - int(nearPlaneDistance * x2 / z2);

	if (startX >= endX) return;

	int lineHeight1 = int(fabs(double(height) / z1));
	int lineHeight2 = int(fabs(double(height) / z2));

	int dx = endX - startX;

	for (int x = max(0, startX); x < min(width, endX); ++x)
	{
		double d = double(x - startX) / double(dx);
		double texModifier = 1.0 / z1 + (1.0 / z2 - 1.0 / z1) * d;

		// Depth test
		double lineDepth = z1 + d * (z2 - z1); 
		if (zBuffer[x] > lineDepth)
			zBuffer[x] = lineDepth;
		else
			continue;
			
		// Interpolate line height
		int lineHeight = int(lineHeight1 + d * (lineHeight2 - lineHeight1));

		int startY = height / 2 - lineHeight / 2 + cameraShift;
		int endY = height / 2 + lineHeight / 2 + cameraShift;

		int dy = endY - startY;

		// Interpolate tex coord
		double texCoord = (texCoord1 / z1 +  d * (texCoord2 / z2 - texCoord1 / z1)) / texModifier;

		int texX = int(texCoord * double(Consts::TileSize));

		for (int y = max(0, startY); y < min(height, endY); ++y)
		{
			int texY = int(double(y - startY) / double(dy) * double(Consts::TileSize));

			PixelShader(buffer[x + y * width], GetTexel(core->art->walls, tile, texX, texY), lineDepth, tint); 
		}
	}
}

void Renderer::RenderEntities()
{
	static const double zClip = 0.2;

	list<PhysicalBody*> bodies = core->level->GetPhysicalBodiesInRadius(cameraPosition, Consts::EventHorizon, false, true);
	bodies.sort(SortPhysicalBodies(cameraPosition, true));

	list<PhysicalBody*>::iterator it;
	for (it = bodies.begin(); it != bodies.end(); ++it)
	{
		Entity *e = (Entity*)*it;
		if (e == core->player) continue;

		uint tint = core->level->GetTileTint(TexType::Sprites, e->sprite);

		Vector2 pos = e->position;
		pos -= cameraPosition;

		pos.Rotate(cameraRotation);

		// Near plane clipping
		if (pos.y < zClip)
			continue;

		// Projection
		int centerX = width / 2 - int(nearPlaneDistance * pos.x / pos.y);

		int halfSpriteSize = int(fabs(double(height) / pos.y)) / 2;

		int startX = centerX - halfSpriteSize;
		int endX = centerX + halfSpriteSize;

		int spriteShift = int((e->GetCenterHeight() - 0.5) * double(halfSpriteSize * 2.0));

		int startY = height / 2 - halfSpriteSize + cameraShift - spriteShift;
		int endY = height / 2 + halfSpriteSize + cameraShift - spriteShift;

		// Render
		for (int x = max(0, startX); x < min(width, endX); ++x)
		{
			// Depth test
			if (pos.y > zBuffer[x])
				continue;

			int texX = int(double(x - startX) / double(endX - startX) * double(Consts::TileSize));

			for (int y = max(0, startY); y < min(height, endY); ++y)
			{
				int texY = int(double(y - startY) / double(endY - startY) * double(Consts::TileSize));

				PixelShader(buffer[x + y * width], GetTexel(core->art->sprites, e->sprite, texX, texY), pos.y, tint);
			}
		}
	}
}

uint Renderer::GetTexel(const SDL_Surface *tex, int tile, int x, int y)
{
	const uint *pixels = (uint*) tex->pixels;

	return pixels[x + (tile * Consts::TileSize) % tex->w + (y + (tile * Consts::TileSize / tex->w) * Consts::TileSize) * tex->w];
}

