#include <iostream>
#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main( void ) {

	Point const a(0, 0);
	Point const b(5, 0);
	Point const c(0, 5);
	Point const point(2, 2);

	if (bsp(a, b, c, point))
		std::cout << "Point is in the triangle" << std::endl;
	else
		std::cout << "Point is not in the triangle" << std::endl;

	return 0;
}