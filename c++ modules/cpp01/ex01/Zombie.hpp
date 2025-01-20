#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie {
	private:
		std::string _name;
	
	public:
	// Constructor and destructor
		Zombie(void);
		~Zombie(void);

	// setter
	void setName(std::string name);

	// Methods
	void announce(void);
};

#endif