#include <iostream>
#include "ClapTrap.hpp"

// Conctructors and Destructor
ClapTrap::ClapTrap(void) : _name(""), _hp(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hp(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "Set constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src) {
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called" << std::endl;
}

// Overloads
ClapTrap &ClapTrap::operator=(const ClapTrap &rhs) {
	std::cout << "Assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_name = rhs._name;
		this->_hp = rhs._hp;
		this->_energyPoints = rhs._energyPoints;
		this->_attackDamage = rhs._attackDamage;
	}
	return *this;
}

// Getters
std::string ClapTrap::getName(void) {
	return this->_name;
}

int ClapTrap::getHp(void) {
	return this->_hp;
}

int ClapTrap::getEnergyPoints(void) {
	return this->_energyPoints;
}

int ClapTrap::getAttackDamage(void) {
	return this->_attackDamage;
}

// Setters
void ClapTrap::setName(std::string name) {
	this->_name = name;
}

void ClapTrap::setHp(int hp) {
	this->_hp = hp;
}

void ClapTrap::setEnergyPoints(int ep) {
	this->_energyPoints = ep;
}

void ClapTrap::setAttackDamage(int ad) {
	this->_attackDamage = ad;
}

// Methods
void ClapTrap::attack(const std::string &target) {
	// Check if ClapTrap is alive
	if (this->getHp() <= 0) {
		std::cout << "ClapTrap " << this->getName() << " can't attack, he's dead" << std::endl;
		return ;
	}
	// Check if ClapTrap has energy points
	// If has, attack oponent
	if (this->getEnergyPoints() > 0) {
		std::cout << "ClapTrap " << this->getName() << " attacks " << target << ", causing " << this->getAttackDamage() << " points of damage!" << std::endl;

		this->setEnergyPoints(this->_energyPoints - 1);

		std::cout << this->getName() << " current energy points: " << this->getEnergyPoints() << std::endl;
	}
	// If has not, inform user
	else {
		std::cout <<  this->getName() << " don't have energy points!" << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount) {
	// Check if ClapTrap is alive
	if (this->getHp() <= 0) {
		std::cout << "ClapTrap " << this->getName() << " is already dead" << std::endl;
		return ;
	}
	// Infomr user that ClapTrap took dmg, decrease hp, tell user current hp
	std::cout << "ClapTrap " << this->getName() << " takes " << amount << " amount of damage " << std::endl;
	this->setHp(this->getHp() - amount);
	std::cout << this->getName() << " current hit points: " << this->getHp() << std::endl;
	// Check if ClapTrap died
	if (this->getHp() <= 0)
		std::cout << "ClapTrap " << this->getName() << " is dead" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	// Check if ClapTrap is alive
	if (this->getHp() <= 0) {
		std::cout << "ClapTrap " << this->getName() << " can't repair, he's dead" << std::endl;
		return ;
	}
	// Check if ClapTrap has energy points
	// If has, inform user ClapTrap is healing, change both hp and energy points, show user current hp and energy point
	if (this->getEnergyPoints() > 0) {
		std::cout << "ClapTrap " << this->getName() << " repairs himself for " << amount << " hp" << std::endl;

		this->setHp(this->getHp() + amount);
		this->setEnergyPoints(this->_energyPoints - 1);

		std::cout << this->getName() << " current hit points: " << this->getHp() << std::endl;
		std::cout << this->getName() << " current energy points: " << this->getEnergyPoints() << std::endl;
	}
	// If has not, inform user
	else {
		std::cout << this->getName() << " don't have energy points!" << std::endl;
	}
}