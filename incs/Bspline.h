#if !defined(BSPLINE_H)
#define BSPLINE_H

#include "Curve.h"

// The basic B-spline class

class Bspline : public Curve  
{
protected:
        void drawSegment(Pvector::iterator p1, Pvector::iterator p2, Pvector::iterator p3, Pvector::iterator p4, int levelOfDetail);

public:
	void draw(int levelOfDetail);
	Bspline() {};
	virtual ~Bspline() {};

};

#endif 
