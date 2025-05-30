#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../includes/Classes.hpp"

Base *generate(void);
void identify (Base *p);
void identify (Base &p);

int main () {
	std::srand(std::time(0));
	
	Base *rand_class = generate();
	if (!rand_class) {
		std::cout << "Generating random class failed!" << std::endl;
		return 1;
	}

	// Base *rand_class = new Base();

	identify(rand_class);
	identify(*rand_class);

	delete rand_class;

	return 0;
}

Base *generate(void) {
	switch (rand() % 3)
	{
		case 0:
			std::cout << "Created A class" << std::endl;
			return new A();
		case 1:
			std::cout << "Created B class" << std::endl;
			return new B();	
		case 2:
			std::cout << "Created C class" << std::endl;
			return new C();
		default:
			std::cout << "Error occured" << std::endl;
			return NULL;
	}
}

void identify (Base *p) {
	std::cout << "Identify by pointer detected ";
	if (dynamic_cast<A*>(p)) {
		std::cout << "A";
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B";
	} else if (dynamic_cast<C*>(p)){
		std::cout << "C";
	} else {
		std::cout << "error: Wrong class!" << std::endl;
		return ;
	}
	std::cout << " class" << std::endl;
}

void identify (Base &p) {
	std::cout << "Identify by reference detected ";
	try {
		(void) dynamic_cast<A &>(p);
		std::cout << "A";
	} catch (...) {
		try {
			(void) dynamic_cast<B &>(p);
			std::cout << "B";
		} catch (...) {
			try {
				(void) dynamic_cast<C &>(p);
				std::cout << "C";
			} catch (...) {
				std::cout << "error: Wrong class!" << std::endl;
				return;
			}
		}
	}
	std::cout << " class" << std::endl;
}
