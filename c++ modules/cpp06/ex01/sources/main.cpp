#include <iostream>
#include "../includes/Serializer.hpp"

void makeTest(Data *data) {
	Data *deserialized;
	uintptr_t raw;
	
	raw = Serializer::serialize(data);
	std::cout << "Raw: " << raw << std::endl;
	deserialized = Serializer::deserialize(raw);
	std::cout << "Deserialized data address " << deserialized << std::endl << "Name: " << deserialized->name << std::endl << "Value: " << deserialized->value << std::endl;
	if (data == deserialized) {
		std::cout << "Addresses are the same, deserialize succeeded" << std::endl;
	} else {
		std::cout << "Addresses are different! Deserialize failed!" << std::endl;
	}
}

int main (void) {
	Data data;

	data.name = "random data";
	data.value = 42;

	std::cout << "Data structure: " << std::endl << "Name: " << data.name << std::endl << "Value: " << data.value << std::endl;

	std::cout << std::endl;

	std::cout << "First serialize and deserialize: " << std::endl;
	makeTest(&data);

	std::cout << std::endl;

	std::cout << "Second serialize and deserialize: " << std::endl;
	makeTest(&data);

	return 0;
}