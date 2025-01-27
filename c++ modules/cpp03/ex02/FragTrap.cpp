#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap() {
	std::cout << "FragTrap default constructor called" << std::endl;
	this->_name = "";
	this->_hp = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "FragTrap set constructor called" << std::endl;
	this->_name = name;
	this->_hp = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
}

FragTrap::FragTrap(FragTrap const &src) : ClapTrap(src) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	// *this = src;
}

FragTrap::~FragTrap(void) {
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap &FragTrap::operator=(FragTrap const &rhs) {
	if (this != &rhs) {
		ClapTrap::operator=(rhs);
	}
	return *this;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << this->_name << " says: High five, anyone? 🙌" << std::endl;
}
