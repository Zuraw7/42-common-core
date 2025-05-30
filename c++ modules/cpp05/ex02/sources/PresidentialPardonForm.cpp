#include <iostream>
#include "../includes/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) : AForm() {
	// std::cout << "PresidentialPardonForm default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string const &target) : AForm("PresidentialPardonForm", 25, 5), _target(target) {
	// std::cout << "PresidentialPardonForm set constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src) : AForm(src) {
	// std::cout << "PresidentialPardonForm copy constructor called" << std::endl;
	*this = src;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &rhs) {
	if (this != &rhs) {
		this->_target = rhs._target;
		AForm::operator=(rhs);
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	// std::cout << "PresidentialPardonForm destructor called" << std::endl;
}

std::string PresidentialPardonForm::getTarget(void) const {
	return this->_target;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	if (executor.getGrade() > this->getExecGradeReq()) {
		throw (AForm::GradeTooLowException());
		return;
	} else if (this->getIsSigned() == false) {
		throw (AForm::FormNotSignedException());
		return;
	}
	std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

std::ostream &operator<<(std::ostream &out, PresidentialPardonForm const &scf) {
	out << "Form: " << scf.getName() <<
	"\n Sign grade:\t" << scf.getSignGradeReq() <<
	"\n Exec grade:\t" << scf.getExecGradeReq() <<
	"\n Is signed:\t" << scf.getIsSigned() << std::endl;
	return out;
}