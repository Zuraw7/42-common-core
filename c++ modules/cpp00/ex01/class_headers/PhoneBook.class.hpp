#ifndef PHONEBOOK_CLASS_HPP
# define PHONEBOOK_CLASS_HPP

#include <iostream>
#include "./Contact.class.hpp"

class PhoneBook {
	private:
		Contact 	_contacts[8];
		static int	_nbContacts;
		int			_index;
	
	public:
		// Constructor and Destructor
		PhoneBook();
		~PhoneBook();

		// Methods
		void addContact(Contact contact);
		void searchContact(int index);
		void showContacts(void);
};

#endif