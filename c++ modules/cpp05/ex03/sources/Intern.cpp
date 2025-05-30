#include <iostream>
#include "../includes/Intern.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"

Intern::Intern() {
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(Intern const &src) {
	*this = src;
	std::cout << "Intern copy construcor called" << std:: endl;
}

Intern &Intern::operator=(Intern const &rhs) {
	std::cout << "Intern assignment operator called" << std:: endl;
	if (this != &rhs) {
		std::cout << "Nothing to copy" << std::endl;
	}
	return *this;
}

Intern::~Intern() {
	std::cout << "Intern destructor called" << std::endl;
}

AForm *Intern::makeForm(std::string const &formName, std::string const &target) {
	AForm *(*create[3])(std::string const &target) = {
		&ShrubberyCreationForm::create,
		&RobotomyRequestForm::create,
		&PresidentialPardonForm::create};
	
	std::string names[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"};


	for (int i = 0; i < 3; i++) {
		if (formName == names[i]) {
			std::cout << "Intern creates " << formName << std::endl;
			return create[i](target);
		}
	}
	throw (Intern::WrongFormException());
	return NULL;
}