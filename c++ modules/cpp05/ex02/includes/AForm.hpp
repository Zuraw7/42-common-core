#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>

class Bureaucrat;

class AForm {
	private:
		std::string const _name;
		bool _isSigned;
		int const _signGradeReq;
		int const _execGradeReq;

	public:
		AForm();
		AForm(std::string const &name, int const signReqs, int const execReqs);
		AForm(AForm const &src);
		virtual ~AForm();

		AForm &operator=(AForm const &rhs);

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
		class FormNotSignedException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Exception: Form is not signed");
				}
		};

		// Methods
		void beSigned(Bureaucrat &bureaucrat);
		virtual void execute(Bureaucrat const &executor) const = 0;
};

std::ostream &operator<<(std::ostream &out, AForm const &form);

#endif