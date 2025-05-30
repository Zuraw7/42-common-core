#include <iostream>
#include "../includes/AForm.hpp"
#include "../includes/Bureaucrat.hpp"

AForm::AForm(void) : _name("Default"), _isSigned(false), _signGradeReq(75), _execGradeReq(75){
	// std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(std::string const &name, int const signGradeReqs, int const execGradeReqs) : _name(name), _isSigned(false), _signGradeReq(signGradeReqs), _execGradeReq(execGradeReqs) {
	if (signGradeReqs < 1 || execGradeReqs < 1) {
		throw AForm::GradeTooHighException();
	} else if (signGradeReqs > 150 || execGradeReqs > 150) {
		throw AForm::GradeTooLowException();
	}
	// std::cout << "AForm set constructor called" << std::endl;
}

AForm::AForm(AForm const &src) : _name("Default"), _signGradeReq(75), _execGradeReq(75) {
	// std::cout << "AForm copy constructor called" << std::endl;
	*this = src;
}

AForm &AForm::operator=(AForm const &rhs) {
	// std::cout << "AForm assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_isSigned = rhs._isSigned;
	}
	return *this;
}

AForm::~AForm(void) {
	// std::cout << "AForm destructor called" << std::endl;
}

std::ostream &operator<<(std::ostream &out, AForm const &form) {
	std::string is_signed = "is not signed.";
	if (form.getIsSigned()) {
		is_signed = "is signed.";
	}

	out << "AForm " << form.getName() << " requires grade " << form.getSignGradeReq() << " to sign and grade " << form.getExecGradeReq() << " to execute it. AForm " << is_signed << std::endl;
	return out;
}

// Getters
std::string AForm::getName() const {
	return this->_name;
}

bool AForm::getIsSigned() const {
	return this->_isSigned;
}

int AForm::getSignGradeReq() const {
	return this->_signGradeReq;
}

int AForm::getExecGradeReq() const {
	return this->_execGradeReq;
}

// Methods
void AForm::beSigned(Bureaucrat  &bureaucrat) {
	if (bureaucrat.getGrade() <= this->getSignGradeReq()) {
		this->_isSigned = true;
	} else {
		throw AForm::GradeTooLowException();
	}
}
