#ifndef FACE_H
#define FACE_H
#include "implicit2D.h"

class face {
public:
	face(Implicit2D head, Implicit2D lEye, Implicit2D rEye, Implicit2D mouth) {
		theShapes.push_back(head);
		theShapes.push_back(lEye);
		theShapes.push_back(rEye);
		theShapes.push_back(mouth);
	}

	//return the color of the top most ellipse or the background color
	color eval(int x, int y, color background) {
		float res;
		color inC;
		bool inTrue = false;
		double curDepth = -1.0;
		for (auto obj : theShapes) {
		  //evaluate the head
		  res = obj.eval(x, y);
		  if (res < 0 && obj.getDepth() > curDepth) {
			inC = obj.getInC();
			inTrue = true;
			curDepth = obj.getDepth();
		  }
		 }
		
		if (inTrue) {			
			return inC;
		}
		else
			return background;
	}

	Implicit2D gethead() { return theShapes.at(0); }
private:
	vector<Implicit2D> theShapes;
};

#endif