#include <iostream>
#include "../includes/Animal.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Cat.hpp"

int main()
{
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete i;
		delete j;
	}

	std::cout << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << "*Wrong Animal and Wrong Cat test*" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;

	{
		const WrongAnimal* meta = new WrongAnimal();
		const WrongAnimal* i = new WrongCat();

		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the WrongAnimal sound!
		meta->makeSound();

		delete meta;
		delete i;
	}

	return 0;
}