#include <iostream>
#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name);

int main(void) {
	int N = 10;
	Zombie *horde = zombieHorde(N, "Moar");

	if (!horde)
		return 1;

	// check if there is N zombies in horde
	for (int i = 0; i < N; i++) {
		std::cout << "Zombie no:" << i + 1 << " ";
		horde[i].announce();
	}

	delete [] horde;

	return 0;
}