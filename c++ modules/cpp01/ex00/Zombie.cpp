#include <iostream>
#include "Zombie.hpp"

// Constructor and Destructor

Zombie::Zombie(std::string name) : _name(name) {}

Zombie::~Zombie(void) {
	std::cout << this->_name << std::endl;
}

// Method
void Zombie::announce(void) {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}