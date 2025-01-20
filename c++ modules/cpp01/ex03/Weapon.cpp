#include <iostream>
#include "Weapon.hpp"

Weapon::Weapon(std::string name) {
	this->_type = name;
	std::cout << "Weapon " << this->getType() << " created" << std::endl;
}

Weapon::~Weapon() {}

std::string Weapon::getType(void) {
	return this->_type;
}

void Weapon::setType(std::string type) {
	std::cout << "Weapon changed from " << this->getType() << " to " << type << std::endl;
	this->_type = type;
}