#pragma once
#include "util.hpp"
#include "Texture.hpp"

class tileTexture
{
private:
	std::string name = "defaultTileTextureName";
	int xPos;
	int yPos;
	int width;
	int height;
	bool computed = false;
	Texture* father;
	float calculatedX;
	float calculatedY;
	float calculatedWidth;
	float calculatedHeight;
	void computeAll();
public:
	tileTexture();
	tileTexture(Texture* fatherTexture, int x, int y, int width, int height, std::string name);
	void putInArray(float* array, int index, int padding);
	void putInIndex(unsigned int* array, int index, int startingIndex);
	~tileTexture();
};

