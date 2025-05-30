#include <iostream>
#include "./Array.hpp"

int main() {

	Array<int> a(5);
	for (size_t i = 0; i < a.size(); ++i)
		a[i] = i * 10;

	std::cout << "Array elements: ";
	for (size_t i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << std::endl;

	Array<int> b = a;
	b[0] = 999;
	std::cout << "Original array first element: " << a[0] << std::endl;
	std::cout << "Copied array first element: " << b[0] << std::endl;

	Array<int> c;
	c = a;
	c[1] = 888;
	std::cout << "Original array second element: " << a[1] << std::endl;
	std::cout << "Assigned array second element: " << c[1] << std::endl;
	
	try {
		std::cout << "Trying out-of-bounds access..." << std::endl;
		std::cout << a[10] << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
