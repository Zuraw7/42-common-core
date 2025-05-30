# C++ Module 06

## About the Project

In this module, I focus on advanced casting and type manipulation in C++. The exercises guide me through creating a **ScalarConverter** that interprets string literals (including special values like **inf** and **nan**) and converts them into various scalar types (**char**, **int**, **float**, **double**), implementing a **Serializer** that can turn a pointer into an unsigned integer and back again without losing the original address, and finally identifying an object’s real type through a **Base** pointer or reference—without relying on **std::typeinfo**. These tasks deepen my understanding of pointer manipulation, type conversions, and object-oriented features in C++.

---

## Main Goals of the Project

1. **Advanced Casting and Conversions**
   - Converting string literals into multiple scalar types.
   - Handling special floating-point values (**inf**, **nan**) gracefully.

2. **Pointer Serialization**
   - Serializing pointers to **uintptr_t** and restoring them, ensuring address integrity.

3. **Type Identification without RTTI**
   - Detecting an object’s real type from a base pointer or reference.
   - Avoiding **std::typeinfo** to deepen understanding of polymorphism.

4. **Robust OOP Practices**
   - Applying polymorphism in a clean, extensible design.
   - Focusing on clarity, error handling, and maintainable code.

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

By working through these exercises, I’ve strengthened my grasp on C++ casting, type identification, and pointer operations. Each task—from converting string literals to handling serialization and polymorphic type detection—demonstrates the power of low-level control and robust OOP design. This knowledge lays a solid foundation for tackling more complex C++ challenges in the future.

---
