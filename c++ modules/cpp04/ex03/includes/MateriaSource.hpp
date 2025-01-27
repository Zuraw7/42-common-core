#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <iostream>
#include "./AMateria.hpp"

class IMateriaSource {
	public:
		virtual ~IMateriaSource() {}
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};

class MateriaSource : public IMateriaSource {
	private:
		AMateria *_knownMateria[4];
		AMateria **_overflow;
		int _overflowSize;

	public:
		MateriaSource();
		MateriaSource(MateriaSource const &src);
		~MateriaSource();

		MateriaSource &operator=(MateriaSource const &rhs);

		void learnMateria(AMateria*);
		AMateria* createMateria(std::string const & type);
};

#endif