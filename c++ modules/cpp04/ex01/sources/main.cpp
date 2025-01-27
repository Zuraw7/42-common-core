#include <iostream>
#include "../includes/Animal.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Cat.hpp"
#include "../includes/Brain.hpp"

int main()
{
	{
		const int size = 6;
		Animal *animals[size];

		for (int i = 0; i < size / 2; i++) {
			animals[i] = new Dog();
			std::cout << std::endl;
		}
		for (int i = size / 2; i < size; i++) {
			animals[i] = new Cat();
			std::cout << std::endl;
		}

		for (int i = 0; i < size; i++) {
			animals[i]->makeSound();
			std::cout << std::endl;
		}

		for (int i = 0; i < size; i++) {
			delete animals[i];
			std::cout << std::endl;
		}
	}

	{
		// Create a Dog and set an idea
		Dog dog1;
		std::cout << std::endl;
		dog1.getBrain()->setIdea("Chase the ball", 0);

		// Create a copy of the Dog
		Dog dog2 = dog1;
		std::cout << std::endl;

		// Modify the copy's brain
		dog2.getBrain()->setIdea("Dig a hole", 0);

		// Print ideas to verify deep copy
		std::cout << "Dog1's idea: " << dog1.getBrain()->getIdea(0) << std::endl;
		std::cout << "Dog2's idea: " << dog2.getBrain()->getIdea(0) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		// Create a Cat and set an idea
		Cat cat1;
		std::cout << std::endl;
		cat1.getBrain()->setIdea("Chase a laser", 0);

		// Create a copy of the Cat
		Cat cat2 = cat1;
		std::cout << std::endl;

		// Modify the copy's brain
		cat2.getBrain()->setIdea("Sleep on the couch", 0);

		// Print ideas to verify deep copy
		std::cout << "Cat1's idea: " << cat1.getBrain()->getIdea(0) << std::endl;
		std::cout << "Cat2's idea: " << cat2.getBrain()->getIdea(0) << std::endl;
		std::cout << std::endl;
	}

	return 0;
}