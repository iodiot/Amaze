#ifndef RENDERER_H
#define RENDERER_H

#include "geometry.h"
#include "art.h"
#include "physical_body.h"

class Core;
class Entity;
class PhysicalBody;

class Renderer
{
private:
	Core *core;

	// Camera
	Vector2 cameraPosition;
	double cameraRotation;
	double nearPlaneDistance;
	int cameraShift;

	// Screen and buffers
	uint *buffer;
	double *zBuffer;
	int width;
	int height;

private:
	void RenderWall(Vector2 v1, Vector2 v2, TileType::e tile, double texCoord1 = 0, double texCoord2 = 1);
	void RenderWalls();
	void RenderFloors();
	void RenderEntities();

	void PixelShader(uint &pixel, uint texColor, double depth, uint tint);
	uint GetTexel(const SDL_Surface *tex, int tile, int x, int y);

public:
	Renderer(Core *core, uint *buffer, int width, int height);
	~Renderer();

	void Render();
};

#endif