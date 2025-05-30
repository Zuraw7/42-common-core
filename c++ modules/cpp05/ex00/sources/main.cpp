#include <iostream>
#include "../includes/Bureaucrat.hpp"

void testCopyConstructor(void);
void testGradeTooHigh(void);
void testGradeTooLow(void);
void testWrongIncrease(void);
void testWrongDecrease(void);
void testCorrect(void);

int main () {

	testCopyConstructor();
	std::cout << std::endl;
	testGradeTooHigh();
	std::cout << std::endl;
	testGradeTooLow();
	std::cout << std::endl;
	testWrongIncrease();
	std::cout << std::endl;
	testWrongDecrease();
	std::cout << std::endl;
	testCorrect();
	std::cout << std::endl;

	return 0;
}

void testCopyConstructor(void) {
	std::cout << "========Test: Copy Constructor========" << std::endl;
	Bureaucrat *Jeff = new Bureaucrat("Jeff", 75);
	Bureaucrat John(*Jeff);

	std::cout << *Jeff << std::endl;
	std::cout << John << std::endl;
	delete Jeff;
}

void testGradeTooHigh(void) {
	std::cout << "========Test: Grade too high========" << std::endl;
	Bureaucrat *Jeff = NULL;
	int grade = 0;

	try {
		Jeff = new Bureaucrat("Jeff", grade);
	} catch (std::exception const &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
		return ;
	}

	Jeff->increaseGrade();
	std::cout << *Jeff << std::endl;

	delete Jeff;
}

void testGradeTooLow(void) {
	std::cout << "========Test: Grade too low========" << std::endl;
	Bureaucrat *Jeff = NULL;
	int grade = 151;

	try {
		Jeff = new Bureaucrat("Jeff", grade);
	} catch (std::exception const &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
		return ;
	}

	Jeff->increaseGrade();
	std::cout << *Jeff << std::endl;

	delete Jeff;
}

void testWrongIncrease(void) {
	std::cout << "========Test: Wrong Increase========" << std::endl;
	int grade = 1;
	Bureaucrat *Jeff = new Bureaucrat("Jeff", grade);

	std::cout << *Jeff << std::endl;

	try {
		Jeff->increaseGrade();
	} catch (std::exception const &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
		delete Jeff;
		return ;
	}

	std::cout << *Jeff << std::endl;

	delete Jeff;
}

void testWrongDecrease(void) {
	std::cout << "========Test: Wrong Decrease========" << std::endl;
	int grade = 150;
	Bureaucrat *Jeff = new Bureaucrat("Jeff", grade);

	std::cout << *Jeff << std::endl;

	try {
		Jeff->decreaseGrade();
	} catch (std::exception const &e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
		delete Jeff;
		return ;
	}

	std::cout << *Jeff << std::endl;

	delete Jeff;
}

void testCorrect() {
	std::cout << "========Test: Correct========" << std::endl;
	int	grade = 75;
	Bureaucrat *Jeff = NULL;

	// Creating
	try {
		Jeff = new Bureaucrat("Jeff", grade);
	} catch (std::exception const &e) {
		std::cout << "Creating bureaucrat: " << e.what() << std::endl;
		return;
	}
	std::cout << *Jeff << std::endl;

	// Increasing
	try {
		Jeff->increaseGrade();
	} catch (std::exception const &e) {
		std::cout << "Increasing grade: " << e.what() << std::endl;
		delete Jeff;
		return;
	}
	std::cout << *Jeff << std::endl;

	// Decreasing
	try {
		Jeff->decreaseGrade();
	} catch (std::exception const &e) {
		std::cout << "Decreasing grade: " << e.what() << std::endl;
		delete Jeff;
		return;
	}
	std::cout << *Jeff << std::endl;	

	delete Jeff;
}
