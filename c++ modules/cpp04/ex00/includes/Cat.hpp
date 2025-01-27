#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include "./Animal.hpp"

class Cat : public Animal {
	public:
		Cat(void);
		Cat(Cat const &src);
		~Cat(void);

		Cat &operator=(Cat const &rhs);

		void makeSound(void) const;
};

class WrongCat : public WrongAnimal {
	public:
		WrongCat(void);
		WrongCat(WrongCat const &src);
		~WrongCat(void);

		WrongCat &operator=(WrongCat const &rhs);

		void makeSound(void) const;
};

#endif