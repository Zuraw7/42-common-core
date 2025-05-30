#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>

class AForm;

class Intern {
	public:
		Intern();
		Intern(Intern const &src);
		~Intern();
		
		class WrongFormException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Exception: Wrong form name";
				}
		};

		Intern &operator=(Intern const &rhs);

		AForm *makeForm(std::string const &formName, std::string const &target);
};

#endif