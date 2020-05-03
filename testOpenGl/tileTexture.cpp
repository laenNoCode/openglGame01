#include "tileTexture.hpp"



void tileTexture::computeAll()
{
	if (!computed) {
#ifdef DEBUG
		std::cout << "computing " << name.c_str()  << " x " << this->xPos  << " y " << this->yPos<< std::endl;
#endif // DEBUG
		this->calculatedX = (float)(this->xPos) / (float)(this->father->getWidth() );
		
		this->calculatedWidth  = (float)(this->width ) / (float)(this->father->getWidth() );
		this->calculatedHeight = (float)(this->height) / (float)(this->father->getHeight());
		this->calculatedY = 1.0 - (float)(this->yPos) / (float)(this->father->getHeight()) - this->calculatedHeight;
		this->computed = true;
	}
}




tileTexture::tileTexture()
{
}

tileTexture::tileTexture(Texture * fatherTexture, int x, int y, int width, int height, std::string name)
{
	this->father   = fatherTexture;
	this->xPos     = x;
	this->yPos     = y;
	this->width    = width;
	this->height   = height;
	this->computed = false;
	this->name     = name;
}

void tileTexture::putInArray(float* array, int index, int padding)
{
	this->computeAll();
	array[index + 0 * padding + 0] = this->calculatedX;
	array[index + 0 * padding + 1] = this->calculatedY;
	array[index + 1 * padding + 0] = this->calculatedX + this -> calculatedWidth;
	array[index + 1 * padding + 1] = this->calculatedY;
	array[index + 2 * padding + 0] = this->calculatedX;
	array[index + 2 * padding + 1] = this->calculatedY + this -> calculatedHeight;
	array[index + 3 * padding + 0] = this->calculatedX + this -> calculatedWidth ;
	array[index + 3 * padding + 1] = this->calculatedY + this -> calculatedHeight;
}

void tileTexture::putInIndex(unsigned int * array, int index, int startingIndex)
{
	array[index + 0] = startingIndex + 0;
	array[index + 1] = startingIndex + 1;
	array[index + 2] = startingIndex + 2;
	array[index + 3] = startingIndex + 2;
	array[index + 4] = startingIndex + 3;
	array[index + 5] = startingIndex + 1;
}


tileTexture::~tileTexture()
{
}
