#include <iostream>
#include "../includes/Form.hpp"
#include "../includes/Bureaucrat.hpp"

Form::Form(void) : _name("Default"), _isSigned(false), _signGradeReq(75), _execGradeReq(75){
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string const &name, int const signGradeReqs, int const execGradeReqs) : _name(name), _isSigned(false), _signGradeReq(signGradeReqs), _execGradeReq(execGradeReqs) {
	if (signGradeReqs < 1 || execGradeReqs < 1) {
		throw Form::GradeTooHighException();
	} else if (signGradeReqs > 150 || execGradeReqs > 150) {
		throw Form::GradeTooLowException();
	}
	std::cout << "Form set constructor called" << std::endl;
}

Form::Form(Form const &src) : _name("Default"), _signGradeReq(75), _execGradeReq(75) {
	std::cout << "Form copy constructor called" << std::endl;
	*this = src;
}

Form &Form::operator=(Form const &rhs) {
	std::cout << "Form assignment operator called" << std::endl;
	if (this != &rhs) {
		this->_isSigned = rhs._isSigned;
	}
	return *this;
}

Form::~Form(void) {
	std::cout << "Form destructor called" << std::endl;
}

std::ostream &operator<<(std::ostream &out, Form const &form) {
	std::string is_signed = "is not signed.";
	if (form.getIsSigned()) {
		is_signed = "is signed.";
	}

	out << "Form " << form.getName() << " requires grade " << form.getSignGradeReq() << " to sign and grade " << form.getExecGradeReq() << " to execute it. Form " << is_signed << std::endl;
	return out;
}

// Getters
std::string Form::getName() const {
	return this->_name;
}

bool Form::getIsSigned() const {
	return this->_isSigned;
}

int Form::getSignGradeReq() const {
	return this->_signGradeReq;
}

int Form::getExecGradeReq() const {
	return this->_execGradeReq;
}

// Methods
void Form::beSigned(Bureaucrat  &bureaucrat) {
	if (bureaucrat.getGrade() <= this->getSignGradeReq()) {
		this->_isSigned = true;
	} else {
		throw Form::GradeTooLowException();
	}
}
