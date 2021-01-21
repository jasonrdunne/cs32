#ifndef IMPL2D_H
#define IMPL2D_H
#include "vec2.h"

/* simple data representation of an implicit ellipse */
class Implicit2D {
  public:
	Implicit2D(double cX, double cY, double r1, double r2, color C) : 
		center(cX, cY), radii(r1, r2), inC(C), depth(0) {}
	Implicit2D(double cX, double cY, double r1, double r2, double d, color C) : 
		center(cX, cY), radii(r1, r2), inC(C), depth(d) {}
	Implicit2D(vec2 inC, double r1, double r2, color C) : 
		center(inC), radii(r1, r2), inC(C), depth(0) {}

	double eval(double x, double y) {
		return ( ((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) + 
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f);
	}
	color getInC() const {return inC; }
	double getDepth() const {return depth; }
  private:
	vec2 center;
	vec2 radii;
	color inC;
	double depth;
};

#endif