#include <iostream>
#include <fstream>

void replace(std::string line, std::ofstream &outfile, const std::string s1, const std::string s2) {
	size_t pos = 0, found;	// pos -> starting position, found -> s1 starting position
	std::string result;		// line with replaced s1 by s2

	while ((found = line.find(s1, pos)) != std::string::npos) {
		result.append(line, pos, found - pos);
		result.append(s2);
		pos = found + s1.length();
	}

	result.append(line, pos, line.length() - pos);
	outfile << result << std::endl;
}

int main (int argc, char **argv) {

	// Input check
	if (argc != 4) {
		std::cout << "Wrong parameters!" << std::endl << "./sed <filename> <string1> <string2>" << std::endl;
		return 1;
	}

	// Open input file
	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cout << "Error: " << argv[1] << ": no such file or directory" << std::endl;
		return 1;
	}

	// Open output file
	std::ofstream outfile((std::string(argv[1]) + ".replace").c_str());
	if (!outfile.is_open()) {
		std::cout << "Error: Cannot create output file." << std::endl;
		return 1;
	}

	// Reading file, line by line
	std::string line;
	while (std::getline(infile, line)) {
		replace(line, outfile, argv[2], argv[3]);
	}
	
	// Closing files
	infile.close();
	outfile.close();

	return 0;
}