#ifndef POINT_H
#define POINT_H

// The basic Point Class.  
// ACTIVE_RADIUS is just how big we draw the points when active 
//    which is set to 0.15 in Point.cpp
// x and y are simply spatial locations 


class Point
{

public:
	static const float ACTIVE_RADIUS;
	float x;
	float y;
	
	bool active;

	void draw();
	Point(float xpos, float ypos);
	virtual ~Point();

};

#endif