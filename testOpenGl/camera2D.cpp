#include "camera2D.hpp"



Camera2D::Camera2D(int x, int y, int width, int height)
{
	this->x      = x;
	this->y      = y;
	this->width  = width;
	this->height = height;
	this->shot   = 0;
}

Camera2D::Camera2D()
{
}

int Camera2D::getY()
{
	return y;
}

int Camera2D::getWidth()
{
	return width;
}

int Camera2D::getHeight()
{
	return height;
}

void Camera2D::setX(int newX)
{
	if (this->x != newX) {
		this->x = newX;
		(this->shot)++;
	}
}

void Camera2D::setY(int newY)
{
	if (this->y != newY) {
		this->y =  newY;
		(this->shot)++;
	}
}

void Camera2D::setWidth(int newWidth)
{
	if (this->width != newWidth) {
		this->width  = newWidth;
		(this->shot)++;
	}
}

void Camera2D::setHeight(int newHeight)
{
	if (this->height != newHeight) {
		this->height  = newHeight;
		(this->shot)++;
	}
}

unsigned int Camera2D::getCurrentShot()
{
	return this->shot;
}

int Camera2D::getX()
{
	return x;
}





Camera2D::~Camera2D()
{
}
