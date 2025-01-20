#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie {
	private:
		std::string _name;

	public:
		// Constructor and destructor
		Zombie(std::string name);
		~Zombie(void);

		// Methods
		void announce(void);
};

#endif