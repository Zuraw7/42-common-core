#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template<typename T>
class Array {
	private:
		T *_array;
		unsigned int _arrSize;

	public:
		Array() : _array(NULL), _arrSize(0) {}
		Array(unsigned int n) : _array(new T[n]()), _arrSize(n) {}
		
		Array(Array const &src) : _array(new T[src._arrSize]()), _arrSize(src._arrSize) {
			for (unsigned int i = 0; i < this->_arrSize; i++) {
				this->_array[i] = src._array[i];
			}
		}
		~Array() {delete [] this->_array;}

		Array &operator=(Array const &rhs) {
			if (this != &rhs) {
				delete [] this->_array;
				this->_arrSize = rhs._arrSize;
				this->_array = new T[this->_arrSize];

				for (unsigned int i = 0; i < rhs._arrSize; i++) {
					this->_array[i] = rhs._array[i];
				}
			}
			return *this;
		}

		T &operator[](unsigned int index) {
			if (index >= this->_arrSize) {
				throw std::out_of_range("Index out of range");
			}
			return this->_array[index];
		}

		unsigned int size() const {
			return this->_arrSize;
		}
};

#endif