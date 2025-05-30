#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>

class Bureaucrat;

class Form {
	private:
		std::string const _name;
		bool _isSigned;
		int const _signGradeReq;
		int const _execGradeReq;

	public:
		Form();
		Form(std::string const &name, int const signReqs, int const execReqs);
		Form(Form const &src);
		~Form();

		Form &operator=(Form const &rhs);

		// Getters
		std::string getName() const;
		bool getIsSigned() const;
		int getSignGradeReq() const;
		int getExecGradeReq() const;

		// Nested classes
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Exception: Grade too high");
				}
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Exception: Grade too low");
				}
		};

		// Methods
		void beSigned(Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &out, Form const &form);

#endif