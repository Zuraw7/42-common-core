#include "./PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const &src) {
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs) {
	if (this != &rhs) {
		this->_v = rhs._v;
		this->_d = rhs._d;
	}
	return *this;
}

void PmergeMe::pushToVector(int number) {
	this->_v.push_back(number);
}

void PmergeMe::pushToDeque(int number) {
	this->_d.push_back(number);
}

std::vector<int> &PmergeMe::getVector() {
	return this->_v;
}

std::deque<int> &PmergeMe::getDeque() {
	return this->_d;
}

/*
	Prints pairs
*/
void printPairs(const std::vector<std::pair<int, int> > &pairs) {
	for (size_t i = 0; i < pairs.size(); i++) {
		std::cout << "(" << pairs[i].first << ", ";
		if (pairs[i].second != -1) {
			std::cout << pairs[i].second;
		} else {
			std::cout << "none";
		}
		std::cout << ")";
	}
	std::cout << std::endl;
}

/*
	Compates numbers in pairs, swaps if first is bigger
*/
void compareInPair(std::vector<std::pair<int, int> > &pairs) {
	for (size_t i = 0; i < pairs.size(); i++) {
		if (pairs[i].first > pairs[i].second) {
			int temp;
			temp = pairs[i].first;
			pairs[i].first = pairs[i].second;
			pairs[i].second = temp;
		}
	}
}

