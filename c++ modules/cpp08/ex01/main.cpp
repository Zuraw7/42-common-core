#include <iostream>
#include <vector>
#include <cstdlib>  // rand()
#include <ctime>    // time()
#include "Span.hpp"

void testAddSingleNumbers();
void testAddMultipleNumbers();
void testLargeSpan();
void testExceptions();

int main() {
    testAddSingleNumbers();
    testAddMultipleNumbers();
    testLargeSpan();
    testExceptions();
    return 0;
}

void testAddSingleNumbers() {
    std::cout << "Test: Adding single numbers" << std::endl;
    Span sp(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    try {
        sp.addNumber(13);
        std::cerr << "Error: Expected an exception!" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Exception caught as expected: " << e.what() << std::endl;
    }

    std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
    std::cout << "longestSpan: " << sp.longestSpan() << std::endl;
    std::cout << "Test passed.\n" << std::endl;
}

void testAddMultipleNumbers() {
    std::cout << "Test: Adding multiple numbers" << std::endl;
    Span sp(10);

    int arr[] = {1, 4, 7, 10, 15, 20, 25, 30, 35, 40};
    std::vector<int> numbers(arr, arr + 10);

    sp.addNumber(numbers.begin(), numbers.end());

    std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
    std::cout << "longestSpan: " << sp.longestSpan() << std::endl;
    std::cout << "Test passed.\n" << std::endl;
}

void testLargeSpan() {
    std::cout << "Test: Large set of numbers (10,000)" << std::endl;
    Span sp(10000);
    std::vector<int> numbers;

    srand(time(0));
    for (int i = 0; i < 10000; i++) {
        numbers.push_back(rand() % 1000000);
    }

    sp.addNumber(numbers.begin(), numbers.end());

    std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
    std::cout << "longestSpan: " << sp.longestSpan() << std::endl;
    std::cout << "Test passed.\n" << std::endl;
}

void testExceptions() {
    std::cout << "Test: Exception handling" << std::endl;
    Span sp(5);

    try {
        sp.shortestSpan();
        std::cerr << "Error: Expected an exception for empty Span!" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Exception caught as expected: " << e.what() << std::endl;
    }

    sp.addNumber(42);

    try {
        sp.shortestSpan();
        std::cerr << "Error: Expected an exception for Span with one element!" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Exception caught as expected: " << e.what() << std::endl;
    }

    std::cout << "Test passed.\n" << std::endl;
}
