#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) {
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
	if (this !=&rhs) {
		this->data = rhs.data;
	}
	return *this;
}

// returns exchange rate form given date or previous if not found
double BitcoinExchange::getData(std::string const &date) const {
	/*
		lower_bound returns >= given date
		is if it finds exact date it returns if
		if not it returns first higher date
	*/
	if (date.size() > 10) {
		throw std::runtime_error("Error: Incorrect data structure");
	}

	std::map<std::string, double>::const_iterator it = this->data.lower_bound(date);

	if (it != this->data.end() && it->first == date) {
		return it->second;
	}

	if (it == this->data.begin()) {
		throw std::runtime_error("Error: No exchange rate available for " + date);
	}

	--it;
	return it->second;
}

bool isCSV(const char *filename) {
	const char *basename = std::strrchr(filename, '/');
	if (basename) {
		filename = basename + 1;
	}

	size_t len = std::strlen(filename);
	if (len < 4) {
		return false;
	}
	return std::strcmp(filename + len - 4, ".csv") == 0;
}

bool isValidDate( const std::string &date) {
	// check if YYYY-MM-DD
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}
	
	// check if numbers only excluding dashes
	for (int i = 0; i < static_cast<int>(date.size()); i++) {
		if ((i != 4 && i != 7) && !std::isdigit(date[i])) {
			return false;
		}
	}

	int year, month, day;
	char dash1, dash2;
	std::istringstream ss(date);
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (!(ss >> year >> dash1 >> month >> dash2 >> day)) {
		return false;
	}

	std::string extra;
	if (ss >> extra) {
		return false;
	}
	if (month < 1 || month > 12 || day < 1) {
		return false;
	}
	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
		daysInMonth[1] = 29;
	}
	if (day > daysInMonth[month - 1]) {
		return false;
	}
	return true;
}

int parseData(std::map<std::string, double> &data, std::string line) {
	std::istringstream ss(line);
	std::string date;
	double price;

	if (!std::getline(ss, date, ',') || date.empty()) {
		return 1;
	}
	if (!(ss >> price)) {
		return 1;
	}

	std::string extra;
	if (ss >> extra || !isValidDate(date)) {
		return 2;
	}
	data[date] = price;

	return 0;
}

void BitcoinExchange::loadData(const char *filename) {
	if (!isCSV(filename)) {
		throw std::invalid_argument("Error: Please provide a .csv file.");
	}

	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Error: Unable to open file " + std::string(filename));
	}

	std::string line;

	getline(file, line);
	if (line != "date,exchange_rate") {
		throw std::invalid_argument("Error: Invalid column format");
	}

	while (std::getline(file, line)) {
		int parseDataSignal = parseData(this->data, line);
		if (parseDataSignal == 1) {
			throw std::invalid_argument("Error: Incorrect line format");
		} else if (parseDataSignal == 2) {
			throw std::invalid_argument("Error: Incorrect data");
		}
	}

}