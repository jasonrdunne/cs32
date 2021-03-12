#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"
#include "shape.h"
#include <algorithm>

/* simple data representation of an implicit ellipse */
class Polygon : public shape {
  public:

	Polygon(vec2 v1, double d, color C) : shape{C,d} {
		theVerts.push_back(v1);
	}

	bool eval(double x, double y) override;
	void addVert(vec2 inV) { theVerts.push_back(inV); }
	bool concave();

	void validate() override
	{
		try{
			try{
				for (auto a : theVerts){
					if (a.x() < 0 || (a.y() < 0)) {
						throw std::out_of_range("polygon vert less zero");
					}
				}
			}
			catch(const std::out_of_range & e){
				std::cout << e.what() << std::endl;
				this->inC = color(0,0,0);
			}
		if (this->concave()){
			throw std::out_of_range("polygon concave");
		}
	}
	catch(const std::out_of_range & e) {
		std::cout << e.what() << std::endl;
		vec2 temp = theVerts.back();
		while (theVerts.size() > 2)
		{
			theVerts.pop_back();
		}
		theVerts.push_back(temp);
		this->inC = color(255,0,0);
	}
	}
  private:
	std::vector<vec2> theVerts;

};

#endif
