#include "Texture.hpp"


Texture::Texture(const std::string & path, const std::string& name)
{
	stbi_set_flip_vertically_on_load(1);
	this->name = name;
	unsigned char* imageData = stbi_load(path.c_str(), &mWidth, &mHeight, &channelsInFile, 4);
#ifdef DEBUG
	std::cout << "loaded file : " << path.c_str()  << " it has normally "<< channelsInFile << "," << mWidth << "," << mHeight << "," << sizeof(imageData) << std::endl;
#endif // DEBUG
	GLCall(glGenTextures(1, &(this->m_id)));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	stbi_image_free(imageData);
#if DEBUG
	std::cout << "created texture number " << m_id << std::endl;
#endif
}

void Texture::bind(int slot)
{
	if (channels[slot] != this->m_id) {
		GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		channels[slot] = this->m_id;
#ifdef DEBUG
		std::cout << "putting texture n°" << this->m_id << " in slot " << slot << std::endl;
#endif // DEBUG

	}
}

int Texture::getWidth()
{
	return this ->mWidth;
}

int Texture::getHeight()
{
	return this->mHeight;
}

Texture::~Texture()
{
#if DEBUG
	std::cout << "deleting texture number " << m_id << std::endl;
#endif
	glDeleteTextures(1, &m_id);
}






//initialization of mapped channel just to be sure, not really important piece of code
unsigned int Texture::channels[32] = { 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0 ,
0,0,0,0,0,0,0,0 ,
0,0,0,0,0,0,0,0 };
