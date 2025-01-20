#ifndef	CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

#include <iostream>

class Contact {
	private:
		// Contact informations
		int	_index;
		std::string	_phoneNumber;
		std::string _firstName;
		std::string _lastName;
		std::string _nickName;
		std::string _darkestSecret;

	public:
		// Constructor and Destructor
		Contact(void);
		~Contact(void);
		
		// Setters
		void setIndex(int index);
		void setPhoneNumber(std::string phoneNumber);
		void setFirstName(std::string firstName);
		void setLastName(std::string lastName);
		void setNickName(std::string nickName);
		void setDarkestSecret(std::string darkestSecret);

		// Getters
		int getIndex(void);
		std::string getPhoneNumber(void);
		std::string getFirstName(void);
		std::string getLastName(void);
		std::string getNickName(void);
		std::string getDarkestSecret(void);

		// Methods
		void displayDetails(void);
};

#endif