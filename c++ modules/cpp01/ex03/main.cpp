#include <iostream>
#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void) {
	
	{
		Weapon bow = Weapon("crude spiked bow");
		HumanA bob("Bob", bow);
		bob.attack();
		bow.setType("some other type of bow");
		bob.attack();
	}

	std::cout << std::endl << std::endl;

	{
		Weapon sword = Weapon("crude spiked sword");
		HumanB jim("Jim");
		jim.setWeapon(sword);
		jim.attack();
		sword.setType("some other type of sword");
		jim.attack();
	}

	return 0;
}