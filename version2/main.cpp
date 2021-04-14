/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "util.h"

using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
void writeOut(ostream& out, ppmR& theWriter, 
				vector<ellipse *> IEs, vector<Rect* > Rs) {

	float res;
	color inC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations (note 'front' determined by order in vector)
			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
			
			//uncomment this section when you've written rect.h
			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}
			
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	vector<ellipse*> theEllipses;
	vector<Rect*> theRects;

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}
	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	vector<color> niceC;
	niceC.push_back(color(117, 119, 186));
	niceC.push_back(color(45, 47, 135));
	niceC.push_back(color(174, 209, 238));
	niceC.push_back(color(239, 174, 115));
	niceC.push_back(color(186, 140, 117));
	
	for (int j=0; j < 400; j++) {
		theEllipses.push_back(new ellipse(vec2(nicerRand(10, sizeX-10), nicerRand(10, sizeX-10)), 
								vec2(nicerRand(11, 30), nicerRand(11, 30)), nicerRand(1, 20), niceC[nicerRand(0,5)]));	
	}

	for (int i=0; i < 400; i++) {
		theRects.push_back(new Rect(vec2(nicerRand(10, sizeX-10), nicerRand(10, sizeX-10)), 
				nicerRand(18, 43), nicerRand(15, 32), color(nicerRand(23, 210)), nicerRand(1, 20)));
	}

	outFile.open(argv[3]);
	if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theEllipses, theRects);
			outFile.close();
			outFilename.erase();
		 } else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
	}

}
