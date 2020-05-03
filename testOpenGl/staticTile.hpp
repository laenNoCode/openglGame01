#pragma once
#include "util.hpp"
#include "tileTexture.hpp"
#include "camera2D.hpp"

class staticTile
{
private:
	std::string name = "StaticTileDefaultName";
	Camera2D* cam;
	tileTexture*    text;
	int           x     ;
	int           y     ;
	int           width ;
	int           height;
	float             cx;
	float             cy;
	float         cwidth;
	float        cheight;
	unsigned int camShot;

	float cx2;
	float cy2;
	bool shouldRender = true;
public:
	staticTile(Camera2D* cam, tileTexture* tex, int x, int y, int width, int height, std::string name);
	void putInArray(float* array, int index, int padding);
	void putInIndex(unsigned int* array, int index, int startingIndex);
	void computeAll(bool force = false);
	bool getShouldRender();
	staticTile();
	~staticTile();
};

