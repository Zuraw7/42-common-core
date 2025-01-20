#include <iostream>
#include <sstream>
#include "./class_headers/PhoneBook.class.hpp"
#include "./class_headers/Contact.class.hpp"

Contact	create_contact();
int check_phonenumber(std::string phoneNumber);
bool string_to_int(std::string &str, int &num);

/*
	Program explanation
		- while loop to keep the program running
		- getting user input
		- if and else if to choose an action
		- running functions
			- ADD - create a new Contact object and add it to PhoneBook
			- SEARCH - search for a Contact object in PhoneBook
			- EXIT - exit the program
*/
int	main (void)
{
	PhoneBook phoneBook;
	std::string command;
	std::string tmp_index;
	int index;

	while (true) {
		
		std::cout << "Please enter a command: ADD, SEARCH or EXIT" << std::endl;

		if (!std::getline(std::cin, command)) {
			if (std::cin.eof()) {
				std::cout << "CTRL+D detected. Exiting program." << std::endl;
				break;
			}
			else {
				std::cout << "Invalid input, try again" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				continue;
			}
		}

		// Creates a new contact and adds it to phoneBook, in case of empty input, it catches the exception
		if (command == "ADD") {
			try {
				phoneBook.addContact(create_contact());
				std::cout << "Contact added" << std::endl;
			}
			catch (...) {
				std::cout << "Invalid contact" << std::endl;
			}
		}
		// Takes user input, checks if it's a number and runs searchContact
		else if (command == "SEARCH") {
			phoneBook.showContacts();

			std::cout << "Enter index to search: ";
			std::getline(std::cin, tmp_index);
			if (tmp_index.empty()) {
				std::cout << "Invalid index" << std::endl;
				continue;
			}
			if (string_to_int(tmp_index, index)) {
				phoneBook.searchContact(index);
			}
			else {
				std::cout << "Invalid index" << std::endl;
			}
		}
		else if (command == "EXIT") {
			std::cout << "Exiting program" << std::endl;
			break;
		}
		else {
			std::cout << "Invalid command" << std::endl;
		}
	}

	return 0;
}

Contact	create_contact() {
	Contact contact;
	std::string phoneNumber;
	std::string firstName;
	std::string lastName;
	std::string nickName;
	std::string darkestSecret;

	std::cout << "Please enter the phone number: ";
	std::getline(std::cin, phoneNumber);
	contact.setPhoneNumber(phoneNumber);

	std::cout << "Please enter the first name: ";
	std::getline(std::cin, firstName);
	contact.setFirstName(firstName);

	std::cout << "Please enter the last name: ";
	std::getline(std::cin, lastName);
	contact.setLastName(lastName);

	std::cout << "Please enter the nick name: ";
	std::getline(std::cin, nickName);
	contact.setNickName(nickName);

	std::cout << "Please enter the darkest secret: ";
	std::getline(std::cin, darkestSecret);
	contact.setDarkestSecret(darkestSecret);

	if (phoneNumber.empty() || firstName.empty() || lastName.empty()
		|| nickName.empty() || darkestSecret.empty() || check_phonenumber(phoneNumber)) {
		throw std::runtime_error("Invalid contact");
	}

	return contact;
}

int check_phonenumber(std::string phoneNumber) {
	char c;

	c = phoneNumber[0];
	if (c != '+' && !std::isdigit(c)) {
		return 1;
	}
	for (size_t i = 1; i < phoneNumber.length(); i++) {
		if (!std::isdigit(phoneNumber[i])) {
			return 1;
		}
	}
	return 0;
}

bool string_to_int(std::string &str, int &num) {
	std::stringstream ss(str);
	
	ss >> num;
	if (ss.fail() || !ss.eof()) {
		return false;
	}
	return true;
}
