#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include "./Character.hpp"

class ICharacter;

class AMateria
{
	protected:
		std::string _type;
	
	public:
		AMateria();
		AMateria(std::string const & type);
		AMateria(AMateria const &src);
		virtual ~AMateria();

		AMateria &operator=(AMateria const &rhs);

		std::string const & getType() const; //Returns the materia type
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

class Ice : public AMateria {
	public:
		Ice();
		Ice(Ice const &src);
		~Ice();

		Ice &operator=(Ice const &rhs);

		AMateria* clone() const;
		void use(ICharacter& target);
};

class Cure : public AMateria {
	public:
		Cure();
		Cure(Cure const &src);
		~Cure();

		Cure &operator=(Cure const &rhs);

		AMateria* clone() const;
		void use(ICharacter& target);
};

#endif