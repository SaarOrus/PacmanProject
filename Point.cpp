#include "Point.h"

void Point::setX(int _x) {
	x = _x;
}

void Point::setY(int _y) {
	y = _y;
}

int Point::getX() const
{
	int curX = x;
	return curX;
}

int Point::getY() const
{
	int curY = y;
	return curY;
}

void Point::increaseY()
{
	setY(++y);
}

void Point::decreaseY()
{
	setY(--y);
}

void Point::increaseX()
{
	setX(++x);
}

void Point::decreaseX()
{
	setX(--x);
}