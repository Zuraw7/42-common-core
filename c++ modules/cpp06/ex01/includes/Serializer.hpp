#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <stdint.h>

struct Data {
	public:
		int value;
		std::string name;
};

class Serializer {
	private:
		Serializer();
		~Serializer();
		Serializer(Serializer const &src);
		Serializer &operator=(Serializer const &rhs);

	public:
		static uintptr_t serialize(Data* const ptr);
		static Data *deserialize(uintptr_t const raw);
};

#endif