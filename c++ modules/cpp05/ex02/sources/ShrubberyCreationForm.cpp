#include <iostream>
#include <fstream>
#include "../includes/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm() {
	// std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
	// std::cout << "ShrubberyCreationForm set constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src) : AForm(src) {
	// std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
	*this = src;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs) {
	if (this != &rhs) {
		this->_target = rhs._target;
		AForm::operator=(rhs);
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	// std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

std::string ShrubberyCreationForm::getTarget(void) const {
	return this->_target;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	//Check reqs
	if (executor.getGrade() > this->getExecGradeReq()) {
		throw (AForm::GradeTooLowException());
		return;
	} else if (this->getIsSigned() == false) {
		throw (AForm::FormNotSignedException());
		return;
	}

	// open file and draw trees
	std::ofstream out(this->getTarget().append("_shrubbery").c_str());
	if (!out) {
		std::cerr << "Error creating file " << this->_target + "_shrubbery" << std::endl;
		return;
	}

	for (int i = 0; i < 3; i++) {
		out << 
			"         v" << std::endl <<
			"        >X<" << std::endl <<
			"         A" << std::endl <<
			"        d$b" << std::endl <<
			"      .d\\$$b." << std::endl <<
			"    .d$i$$\\$$b." << std::endl <<
			"       d$$@b" << std::endl <<
			"      d\\$$$ib" << std::endl <<
			"    .d$$$\\$$$b" << std::endl <<
			"  .d$$@$$$$\\$$ib." << std::endl <<
			"      d$$i$$b" << std::endl <<
			"     d\\$$$$@$b" << std::endl <<
			"  .d$@$$\\$$$$$@b." << std::endl <<
			".d$$$$i$$$\\$$$$$$b." << std::endl <<
			"        ###" << std::endl <<
			"        ###" << std::endl <<
			"        ###" << std::endl <<
			std::endl;
	}
	std::cout << "Created " << this->getTarget() + "_shrubbery" << " file!" << std::endl;
	out.close();
}

std::ostream &operator<<(std::ostream &out, ShrubberyCreationForm const &scf) {
	out << "Form: " << scf.getName() <<
	"\n Sign grade:\t" << scf.getSignGradeReq() <<
	"\n Exec grade:\t" << scf.getExecGradeReq() <<
	"\n Is signed:\t" << scf.getIsSigned() << std::endl;
	return out;
}