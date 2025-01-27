#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap() {
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->_name = "";
	this->_hp = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	this->_guardMode = false;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	std::cout << "ScavTrap set constructor called" << std::endl;
	this->_name = name;
	this->_hp = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	this->_guardMode = false;
}

ScavTrap::ScavTrap(ScavTrap const &src) : ClapTrap(src) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
	// *this = src;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "ScavTrap destructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &rhs) {
	if (this != &rhs) {
		ClapTrap::operator=(rhs);
	}
	return *this;
}

void ScavTrap::attack(const std::string& target) {
	// Check if ScavTrap is alive
	if (this->_hp <= 0) {
		std::cout << "ScavTrap " << this->_name << " can't attack, he's dead" << std::endl;
		return ;
	}
	// Check if ScavTrap has energy points
	// If has, attack oponent
	if (this->_energyPoints > 0) {
		std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;

		this->_energyPoints -= 1;

		std::cout << this->_name << " current energy points: " << this->_energyPoints << std::endl;
	}
	// If has not, inform user
	else {
		std::cout <<  this->_name << " don't have energy points!" << std::endl;
	}
}

void ScavTrap::guardGate() {
	if (!this->_guardMode) {
		std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode" << std::endl;
		this->_guardMode = true;
	} else {
		std::cout << "ScavTrap " << this->_name << " is no longer in Gate keeper mode" << std::endl;
		this->_guardMode = false;
	}
}
