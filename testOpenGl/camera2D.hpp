#pragma once
class Camera2D
{
private:
	int x;
	int y;
	int width;
	int height;
	unsigned int shot;
public:
	Camera2D(int x, int y, int width, int height);
	Camera2D();
	int getX     ();
	int getY     ();
	int getWidth ();
	int getHeight();
	void setX(int newX);
	void setY(int newY);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setPosition(int newPosition);

	unsigned int getCurrentShot();
	~Camera2D();
};

