# C++ Module 08

## About the Project

This module explores advanced usage of **C++ templates** in combination with **STL containers**, exception handling, and container adaptation. Each exercise dives deeper into writing robust, reusable, and safe code using the standard library’s power. I implement generic algorithms and container-like classes that stretch the limits of traditional STL behaviors, like adding iterators to `std::stack` or efficiently finding value spans in sequences of integers.

---

## Main Goals of the Project

1. **Generic Search in Containers**
   - Implement `easyfind`, a function template to search for an integer value inside any STL-like container of integers.
   - Handle error scenarios gracefully (e.g., throw an exception if not found).

2. **Span Class for Numeric Ranges**
   - Implement a `Span` class that stores up to `N` integers.
   - Add methods `shortestSpan()` and `longestSpan()` to calculate differences between stored numbers.
   - Enforce capacity constraints with exceptions.
   - Add support for bulk insertion via iterator ranges.

3. **Iterable Stack: MutantStack**
   - Create `MutantStack`, a wrapper around `std::stack` that exposes iterators.
   - Maintain all original stack functionality while making it iterable like a sequence container.
   - Ensure the implementation is compatible with algorithms that work on standard iterators.

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

In this module, I’ve solidified my understanding of **template specialization**, **container manipulation**, and **custom STL-like class design**. Whether by enhancing `std::stack` with iteration support or analyzing numeric spans efficiently, each task helped refine my ability to write expressive and powerful C++ code. These techniques are vital for creating high-performance and flexible systems using modern C++ standards.

---
