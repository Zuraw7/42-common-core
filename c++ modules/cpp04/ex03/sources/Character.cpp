#include <iostream>
#include "../includes/Character.hpp"

Character::Character() : _name("Default"), _unequipped(NULL), _unequippedSize(0) {
	// std::cout << "Character default constructor called" << std::endl;
	for (int i = 0; i < 4; i++) {
		this->_inventory[i] = NULL;
	}
}

Character::Character(std::string const &name) : _name(name), _unequipped(NULL), _unequippedSize(0) {
	// std::cout << "Character set constructor called" << std::endl;
	for (int i = 0; i < 4; i++) {
		this->_inventory[i] = NULL;
	}
}

Character::Character(Character const &src) : _name(src._name), _unequipped(NULL), _unequippedSize(0) {
	// std::cout << "Character copy constructor called" << std::endl;
	// Copy inventory
	for (int i = 0; i < 4; i++) {
		if (src._inventory[i]) {
			this->_inventory[i] = src._inventory[i]->clone();
		} else {
			this->_inventory[i] = NULL;
		}
	}
	// Copy _unequipped
	this->_unequippedSize = src._unequippedSize;
	if (this->_unequippedSize > 0) {
		this->_unequipped = new AMateria*[this->_unequippedSize];
		for (int i = 0; i < this->_unequippedSize; i++) {
			this->_unequipped[i] = src._unequipped[i]->clone();
		}
	}
}

Character::~Character() {
	// Delete inventory
	for (int i = 0; i < 4; i++) {
		if (this->_inventory[i]) {
			delete this->_inventory[i];
			this->_inventory[i] = NULL;
		}
	}

	// Delete unequipped
	for (int i = 0; i < this->_unequippedSize; i++) {
		if (this->_unequipped[i]) {
			delete this->_unequipped[i];
			this->_unequipped[i] = NULL;
		}
	}
	delete[] this->_unequipped;

	// std::cout << "Character destructor called" << std::endl;
}

Character &Character::operator=(Character const &rhs) {
	// std::cout << "Character assignment operator called" << std::endl;
	if (this != &rhs) {
		// copy name
		this->_name = rhs._name;

		// delete _inventory
		for (int i = 0; i < 4; i++) {
			if (_inventory[i]) {
				delete this->_inventory[i];
				this->_inventory[i] = NULL;
			}
		}

		// copy _inventory
		for (int i = 0; i < 4; i++) {
			if (rhs._inventory[i]) {
				this->_inventory[i] = rhs._inventory[i]->clone();
			} else {
				this->_inventory[i] = NULL;
			}
		}

		// delete _unequipped
		for (int i = 0; i < this->_unequippedSize; i++) {
			if (this->_unequipped[i]) {
				delete this->_unequipped[i];
			}
		}
		delete[] this->_unequipped;

		// copy _unequipped
		this->_unequippedSize = rhs._unequippedSize;
		if (rhs._unequippedSize > 0) {
			this->_unequipped = new AMateria*[rhs._unequippedSize];
			for (int i = 0; i < rhs._unequippedSize; i++) {
				this->_unequipped[i] = rhs._unequipped[i]->clone();
			}
		} else {
			this->_unequipped = NULL;
		}
	}
	return *this;
}

std::string const &Character::getName() const {
	return this->_name;
}

void Character::equip(AMateria* m) {
	if (!m) {
		std::cout << "Cannot equip NULL Materia!" << std::endl;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (this->_inventory[i] == NULL) {
			std::cout << "Equipped " << m->getType() << " at the slot " << i << "!" << std::endl;
			_inventory[i] = m;
			return;
		}
	}

	std::cout << "Inventory is full! Cannot equip " << m->getType() << "." << std::endl;
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4) {
		std::cout << "Invalid index: " << idx << ". Cannot unequip!" << std::endl;
		return;
	}

	if (this->_inventory[idx]) {

		// Expand unequipped dynamic array
		AMateria **newUnequippped = new AMateria*[this->_unequippedSize + 1];
		for (int i = 0; i < this->_unequippedSize; i++) {
			newUnequippped[i] = this->_unequipped[i];
		}
		newUnequippped[this->_unequippedSize] = this->_inventory[idx];
		
		// delete old Unequipped array and assign new
		delete [] this->_unequipped;
		this->_unequipped = newUnequippped;
		++this->_unequippedSize;
		
		std::cout << "Unequipped from the slot " << idx << "!" << std::endl;
		this->_inventory[idx] = NULL;
	} else {
		std::cout << "Slot " << idx << " is already empty!" << std::endl;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4) {
		std::cout << "Invalid index: " << idx << ". Cannot use materia!" << std::endl;
		return;
	}
	if (this->_inventory[idx]) {
		// std::cout << "Using materia in slot " << idx << " on target " << target.getName() << "." << std::endl;
		this->_inventory[idx]->use(target);

	} else {
		std::cout << "Slot " << idx << " is empty. No materia to use!" << std::endl;
	}
}