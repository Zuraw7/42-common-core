#ifndef HUMAN_A_HPP
#define HUMAN_A_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA {
	private:
		std::string _name;
		Weapon 		&_weapon;

	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA(void);

		std::string getName(void);

		void attack(void);
};


#endif