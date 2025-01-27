#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain {
	private:
		std::string _ideas[100];

	public:
		Brain(void);
		Brain(Brain const &src);
		~Brain(void);

		Brain &operator=(Brain const &rhs);

		// getter
		std::string getIdea(int i) const;

		// setter
		void setIdea(const std::string &idea, int i);

};

#endif