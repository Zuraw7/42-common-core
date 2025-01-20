#include <iostream>
#include "../class_headers/Contact.class.hpp"

// Constructor and Destructor
Contact::Contact(void) {
	this->_index = 0;
	this->_phoneNumber = "";
	this->_firstName = "";
	this->_lastName = "";
	this->_nickName = "";
	this->_darkestSecret = "";

	return;
}

Contact::~Contact(void) {
	return;
}

// Methods
void	Contact::displayDetails(void) {
	std::string phoneNumber;
	std::string firstName;
	std::string lastName;
	std::string nickName;
	std::string darkestSecret;

	std::cout << std::endl << "Contact info:" << std::endl;
	std::cout << "Phone number:" << this->getPhoneNumber() << std::endl;
	std::cout << "First name:" << this->getFirstName() << std::endl;
	std::cout << "Last name:" << this->getLastName() << std::endl;
	std::cout << "Nickname:" << this->getNickName() << std::endl;
	std::cout << "Darkest secret:" << this->getDarkestSecret() << std::endl << std::endl;
}

// Setters
void Contact::setIndex(int index) {
	this->_index = index;
	return;
}

void Contact::setPhoneNumber(std::string phoneNumber) {
	this->_phoneNumber = phoneNumber;
	return;
}

void Contact::setFirstName(std::string firstName) {
	this->_firstName = firstName;
	return;
}

void Contact::setLastName(std::string lastName) {
	this->_lastName = lastName;
	return;
}

void Contact::setNickName(std::string nickName) {
	this->_nickName = nickName;
	return;
}

void Contact::setDarkestSecret(std::string darkestSecret) {
	this->_darkestSecret = darkestSecret;
	return;
}

// Getters
int Contact::getIndex(void) {
	return this->_index;
}

std::string Contact::getPhoneNumber(void) {
	return this->_phoneNumber;
}

std::string Contact::getFirstName(void) {
	return this->_firstName;
}

std::string Contact::getLastName(void) {
	return this->_lastName;
}

std::string Contact::getNickName(void) {
	return this->_nickName;
}

std::string Contact::getDarkestSecret(void) {
	return this->_darkestSecret;
}
