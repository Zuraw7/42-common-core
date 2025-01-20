#include <iostream>
#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon) {
	std::cout << "HumanA " << this->getName() << " created with " << weapon.getType() << std::endl;
}

HumanA::~HumanA() {
	std::cout << "HumanA " << this->getName() << " destroyed" << std::endl;
}

std::string HumanA::getName() {
	return this->_name;
}

void HumanA::attack() {
	std::cout << this->_name << " attacks with their " << this->_weapon.getType() << std::endl;
}
