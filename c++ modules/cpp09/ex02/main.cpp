#include "PmergeMe.hpp"

bool isValidInput(char **argv, PmergeMe &pmm);
template<typename T>
void printContainer(const T &container);
void printResults(PmergeMe &pmme);
template <typename T>
void checkIsSorted(T &container);

int main (int argc, char **argv) {

	if (argc < 2) {
		std::cerr << "Error: Wrong usage!" << std::endl;
		std::cout << "Usage: ./PmergeMe <int> <int> <int> ... <int>" << std::endl;
		return 1;
	}

	PmergeMe pmme;

	if (!isValidInput(++argv, pmme)) {
		std::cerr << "Error: Wrong input!" << std::endl;
		return 1;
	}

	printResults(pmme);

	return 0;
}

/*
	Checks if input is correct -> positive numbers only
*/
bool isValidInput(char **argv, PmergeMe &pmm) {
	while (*argv) {
		std::istringstream ss(*argv);
		int number;
		while (ss >> number) {
			if (number < 0) {
				return false;
			}
			pmm.pushToVector(number);
			pmm.pushToDeque(number);
		}
		if (!ss.eof()) {
			return false;
		}
		argv++;
	}
	return true;
}

/*
	Prints container's numbers
*/
template<typename T>
void printContainer(const T &container) {
	typename T::const_iterator it;
	if (container.size() > 5) {
		it = container.begin();
		for (int i = 0; i < 5; i++) {
			std::cout << *it << " ";
			it++;
		}
		std::cout << " [...]" << std::endl;
		return;
	}
	for (it = container.begin(); it != container.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/*
	Runs sort algorithms, prints result and calculates time
*/
void printResults(PmergeMe &pmme) {
	std::cout << "Before: ";
	printContainer(pmme.getVector());

	clock_t startVec = clock();
	pmme.fordJohnsonSort(pmme.getVector());
	clock_t endVec = clock();

	clock_t startDeq = clock();
	pmme.fordJohnsonSort(pmme.getDeque());
	clock_t endDeq = clock();

	std::cout << "After: ";
	printContainer(pmme.getDeque());

	// checkIsSorted(pmme.getVector());
	// checkIsSorted(pmme.getDeque());

	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << pmme.getVector().size() << " elements with std::vector: " << timeVec << " us" << std::endl;

	std::cout << "Time to process a range of " << pmme.getDeque().size() << " elements with std::deque:  " << timeDeq << " us"<< std::endl;
}

/*
	Check if container is sorted
*/
template <typename T>
bool isSorted(T &container) {
	typename T::iterator it = container.begin();
	if (it == container.end()) {
		return true;
	}

	typename T::iterator next = it;
	++next;
	while (next != container.end()) {
		if (*next < *it) {
			return false;
		}
		++it;
		++next;
	}
	return true;
}

template <typename T>
void checkIsSorted(T &container) {
	if (isSorted(container)) {
		std::cout << "Container is sorted!" << std::endl;
	} else {
		std::cout << "Container is NOT sorted!" << std::endl;
	}
}