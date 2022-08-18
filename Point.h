#pragma once


#include "config.h"
#include "Color.h"
#include <iostream>


class Point {
	int x=0;//default values
	int y=0;

public:
	Point(){}
	Point(int _x, int _y) {x = _x, y = _y; }
	int getX() const;//return current x
	int getY() const;//return current y
	void setX(int _x);//initalize x
	void setY(int _y);//initalize y
	void increaseY(); //increase y by 1
	void decreaseY();//decrease y by 1
	void increaseX(); // increase x by 1
	void decreaseX();//decrease x by 1
};
