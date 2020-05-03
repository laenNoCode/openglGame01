#include "staticTile.hpp"



staticTile::staticTile(Camera2D* cam, tileTexture* tex, int x, int y, int width, int height, std::string name)
{
	this->cam     = cam;
	this->text    = tex;
	this->x       = x;
	this->y       = y;
	this->width   = width;
	this->height  = height;
	this->name    = name;
	this->computeAll(true);
}

void staticTile::putInArray(float * array, int index, int padding)
{
	this->text->putInArray(array, index+2, padding);
	array[index + 0 * padding + 0] = this->cx;
	array[index + 0 * padding + 1] = this->cy;
	array[index + 1 * padding + 0] = this->cx2;
	array[index + 1 * padding + 1] = this->cy;

	array[index + 2 * padding + 0] = this->cx;
	array[index + 2 * padding + 1] = this->cy2;

	array[index + 3 * padding + 0] = this->cx2;
	array[index + 3 * padding + 1] = this->cy2;

	
}

void staticTile::putInIndex(unsigned int * array, int index, int startingIndex)
{
	this->text->putInIndex(array, index , startingIndex);
}

void staticTile::computeAll(bool force)
{
	if (force||cam->getCurrentShot() != this->camShot)
	{
		this->cx = ((float)(this->x - this->cam->getX()) / (float)(this->cam->getWidth())) * 2.0f -1.0f;
		this->cy = ((float)(this->y - this->cam->getY()) / (float)(this->cam->getHeight())) * 2.0f -1.0f;
		//this->cy = (float)(this->y - this->cam->getY()) / (float)(this->cam->getHeight());
		this->cwidth = 2.0f*(float)(this->width) / (float)(this->cam->getWidth());
		this->cheight = 2.0f * (float)(this->height) / (float)(this->cam->getHeight());
		this->camShot = this->cam->getCurrentShot();
		this->cx2 = this->cx + this->cwidth;
		this->cy2 = this->cy + this->cheight;
		this ->shouldRender = ((cx <= 1.0 && cx >= -1.0) || (cy <= 1.0 && cy >= -1.0) || (cx2 <= 1.0 && cx2 >= -1.0) || (cy2 <= 1.0 && cy2 >= -1.0));
	}
}

bool staticTile::getShouldRender()
{
	this->computeAll();
	return shouldRender;
}

staticTile::staticTile()
{
}


staticTile::~staticTile()
{
}
