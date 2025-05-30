#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <exception>

class NotFoundException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return ("error: Number not found");
		}
};

template <typename T>
typename T::iterator easyfind(T &container, int to_find) {
	typename T::iterator it;
	
	it = std::find(container.begin(), container.end(), to_find);

	if (it == container.end()) {
		throw NotFoundException();
	}

	return it;
}

#endif