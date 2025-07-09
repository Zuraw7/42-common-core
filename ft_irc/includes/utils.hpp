#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

bool	isIn(char needle, const char *haystack);
std::size_t	ft_strlen(const char string[]);
int	ft_atoi(const std::string &num);
std::vector<std::string> split(const std::string &str, char delimiter);
bool	isDigits(std::string string, char begin_after, char end_before);
bool isValidNumber(const std::string &str);
int checkArgv(int argc, char **argv, int &port);