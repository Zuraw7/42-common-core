#include <iostream>
#include "../includes/Serializer.hpp"

Serializer::Serializer() {};
Serializer::~Serializer() {};
Serializer::Serializer(Serializer const &src) {*this = src;}
Serializer &Serializer::operator=(Serializer const &rhs) {
	if (this != &rhs) {
		// nothing to assign
	}
	return *this;
}

uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

