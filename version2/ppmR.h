#ifndef PPM_H
#define PPM_H

#include <math.h>
#include "color.h"

using namespace std;

class ppmR  {

	public:
		ppmR(int w, int h) : width(w), height(h) {}

	    void writePixel(ostream& out, int x, int y, color cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;

	public:
		int width;
		int height;
};

void ppmR::writePixel(ostream& out, int x, int y, color cOut) const {

 	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl; 
 		
}

void ppmR::writeNewLine(ostream& out) const {
 	out << "\n"; 
 }

void ppmR::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
 }

#endif


