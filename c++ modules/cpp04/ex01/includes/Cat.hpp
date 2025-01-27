#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include "./Animal.hpp"
#include "./Brain.hpp"

class Cat : public Animal {
	private:
		Brain *brain;

	public:
		Cat(void);
		Cat(Cat const &src);
		~Cat(void);

		Cat &operator=(Cat const &rhs);

		// get
		Brain *getBrain(void) const;

		void makeSound(void) const;
};

#endif