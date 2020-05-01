#pragma once
#include "util.h"
#include <iostream>
#include "extern/stb_image.h"
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

