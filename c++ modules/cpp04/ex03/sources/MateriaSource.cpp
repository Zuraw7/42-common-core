#include <iostream>
#include "../includes/MateriaSource.hpp"

MateriaSource::MateriaSource() : _overflow(NULL), _overflowSize(0) {
	// std::cout << "MateriaSource default constructor" << std::endl;
	for (int i = 0; i < 4; i++) {
		this->_knownMateria[i] = NULL;
	}
}

MateriaSource::MateriaSource(MateriaSource const &src) : _overflow(NULL), _overflowSize(0) {
	// std::cout << "MateriaSource copy constructor" << std::endl;
	// Copy _knowMateria
	for (int i = 0; i < 4; i++) {
		if (src._knownMateria[i]) {
			this->_knownMateria[i] = src._knownMateria[i]->clone();
		} else {
			this->_knownMateria[i] = NULL;
		}
	}

	// Copy overflow
	this->_overflowSize = src._overflowSize;
	if (this->_overflowSize > 0) {
		this->_overflow = new AMateria*[this->_overflowSize];
		for (int i = 0; i < this->_overflowSize; i++) {
			this->_overflow[i] = src._overflow[i]->clone();
		}
	}
}

MateriaSource::~MateriaSource() {
	// Delete knownMateria
	for (int i = 0; i < 4; i++) {
		if (this->_knownMateria[i]) {
			delete this->_knownMateria[i];
			this->_knownMateria[i] = NULL;
		}
	}
	// Delete overflow
	for (int i = 0; i < this->_overflowSize; i++) {
		if (this->_overflow[i]) {
			delete this->_overflow[i];
		}
	}
	delete[] this->_overflow;
	// std::cout << "MateriaSource destructor" << std::endl;
}

MateriaSource &MateriaSource::operator=(MateriaSource const &rhs) {
	// std::cout << "MateriaSource assignment constructor" << std::endl;
	if (this != &rhs) {
		// delete _knownMateria
		for (int i = 0; i < 4; i++) {
			if (this->_knownMateria[i]) {
				delete this->_knownMateria[i];
				this->_knownMateria[i] = NULL;
			}
		}

		// copy _knownMateria
		for (int i = 0; i < 4; i++) {
			if (rhs._knownMateria[i]) {
				this->_knownMateria[i] = rhs._knownMateria[i]->clone();
			} else {
				this->_knownMateria[i] = NULL;
			}
		}

		// delete overflow
		for (int i = 0; i < this->_overflowSize; i++) {
			if (this->_overflow[i]) {
				delete this->_overflow[i];
			}
		}
		delete[] this->_overflow;

		// copy overflow
		this->_overflowSize = rhs._overflowSize;
		if (rhs._overflowSize > 0) {
			this->_overflow = new AMateria*[rhs._overflowSize];
			for (int i = 0; i < rhs._overflowSize; i++) {
				this->_overflow[i] = rhs._overflow[i]->clone();
			}
		} else {
			this->_overflow = NULL;
		}
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* materia) {
	if (!materia) {
		std::cout << "Cannot hold NULL materia" << std::endl;
	}
	// Add materia to knownMateria
	for (int i = 0; i < 4; i++) {
		if (this->_knownMateria[i] == NULL) {
			this->_knownMateria[i] = materia->clone();
			delete materia;
			return;
		}
	}
	// Add materia to overflow
	AMateria **newOverflow = new AMateria*[this->_overflowSize + 1];
	for (int i = 0; i < this->_overflowSize; i++) {
		newOverflow[i] = this->_overflow[i];
	}
	newOverflow[this->_overflowSize] = materia;

	// Delete old overflow and assign newOverflow
	delete [] this->_overflow;
	this->_overflow = newOverflow;
	++this->_overflowSize;

	std::cout << "Cannot assign materia, no space left" << std::endl;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (this->_knownMateria[i] && this->_knownMateria[i]->getType() == type) {
			// std::cout << "Created materia: " << this->_knownMateria[i]->getType() << std::endl;
			return this->_knownMateria[i]->clone();
		}
	}
	return 0;
}