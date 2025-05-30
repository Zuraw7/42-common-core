#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T>
void print(T const &element) {
	std::cout << element << " ";
}

template<typename T>
void iter(T const *arr, size_t len, void (*f)(T const &)) {
	for (size_t i = 0; i < len; i++) {
		f(arr[i]);
	}
	std::cout << std::endl;
}

#endif