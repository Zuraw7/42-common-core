#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include "./Animal.hpp"
#include "./Brain.hpp"

class Dog : public AAnimal {
	private:
		Brain *brain;

	public:
		Dog(void);
		Dog(Dog const &src);
		~Dog(void);

		Dog &operator=(Dog const &rhs);

		// get
		Brain *getBrain(void) const;

		void makeSound(void) const;

};

#endif