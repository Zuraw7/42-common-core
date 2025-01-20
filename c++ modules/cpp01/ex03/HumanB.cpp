#include <iostream>
#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB(std::string name) : _name(name) {
	std::cout << "HumanB " << this->getName() << " created with no weapon" << std::endl;
}

HumanB::~HumanB() {
	std::cout << "HumanB " << this->getName() << " destroyed" << std::endl;
}

std::string HumanB::getName() {
	return this->_name;
}

void HumanB::attack() {
	std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) {
	this->_weapon = &weapon;
	std::cout << "Weapon " << this->_weapon->getType() << " was given to " << this->getName() << std::endl;
}