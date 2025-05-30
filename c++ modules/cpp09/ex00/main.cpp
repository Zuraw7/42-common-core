#include "BitcoinExchange.hpp"

int checkFile(std::ifstream &file, char *filename);
void calculateBTC(std::ifstream &file, BitcoinExchange &btc);
std::string trim(const std::string &str);

int main (int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: ./btc <btcExchangeRateFile>" << std::endl;
		return 1;
	}

	BitcoinExchange btc;
	const char *dataFile = "cpp_09/data.csv";

	try {
		btc.loadData(dataFile);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	if (checkFile(file, argv[1])) {
		file.close();
		return 1;
	}

	calculateBTC(file, btc);

	file.close();

	return 0;
}

int checkFile(std::ifstream &file, char *filename) {
	if (!file) {
		std::cout << "Error: Unable to open file " + std::string(filename) << std::endl;
		return 1;
	}
	std::string line;
	std::getline(file, line);
	if (line != "date | value") {
		std::cout << "Error: Incorrect title structure" << std::endl;
	}
	return 0;
}

std::string trim(const std::string &str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(" \t\n\r\f\v");
	return str.substr(first, last - first + 1);
}

void calculateBTC(std::ifstream &file, BitcoinExchange &btc) {
	std::string line;

	while (std::getline(file, line)) {
		if (trim(line).empty()) {
			std::cout << "Error: empty line" << std::endl;
			continue;
		}

		std::istringstream ss(line);
		std::string date, valueStr;
		char pipe;
		double amount;

		ss >> date;
		ss >> pipe;
		ss >> valueStr;

		date = trim(date);
		valueStr = trim(valueStr);

		std::istringstream valueStream(valueStr);
		if (!isValidDate(date) || pipe != '|' || !(valueStream >> amount)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (amount < 0) {
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		
		if (amount > 1000) {
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		double rate;
		try {
			rate = btc.getData(date);
		} catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		if (rate < 0 ) {
			std::cerr << "Error: No exchange rate for " << date << std::endl;
			continue;
		}

		std::cout << date << " => " << amount << " = " << (amount * rate) << std::endl;
	}
}