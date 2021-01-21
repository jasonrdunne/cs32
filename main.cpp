/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "implicit2D.h"
#include "face.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

void writeOut(ostream& out, ppmR& theWriter, 
				vector<shared_ptr<Implicit2D>> IEs, vector<shared_ptr<Rect>> Rs,
				face theFace) {

	float res;
	color inC;
	color drawC;
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
			/* compare my ret.h with yours */
			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}

			//naive draw that 'always' draws face (next modify to return fragment)
			//only overwrite if not background
			drawC = theFace.eval(x, y, background);
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
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

	vector<color> niceC;
	niceC.push_back(color(91, 49, 245));
	niceC.push_back(color(91, 212,199));
	niceC.push_back(color(182, 235, 113));
	niceC.push_back(color(212, 169,91));
	niceC.push_back(color(247, 106, 120));

	// create all the equations for a simple asci face
	// layer values larger is closer - ie on top
	vector<shared_ptr<Implicit2D>> theEllipses;
	theEllipses.push_back(make_shared<Implicit2D>(150, 180, 60, 80, 2, niceC[1]));	
	theEllipses.push_back(make_shared<Implicit2D>(130, 140, 10, 23, 3, niceC[2]));
	theEllipses.push_back(make_shared<Implicit2D>(130, 145, 4, 4, 4, color(128)));
	theEllipses.push_back(make_shared<Implicit2D>(160, 140, 10, 23, 3, niceC[2]));
	theEllipses.push_back(make_shared<Implicit2D>(160, 145,4, 4, 4, color(128)));
	theEllipses.push_back(make_shared<Implicit2D>(150, 210, 40, 20, 3, color(0)));

	//collection of rectangles (empty in base)
	vector<shared_ptr<Rect>> theRects;
	theRects.push_back(make_shared<Rect>(vec2(120, 10), 60, 110, niceC[1], 7));
	theRects.push_back(make_shared<Rect>(vec2(115, 10), 10, 110, niceC[4], 8));
	theRects.push_back(make_shared<Rect>(vec2(175, 10), 10, 110, niceC[4], 8));
	theRects.push_back(make_shared<Rect>(vec2(90, 120), 120, 20, niceC[0], 7));


	face theFace(Implicit2D(15, 18, 6, 8, 2, niceC[4]), Implicit2D(13, 14, 1, 2, 3, niceC[2]),
		Implicit2D(16, 14, 1, 2, 3, niceC[2]), Implicit2D(15, 21, 4, 2, 3, color(0)));

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);
		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theEllipses, theRects, theFace);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}

}
