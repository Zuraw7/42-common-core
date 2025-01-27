#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap {
	private:
		std::string _name;
		int	_hp;
		int _energyPoints;
		int _attackDamage;

	public:
		// Conctructors and Destructor
		ClapTrap(void);		// Default construcotr (CANNON)
		ClapTrap(std::string name); // Set constructor
		ClapTrap(const ClapTrap &src);	// Copy construcor (CANNON)
		virtual ~ClapTrap(void);	// Destructor (CANNON)

		// Overloads
		ClapTrap &operator=(const ClapTrap &rhs); // Assign operator (CANNON)

		// Getters
		std::string getName(void);
		int			 getHp(void);
		int			 getEnergyPoints(void);
		int			 getAttackDamage(void);

		// Setters
		void setName(std::string name);
		void setHp(int hp);
		void setEnergyPoints(int energyPoints);
		void setAttackDamage(int attackDamage);

		// Methods
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif