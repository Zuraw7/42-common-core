#include <iostream>
#include <cstdlib>
#include "../includes/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) : AForm() {
	// std::cout << "RobotomyRequestForm default constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string const &target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {
	// std::cout << "RobotomyRequestForm set constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src) : AForm(src) {
	// std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
	*this = src;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &rhs) {
	if (this != &rhs) {
		this->_target = rhs._target;
		AForm::operator=(rhs);
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	// std::cout << "RobotomyRequestForm destructor called" << std::endl;
}

std::string RobotomyRequestForm::getTarget(void) const {
	return this->_target;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	if (executor.getGrade() > this->getExecGradeReq()) {
		throw (AForm::GradeTooLowException());
		return;
	} else if (this->getIsSigned() == false) {
		throw (AForm::FormNotSignedException());
		return;
	}
	std::cout << "* Drilling noises *" << std::endl;
	if (rand() % 2 == 0) {
		std::cout << this->getTarget() << " has been successfully robotomized!" << std::endl;
	} else {
		std::cout << "Robotomy failed on " << this->getTarget() << "!" << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, RobotomyRequestForm const &scf) {
	out << "Form: " << scf.getName() <<
	"\n Sign grade:\t" << scf.getSignGradeReq() <<
	"\n Exec grade:\t" << scf.getExecGradeReq() <<
	"\n Is signed:\t" << scf.getIsSigned() << std::endl;
	return out;
}