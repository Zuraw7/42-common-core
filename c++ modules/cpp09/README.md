# C++ Module 09

## About the Project

This module focuses on creating real-world, algorithm-heavy tools using C++ and STL containers. It involves parsing structured files, implementing custom algorithms, and comparing performance between different data structures. The goal is to build practical, efficient, and accurate applications that reinforce algorithmic thinking and container manipulation.

---

## Main Goals of the Project

**Exercise 00: Bitcoin Exchange**
- Implement a program `btc` that:
   - Reads inout in the format `date | value`.
   - Uses a reference CSV database pf historical Bitcoin exchange rates.
   - Calculate the value of a given amount of BTC on a given date.
   - If the exact date is not present in the database, it uses closest earlier date.
- Handles the following edge cases:
   - Invalid dates or formats.
   - Negative numbers.
   - Extremely large values.
- Implements robust error handling and output that reflects real-time data lookups.

**Skills Practiced:**
- CSV parsing
- Data validation
- Lower bound search using `std::map`
- Error handling

**Exercise 01: Reverse Polish Notation (RPN)**
- Create an executable `RPN` that:
   - Takes an expression in Reverse Polish Notation as a command-line argument.
   - Uses a stack to evaluate the expression.
   - Supports the four basic arithmetic operations: `+`, `-`, `*`, `/`.
   - Handles errors (invalid input, division by zero, bad format).
   - Ignores brackets and floating-point numbers — integer-only math.
**Example**
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# Output: 42
```

**Skills Practiced:**
- Stack-based evaluation
- Token parsing
- Robust input checking

**Exercise 02: PmergeMe (Ford-Johnson Sort)**
- Implement `PmergeMe`, a tool that:
   - Accepts a sequence of positive integers.
   - Sorts them using **Merge-Insertion Sort (Ford-Johnson algorithm)**.
   - Uses two different containers (std::vector and std::deque).
   - Benchmarks and prints the processing time for each container separately.
   - Handles up to 3000+ integers efficiently.

**Skills Practiced:**
- High-performance sorting
- STL containers benchmarking
- Algorithm implementation from theory (Ford-Johnson sort)

---

## Downloading the Project

To download the project to your computer, follow these steps:

1. Clone the repository using `git`:
```bash
   git clone <repository_link>
   cd <repository_folder_name>
```

2. Navigate to the appropriate subfolder (e.g., `ex00`, `ex01`, or `ex02`) to check a specific task.

---

## Summary

This module was an in-depth exercise in building practical tools using C++, with a strong focus on:
- **File I/O**
- **Error handling**
- **Custom algorithm implementation**
- **STL mastery**
- **Performance benchmarking**
The `BitcoinExchange` project mirrors real-life data tools, `RPN` sharpens stack and parsing skills, while `PmergeMe` offers deep insight into classic algorithm optimization.

---
