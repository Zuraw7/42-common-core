#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <utility>
#include <ctime>
#include <iomanip>

class PmergeMe {
	private:
		std::vector<int> _v;
		std::deque<int> _d;

	public:
		PmergeMe();
		PmergeMe(PmergeMe const &src);
		~PmergeMe();

		PmergeMe &operator=(PmergeMe const &rhs);

		void pushToVector(int number);
		void pushToDeque(int number);

		std::vector<int> &getVector();
		std::deque<int> &getDeque();

		template<typename T>
		void fordJohnsonSort(T &container);
};


/*
	Ford Johnson sort algorithm:
		1. Split into pairs and sort them
			a. Cuts last element if container.size() is odd
			b. Create pairs in from given container
			c. Check if pairs are sorted (smaller, bigger), swap if not
			d. Create 2 containers for smaller and larger numbers
		2. Recursive calls
			a. split container with larger numbers into smaller ones
		3. Insert smaller into larger
			a. Insert each smaller number into larger container
			b. Insert using Binary Insertion
		4. Insert lastElement at the right spot (Binary Insertion)
*/
template <typename T>
std::vector<std::pair<int, int> > createPairs(T &constainer);
void printPairs(const std::vector<std::pair<int, int> > &pairs);
void compareInPair(std::vector<std::pair<int, int> > &pairs);
template <typename T>
void splitPairs(std::vector<std::pair<int, int> > &pairs, T &smaller, T &larger);

template <typename T>
inline void PmergeMe::fordJohnsonSort(T &container) {
	
	// 1. 
		// a. Cuts last element if container.size() is odd
	int	lastElement = -1;	// Holds last element if container has odd numbers else it's set to -1 (numbers can't be less then 0)
	if (container.size() % 2 != 0) {
		lastElement = container.back();
		container.pop_back();
	}

		// b. Create pairs in from given container
	std::vector<std::pair<int, int> > pairs = createPairs(container);
	// printPairs(pairs);

		// c. Check if pairs are sorted (smaller, bigger), swap if not
	compareInPair(pairs);
	// printPairs(pairs);

		// d. Create 2 containers for smaller and larger numbers
	T smaller, larger;
	splitPairs(pairs, smaller, larger);


	// 2.
		// a. split container with larger numbers into smaller ones
	if (!larger.empty()) {
		fordJohnsonSort(larger);
	}

	// 3.
		// a. Insert each smaller number into larger container
		// b. Insert using Binary Insertion
	for (size_t i = 0; i < smaller.size(); i++) {
		typename T::iterator pos = std::lower_bound(larger.begin(), larger.end(), smaller[i]);
		larger.insert(pos, smaller[i]);
	}

	container = larger;

	// 4. Insert lastElement at the right spot (Binary Insertion)
	if (lastElement != -1) {
		typename T::iterator pos = std::lower_bound(container.begin(), container.end(), lastElement);
		container.insert(pos, lastElement);
	}
	
}

/*
	Creates pairs from given containers
*/
template <typename T>
std::vector<std::pair<int, int> > createPairs(T &container) {
	std::vector<std::pair<int, int> > pairs;

	typename T::iterator it = container.begin();
	while (it != container.end()) {
		int first = *it;
		++it;
		if (it != container.end()) {
			int second = *it;
			pairs.push_back(std::make_pair(first, second));
			++it;
		} else {
			pairs.push_back(std::make_pair(first, -1));
			std::cout << "No pair!!!" << std::endl;
		}
	}
	return pairs;
}

/*
	Splits pairs into smaller and larger containers
*/
template <typename T>
void splitPairs(std::vector<std::pair<int, int> > &pairs, T &smaller, T &larger) {
	for (size_t i = 0; i < pairs.size(); i++) {
		smaller.push_back(pairs[i].first);
		if (pairs[i].second != -1) {
			larger.push_back(pairs[i].second);
		}
	}
}

#endif