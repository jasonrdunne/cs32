#ifndef FACE_H
#define FACE_H
#include "implicit2D.h"

class face {
public:
	face(Implicit2D head, Implicit2D lEye, Implicit2D rEye, Implicit2D mouth) : head(head), lEye(lEye), rEye(rEye), mouth(mouth) {}

	//return the color of the top most ellipse or the background color
	color eval(int x, int y, color background) {
		float res;
		color inC;
		bool inTrue = false;
		double curDepth = -1.0;
		//evaluate the head
		
		res = head.eval(x, y);
		if (res < 0 && head.getDepth() > curDepth) {
			inC = head.getInC();
			inTrue = true;
			curDepth = head.getDepth();
		}

		res = lEye.eval(x, y);
		if (res < 0 && lEye.getDepth() > curDepth) {
			inC = lEye.getInC();
			inTrue = true;
			curDepth = lEye.getDepth();
		}

		res = rEye.eval(x, y);
		if (res < 0 && rEye.getDepth() > curDepth) {
			inC = rEye.getInC();
			inTrue = true;
			curDepth = rEye.getDepth();
		}
		res = mouth.eval(x, y);
		if (res < 0 && mouth.getDepth() > curDepth) {
			inC = mouth.getInC();
			inTrue = true;
			curDepth = mouth.getDepth();
		}

		if (inTrue) {			
			return inC;
		}
		else
			return background;
	}

	Implicit2D gethead() { return head; }
private:
	Implicit2D head;
	Implicit2D lEye, rEye;
	Implicit2D mouth;
};

#endif