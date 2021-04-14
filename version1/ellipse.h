#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <iostream>
#include "color.h"
#include "vec2.h"

/* simple data representation of an implicit ellipse */
class ellipse {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) :  
		center(cX, cY), radii(r1, r2), inC(C), depth(0) {}
	ellipse(vec2 inC, double r1, double r2, double d, color C) : 
		 center(inC), radii(r1, r2), inC(C), depth(d) {}
	ellipse(vec2 inC, vec2 inR, double d, color C) : 
		 center(inC), radii(inR), inC(C), depth(d) {}
	ellipse(double cX, double cY, double r1, double r2, double d, color C) : 
		center(cX, cY), radii(r1, r2), inC(C), depth(d) {}

	double eval(double x, double y) {
		return ( ((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) + 
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f);
	}

	color getInC() const {return inC; }
	double getDepth() const {return depth; }

  private:
	vec2 center; //center point of ellipse
	vec2 radii; //radii of the ellipse
	color inC;
	double depth;
};

#endif