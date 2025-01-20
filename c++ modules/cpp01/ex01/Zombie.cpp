#include <iostream>
#include "Zombie.hpp"

Zombie::Zombie(void) : _name("") {}

Zombie::~Zombie(void) {
	std::cout << this->_name << std::endl;
}

void Zombie::setName(std::string name) {
	this->_name = name;
}

void Zombie::announce(void) {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}