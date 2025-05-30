#include <iostream>
#include "../includes/Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) : _name("Default"), _grade(75) {
	std::cout << "Default Bureaucrat constructor called" << std::endl;
	if (this->_grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	} else if (this->_grade > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
}

Bureaucrat::Bureaucrat(std::string const &name, int const grade) : _name(name), _grade(grade) {
	if (grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	} else if (grade > 150) {
		throw Bureaucrat::GradeTooLowException();
	}
	std::cout << "Set Bureaucrat constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src) : _name("Default") {
	std::cout << "Copy Bureaucrat constructor called" << std::endl;
	*this = src;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Bureaucrat destructor called" << std::endl;	
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs) {
	std::cout << "Bureaucrat assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_grade = rhs._grade;
	}
	return *this;
}

std::string Bureaucrat::getName(void) const {
	return this->_name;
}

int Bureaucrat::getGrade(void) const {
	return this->_grade;
}

void Bureaucrat::increaseGrade(void) {
	if ((this->_grade - 1) < 1) {
		throw Bureaucrat::GradeTooHighException();
		return;
	}
	--this->_grade;
}

void Bureaucrat::decreaseGrade(void) {
	if ((this->_grade + 1) > 150) {
		throw Bureaucrat::GradeTooLowException();
		return;
	}
	++this->_grade;
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat) {
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
	return out;
}