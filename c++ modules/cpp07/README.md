# C++ Module 07

## About the Project

In this module, I delve into **templates** in C++, exploring how to write type-independent code with maximum flexibility and type safety. The tasks guide me through implementing generic functions (`swap`, `min`, `max`), a higher-order function that applies a given function to all elements in an array (`iter`), and finally, a custom class template (`Array`) that mimics standard container behavior with safety and robustness. These exercises build foundational knowledge in template programming and deepen my grasp on generic design patterns in C++.

---

## Main Goals of the Project

1. **Function Templates**
   - Implement `swap`, `min`, and `max` as fully generic functions.
   - Ensure they support any type with valid comparison and assignment operations.

2. **Higher-Order Function with Templates**
   - Implement `iter`, a function that takes an array and a callable to apply to each element.
   - Ensure compatibility with arrays of any type and functions with any side effects.

3. **Class Template: Custom Array**
   - Build a generic `Array<T>` class with proper memory management.
   - Handle deep copies and ensure bounds-checked element access.
   - Implement exception safety and robust object lifecycle management.

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

By completing this module, I’ve developed a strong foundation in C++ **template programming**. Writing type-agnostic functions and classes pushed me to think in terms of **reusability**, **type safety**, and **modularity**. From simple comparisons to generic arrays, each task showcased how C++ templates enable clean, extensible, and powerful abstractions—essential for modern software design.

---
