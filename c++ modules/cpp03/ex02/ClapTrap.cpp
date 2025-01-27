#include <iostream>
#include "ClapTrap.hpp"

// Conctructors and Destructor
ClapTrap::ClapTrap(void) : _name(""), _hp(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hp(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap set constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src) {
	std::cout << "ClapTrap copy constructor called" << std::endl;
	*this = src;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called" << std::endl;
}

// Overloads
ClapTrap &ClapTrap::operator=(const ClapTrap &rhs) {
	std::cout << "ClapTrap assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_name = rhs._name;
		this->_hp = rhs._hp;
		this->_energyPoints = rhs._energyPoints;
		this->_attackDamage = rhs._attackDamage;
	}
	return *this;
}

// Methods
void ClapTrap::attack(const std::string &target) {
	// Check if ClapTrap is alive
	if (this->_hp <= 0) {
		std::cout << "ClapTrap " << this->_name << " can't attack, he's dead" << std::endl;
		return ;
	}
	// Check if ClapTrap has energy points
	// If has, attack oponent
	if (this->_energyPoints > 0) {
		std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;

		this->_energyPoints -= 1;

		std::cout << this->_name << " current energy points: " << this->_energyPoints << std::endl;
	}
	// If has not, inform user
	else {
		std::cout <<  this->_name << " don't have energy points!" << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount) {
	// Check if ClapTrap is alive
	if (this->_hp <= 0) {
		std::cout << "ClapTrap " << this->_name << " is already dead" << std::endl;
		return ;
	}
	// Infomr user that ClapTrap took dmg, decrease hp, tell user current hp
	std::cout << "ClapTrap " << this->_name << " takes " << amount << " amount of damage " << std::endl;
	this->_hp -= amount;
	std::cout << this->_name << " current hit points: " << this->_hp << std::endl;
	// Check if ClapTrap died
	if (this->_hp <= 0)
		std::cout << "ClapTrap " << this->_name << " is dead" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	// Check if ClapTrap is alive
	if (this->_hp <= 0) {
		std::cout << "ClapTrap " << this->_name << " can't repair, he's dead" << std::endl;
		return ;
	}
	// Check if ClapTrap has energy points
	// If has, inform user ClapTrap is healing, change both hp and energy points, show user current hp and energy point
	if (this->_energyPoints > 0) {
		std::cout << "ClapTrap " << this->_name << " repairs himself for " << amount << " hp" << std::endl;

		this->_hp += amount;
		this->_energyPoints -= 1;

		std::cout << this->_name << " current hit points: " << this->_hp << std::endl;
		std::cout << this->_name << " current energy points: " << this->_energyPoints << std::endl;
	}
	// If has not, inform user
	else {
		std::cout << this->_name << " don't have energy points!" << std::endl;
	}
}