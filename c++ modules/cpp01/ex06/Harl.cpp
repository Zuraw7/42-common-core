#include <iostream>
#include "Harl.hpp"

Harl::Harl(void) {
}

Harl::~Harl(void) {
}

void Harl::debug(void) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl << std::endl;
}

void Harl::info(void) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" << std::endl << std::endl;
}

void Harl::warning(void) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I've been coming for years whereas you started working here since last month." << std::endl << std::endl;
}

void Harl::error(void) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}

void Harl::complain(std::string level) {
	void (Harl::*complainPTR[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	int	levelIndex = -1;

	for (int i = 0; i < 4; i++) {
		if (level == levels[i]) {
			levelIndex = i;
			break ;
		}
	}

	switch (levelIndex)
	{
		case 0:
			(this->*complainPTR[0])();
			// fall-through
		case 1:
			(this->*complainPTR[1])();
			// fall-through
		case 2:
			(this->*complainPTR[2])();
			// fall-through
		case 3:
			(this->*complainPTR[3])();
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
	}

}