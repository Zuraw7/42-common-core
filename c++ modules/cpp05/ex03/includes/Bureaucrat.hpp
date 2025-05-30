#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "AForm.hpp"

class AForm;

class Bureaucrat {
	private:
		std::string const _name;
		int			_grade;

	public:
		Bureaucrat(void);
		Bureaucrat(std::string const &name, int const grade);
		Bureaucrat(Bureaucrat const &src);
		~Bureaucrat(void);

		Bureaucrat &operator=(Bureaucrat const &rhs);

		// Getters
		std::string getName(void) const;
		int		getGrade(void) const;

		// Methods
		void increaseGrade(void);
		void decreaseGrade(void);
		void signForm(AForm &form);
		void executeForm(AForm const &form);

		// Nested Classes
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Exception: Grade too high";
				}
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return "Exception: Grade too low";
				}
		};
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);

#endif