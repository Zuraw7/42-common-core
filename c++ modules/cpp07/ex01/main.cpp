#include <iostream>
#include "./iter.hpp"

int main (void) {
	size_t x = 5;
    int arr1[] = { 1, 2, 3, 4, 5 };

    std::cout << "arr1: " << std::endl;
    iter(arr1, x, &print);

    double arr2[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

    std::cout << "arr2: " << std::endl;
    iter(arr2, x, &print);

    char arr3[] = { 'a', 'b', 'c', 'd', 'e' };

    std::cout << "arr3: " << std::endl;
    iter(arr3, x, &print);

    std::string arr4[] = { "one", "two", "three", "four", "five" };

    std::cout << "arr4: " << std::endl;
    iter(arr4, x, &print);

    return 0;
}
