#pragma once
#include "util.hpp"
#include "VertexAndIndexBuffer.hpp"
#include "Texture.hpp"
#include "staticTile.hpp"
#include "camera2D.hpp"
#include "map.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
class staticTiledMap
{
	std::string name = "default";
	int width;
	int height;
	laen::map<staticTile> elements;
	laen::map<tileTexture> textures;
	int dataLength;
	int indexesLength;
	Texture* texture;
	Camera2D* cam;
	unsigned int camshot;
	VertexAndIndexBuffer* vaib;
	float* vertices;
	unsigned int* indexes;
	void readFromFile(std::ifstream& f, laen::map<Texture>& textures);
public:
	int getWidth ();
	int getHeight();
	void draw();
	Camera2D* getCamera();
	staticTiledMap(std::string path, laen::map<Texture>& textures);
	~staticTiledMap();
};

