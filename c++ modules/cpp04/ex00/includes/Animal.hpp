#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal {
	protected:
		std::string _type;
	
	public:
		Animal(void);
		Animal(Animal const &src);
		virtual ~Animal(void);

		Animal &operator=(Animal const &rhs);

		std::string getType(void) const;

		virtual void makeSound(void) const;

};

class WrongAnimal {
	protected:
		std::string _type;
	
	public:
		WrongAnimal(void);
		WrongAnimal(WrongAnimal const &src);
		virtual ~WrongAnimal(void);

		WrongAnimal &operator=(WrongAnimal const &rhs);

		std::string getType(void) const;

		void makeSound(void) const;

};


#endif