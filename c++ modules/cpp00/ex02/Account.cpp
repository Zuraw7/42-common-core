#include <iostream>
#include "./Account.hpp"

// Constructor and Destructor
Account::Account(int initial_deposit) : _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
	Account::_displayTimestamp();
	_accountIndex = Account::_nbAccounts++;
	_totalAmount += _amount;
	std::cout	<< "index:" << _accountIndex
				<< ";amount:" << _amount
				<< ";created" << std::endl;
}

Account::~Account(void) {
	Account::_displayTimestamp();
	std::cout	<< "index:" << _accountIndex
				<< ";amount:" << _amount
				<< ";closed" << std::endl;
}

// Static Private Methods
void Account::_displayTimestamp(void) {
	std::cout << "[20250113_204733] ";
}

// Static Public Methods
void Account::displayAccountsInfos(void) {
	Account::_displayTimestamp();
	std::cout	<< "accounts:" << _nbAccounts
				<< ";total:" << _totalAmount
				<< ";deposits:" << _totalNbDeposits
				<< ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

// Methods
void Account::makeDeposit(int deposit) {
	int p_amount = _amount;

	Account::_displayTimestamp();
	_amount += deposit;
	_totalAmount += deposit;
	_nbDeposits++;
	_totalNbDeposits++;
	std::cout	<< "index:" << _accountIndex
				<< ";p_amount:" << p_amount
				<< ";deposit:" << deposit
				<< ";amount:" << _amount
				<< ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << _amount
			  << ";withdrawal:";
	if (_amount < withdrawal) {
		std::cout << "refused" << std::endl;
		return false;
	}
	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	_nbWithdrawals++;
	_totalNbWithdrawals++;
	std::cout << withdrawal
			  << ";amount:" << _amount
			  << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return true;
}

int Account::checkAmount(void) const {
	return _amount;
}

void Account::displayStatus(void) const {
	Account::_displayTimestamp();
	std::cout	<< "index:" << _accountIndex
				<< ";amount:" << _amount
				<< ";deposits:" << _nbDeposits
				<< ";withdrawals:" << _nbWithdrawals << std::endl;
}

// Setters
int Account::getNbAccounts(void) {
	return _nbAccounts;
}

int Account::getTotalAmount(void) {
	return _totalAmount;
}

int Account::getNbDeposits(void) {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
	return _totalNbWithdrawals;
}

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;
