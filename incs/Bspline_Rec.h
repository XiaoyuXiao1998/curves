#if !defined(BSPLINE_REC_H)
#define BSPLINE_REC_H

#include "Curve.h"

// The basic Bezier2 class.  Note that levelofdetail means differently here. 
//  draw the curve by repeated subdivision.

class Bspline_Rec : public Curve  
{
public:
	void draw(int levelOfDetail);
	Bspline_Rec() {};
	virtual ~Bspline_Rec() {};

};

#endif
