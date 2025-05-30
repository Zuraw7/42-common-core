#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <map>
#include <ostream>
#include <cstring>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>
#include <cctype>

bool isCSV(const char *filename);
bool isValidDate( const std::string &date);
int parseData(std::map<std::string, double> &data, std::string line);

class BitcoinExchange {
	private:
		std::map<std::string, double> data;


	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &src);
		~BitcoinExchange();

		BitcoinExchange &operator=(BitcoinExchange const &rhs);

		double getData(std::string const &date) const;
		void loadData(const char *filename);
};

#endif