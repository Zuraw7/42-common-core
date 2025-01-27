#include <iostream>
#include "Point.hpp"

float calc_area(Point const &p1, Point const &p2, Point const &p3);

/*
	A, B and C are vertices of the trianlge
	point is the point to check if it is in a triangle or not

	Solution:
	1. Calculate the area of the given triangle
	2. Split given triangle into smaller ones - t1, t2, t3
		a. t1 - a, b, point; t2 - a, point, c; t3 - point, b, c
		b. Calculate areas for smaller triangles.
		c. Sum areas of smaller triangles to the given one
		d. Point is in if the sum is equal to are of the big triangle
		e. If any of the areas are equal to 0, point is a vertex or on edge

*/
bool bsp (Point const a, Point const b, Point const c, Point const point) {

	float t = calc_area(a, b, c);
	float t1 = calc_area(a, b, point);
	float t2 = calc_area(a, point, c);
	float t3 = calc_area(point, b, c);
	float tsum = t1 + t2 + t3;

	std::cout << "t: " << t << std::endl;
	std::cout << "t1: " << t1 << std::endl;
	std::cout << "t2: " << t2 << std::endl;
	std::cout << "t3: " << t3 << std::endl;
	if (t == tsum) {
		if (t1 == 0 || t2 == 0 || t3 == 0) {
			std::cout << "Point is a vertex or on edge" << std::endl;
			return false;
		}
		return true;
	}

	return false;
}

float calc_area(Point const &p1, Point const &p2, Point const &p3) {
	float area;
	Fixed p1x = p1.getX();
	Fixed p1y = p1.getY();
	Fixed p2x = p2.getX();
	Fixed p2y = p2.getY();
	Fixed p3x = p3.getX();
	Fixed p3y = p3.getY();

	area = ( p1x.toFloat() * (p2y.toFloat() - p3y.toFloat()) + 
			 p2x.toFloat() * (p3y.toFloat() - p1y.toFloat()) +
			 p3x.toFloat() * (p1y.toFloat() - p2y.toFloat())) * 0.5;
	if (area < 0)
		area *= -1;
	return area;
}
