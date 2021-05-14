#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include<glad/glad.h>
#include "Point.h"
#include<iostream>


#define vector std::vector  
typedef vector<Point> Pvector;



class Curve
{
protected:
	Pvector points;
	Pvector::iterator activePoint;
	bool isactive;

public:
	Curve();
	virtual ~Curve();
	virtual void draw(int levelOfDetail);
	void addPoint(float x, float y);
	void deleteActivePoint();
	void moveActivePoint(float dx, float dy);
	void updateActivePoint(float x, float y);
	void connectTheDots();
	void drawLine(float x1, float y1, float x2, float y2);
	bool getactive() {
		return isactive;
	}
};

#endif
