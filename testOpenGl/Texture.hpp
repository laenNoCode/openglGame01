#pragma once
#include "util.hpp"
#include <iostream>
#include "extern/stb_image.hpp"
class Texture
{
private:
	unsigned int m_id;
	int mWidth, mHeight;
	int channelsInFile;
	std::string name;
public:
	Texture(const std::string& path, const std::string& name = "defaultTextureName");
	void bind(int slot);
	int getWidth();
	int getHeight();
	~Texture();
	static unsigned int channels[];
};

