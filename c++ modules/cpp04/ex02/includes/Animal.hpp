#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include "./Brain.hpp"

class AAnimal {
	protected:
		std::string _type;
	
	public:
		AAnimal(void);
		AAnimal(AAnimal const &src);
		virtual ~AAnimal(void);

		AAnimal &operator=(AAnimal const &rhs);

		std::string getType(void) const;
		
		virtual Brain *getBrain(void) const = 0;
		virtual void makeSound(void) const = 0;

};

#endif