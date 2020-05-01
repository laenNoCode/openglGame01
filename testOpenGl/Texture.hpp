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
	
public:
	Texture(const std::string& path);
	void bind(int slot);
	~Texture();
	static unsigned int channels[];
};

