#include <iostream>
#include "ClapTrap.hpp"

int main (void) {
	ClapTrap c1("Gearbert");
	ClapTrap c2("Bolster");

	{
		std::cout << std::endl;
		c2.attack(c1.getName());
		std::cout << std::endl;
		c2.beRepaired(1);
		std::cout << std::endl;
		c2.takeDamage(3);
		std::cout << std::endl;
		c2.takeDamage(8);
		std::cout << std::endl;
		c2.attack(c1.getName());
	}
	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Another block of code" << std::endl;
		std::cout << std::endl;
		c1.attack(c2.getName());
		std::cout << std::endl;
		c1.attack(c2.getName());
		std::cout << std::endl;
		c1.beRepaired(2);
		std::cout << std::endl;
		c1.beRepaired(2);
		std::cout << std::endl;
		c1.takeDamage(4);
		std::cout << std::endl;
		std::cout << "Manual energy point set to 0" << std::endl;
		c1.setEnergyPoints(0);
		c1.attack(c2.getName());
	}

	return 0;
}