#include "easyfind.hpp"

template <typename T> void autoFill(T &container);
void fillContainers(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1);
void printContainers(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1);
void executeEasyfind(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1);

int main (void) {

	std::vector<int>	v1(10);
	std::list<int>		l1(10);
	std::deque<int>		d1(10);

	// Filling containers with numbers ranging 0 to 9
	fillContainers(v1, l1, d1);

	// Printing containers values
	printContainers(v1, l1, d1);

	// Executing easyfind command for different containers
	executeEasyfind(v1, l1, d1);

	return 0;
}

// funciton fills given container with numbers 0 to 9
template <typename T>
void autoFill(T &container) {
	typename T::iterator it;
	int value = 0;

	for (it = container.begin(); it != container.end(); it++) {
		*it = value++;
	}
}

void fillContainers(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1) {
	autoFill(v1);
	autoFill(l1);
	autoFill(d1);
}

void printContainers(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1) {
	std::cout << "v1: ";
	for (std::vector<int>::iterator itv1 = v1.begin(); itv1 != v1.end(); itv1++) {
		std::cout << *itv1 << " ";
	}
	std::cout << std::endl;

	std::cout << "l1: ";
	for (std::list<int>::iterator itl1 = l1.begin(); itl1 != l1.end(); itl1++) {
		std::cout << *itl1 << " ";
	}
	std::cout << std::endl;

	std::cout << "d1: ";
	for (std::deque<int>::iterator itd1 = d1.begin(); itd1 != d1.end(); itd1++) {
		std::cout << *itd1 << " ";
	}
	std::cout << std::endl;
}

void executeEasyfind(std::vector<int> &v1, std::list<int> &l1, std::deque<int> &d1) {
	try {
		std::cout << "The index of a given number is: " << std::distance(v1.begin(), easyfind(v1, 4)) << std::endl;
	} catch (NotFoundException &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::cout << "The index of a given number is: " << std::distance(l1.begin(), easyfind(l1, 2)) << std::endl;
	} catch (NotFoundException &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		std::cout << "The index of a given number is: " << std::distance(d1.begin(), easyfind(d1, 42)) << std::endl;
	} catch (NotFoundException &e) {
		std::cout << e.what() << std::endl;
	}	
}
