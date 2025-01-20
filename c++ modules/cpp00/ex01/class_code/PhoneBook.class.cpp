#include <iostream>
#include <iomanip>
#include "../class_headers/PhoneBook.class.hpp"
#include "../class_headers/Contact.class.hpp"


// Constructor and Destructor
PhoneBook::PhoneBook(void) {
	this->_index = 0;

	return;
}

PhoneBook::~PhoneBook(void) {
	PhoneBook::_nbContacts--;
	return;
}

// Methods

/*
	1. Adds a contact to the PhoneBook
		- sets the index of the contact
		- increments the number of contacts if less than 8
		- increments the index
			- if index is greater than 7, it sets it to 0
*/
void PhoneBook::addContact(Contact contact) {

	this->_contacts[this->_index] = contact;
	if (PhoneBook::_nbContacts < 8)
		PhoneBook::_nbContacts++;
	this->_contacts[this->_index].setIndex(this->_index);
	this->_index = (this->_index + 1) % 8;
	return;
}

/*
	1. Searches for a contact in the PhoneBook
		- checks if the index is valid
		- displays the contact details
*/
void PhoneBook::searchContact(int index) {
	if (index < 0 || index >= PhoneBook::_nbContacts)
	{
		std::cout << "Invalid index" << std::endl;
		return;
	}
	this->_contacts[index].displayDetails();
	return;
}

/*
	1. Displays the contact details
		- checks if the length of the string is greater than 10
			if so, it cuts the string and adds "."
		- displays the contact details
*/
void	PhoneBook::showContacts(void) {
	std::string fName;
	std::string	lName;
	std::string	nName;

	std::cout << std::setw(10) << std::right << "Index" << "|"
			<< std::setw(10) << std::right << "Full name" << "|"
			<< std::setw(10) << std::right << "Last name" << "|"
			<< std::setw(10) << std::right << "Nickname" << std::endl;

	for (int i = 0; i < PhoneBook::_nbContacts; i++)
	{
		fName = this->_contacts[i].getFirstName();
		lName = this->_contacts[i].getLastName();
		nName = this->_contacts[i].getNickName();

		if (fName.length() > 10)
			fName = fName.substr(0, 9) + ".";
		if (lName.length() > 10)
			lName = lName.substr(0, 9) + ".";
		if (nName.length() > 10)
			nName = nName.substr(0, 9) + ".";

		std::cout << std::setw(10) << std::right << this->_contacts[i].getIndex() << "|"
			<< std::setw(10) << std::right << fName << "|"
			<< std::setw(10) << std::right << lName << "|"
			<< std::setw(10) << std::right << nName << std::endl;
	}
}

// Static variable
int PhoneBook::_nbContacts = 0;
