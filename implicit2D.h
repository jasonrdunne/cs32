#ifndef IMPL2D_H
#define IMPL2D_H
#include "vec2.h"
#include "shape.h"

/* simple data representation of an implicit ellipse - derived from shape */
class Implicit2D : public shape {
  public:
	Implicit2D(double cX, double cY, double r1, double r2, color C) : shape{C, 0},
		center(cX, cY), radii(r1, r2) {}
	Implicit2D(double cX, double cY, double r1, double r2, double d, color C) : shape{C, d}, 
		center(cX, cY), radii(r1, r2) {}
	Implicit2D(vec2 inC, double r1, double r2, color C) : shape{C, 0},
		center(inC), radii(r1, r2) {}

	 bool eval(double x, double y) override {
		return ( (((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) + 
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f)  < 0);
	}
	void translate(vec2 offset) {
		center += offset;
	}

	double getMaxR() {return fmax(radii.x(), radii.y());}
	vec2 getCent() const {return center; }

	void validate() override {
		try {
			try {
				if((center.x() < 0) || (center.y() < 0))
				{
					throw std::out_of_range("ellipse center less zero");
				}
			}
			catch(const std::out_of_range & e)
			{
				std::cout << e.what() << std::endl;
				this->inC = color(0,0,0);
			}
			if ( (radii.x() == 0 || (radii.y() == 0)))
			{
				throw std::out_of_range("ellipse divide zero");
			}
		}
		catch(const std::out_of_range & e)
		{
			std::cout << e.what() << std::endl;
			if (radii.x() == 0) this->radii.setX(2);
			if (radii.y() == 0) this->radii.setY(2);
			this->inC = color(255,0,0);
		}

	}

  private:
	vec2 center;
	vec2 radii;
};

#endif
