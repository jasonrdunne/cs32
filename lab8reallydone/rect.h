#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep},
		upperL(lX, lY), lowerR(rX, rY) {}
	
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep},
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep},
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) override {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	void setColor(color col) { inC = color{0, 0, col.b()}; }

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

	void validate()
	{
		try{
			try{
				if (upperL.x() <= 0 || upperL.y() <= 0 || lowerR.x() <= 0 || lowerR.y() <= 0)
				{
					throw std::out_of_range("rect vert less zero");
				}
			}
			catch(const std::out_of_range & e)
			{
				std::cout << e.what() << std::endl;
				this->inC = color(0,0,0);
			}
			if (upperL.x() > lowerR.x() || upperL.y() > lowerR.y())
			{
				if (upperL.x() > lowerR.x())
				{
					double storage = upperL.x();
					upperL.setX(lowerR.x());
					lowerR.setX(storage);
				}
				if (upperL.y() > lowerR.y())
				{
					double storage = upperL.y();
					upperL.setY(lowerR.y());
					lowerR.setY(storage);
				}
				throw std::out_of_range("rect order incorrect");
			}
		}
		catch(const std::out_of_range & e)
		{
			std::cout << e.what() << std::endl;
			this->inC = color(255,0,0);
		}
	}

  private:
	vec2 upperL;
	vec2 lowerR;

};

#endif
