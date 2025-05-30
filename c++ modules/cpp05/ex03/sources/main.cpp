#include <iostream>
#include "../includes/Intern.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

void testValidForms();
void testInvalidForm();
void testMultipleForms();
void testCopyAndAssign();

int main() {
    testValidForms();
    std::cout << std::endl;

    testInvalidForm();
    std::cout << std::endl;

    testMultipleForms();
    std::cout << std::endl;

    testCopyAndAssign();
    std::cout << std::endl;

    return 0;
}

// **Test poprawnego tworzenia formularzy przez Interna**
void testValidForms() {
    std::cout << "========Test: Intern Creates Valid Forms========" << std::endl;

    Intern intern;

    try {
        AForm *form1 = intern.makeForm("shrubbery creation", "Garden");
        AForm *form2 = intern.makeForm("robotomy request", "Bender");
        AForm *form3 = intern.makeForm("presidential pardon", "Alice");

        std::cout << std::endl;
        if (form1)
            std::cout << *form1 << std::endl;
        if (form2)
            std::cout << *form2 << std::endl;
        if (form3)
            std::cout << *form3 << std::endl;

        delete form1;
        delete form2;
        delete form3;
    } catch (std::exception &e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
}

// **Test błędnej nazwy formularza (obsługa wyjątku)**
void testInvalidForm() {
    std::cout << "========Test: Intern Handles Invalid Form========" << std::endl;

    Intern intern;

    try {
        AForm *invalidForm = intern.makeForm("unknown form", "ErrorTest");
        std::cout << "Error: Intern created an invalid form!" << std::endl;
        delete invalidForm;
    } catch (const std::exception &e) {
        std::cout << "Intern couldn't make a form due to: " << e.what() << std::endl;
    }
}

// **Test tworzenia wielu formularzy pod rząd (czy nie ma wycieków pamięci)**
void testMultipleForms() {
    std::cout << "========Test: Intern Creates Multiple Forms========" << std::endl;

    Intern intern;

    for (int i = 0; i < 10; i++) {
        try {
            AForm *form = intern.makeForm("robotomy request", "TestTarget_" + i);
            std::cout << "Created form " << i << " -> " << *form << std::endl;
            delete form;
        } catch (std::exception &e) {
            std::cout << "Unexpected exception in loop: " << e.what() << std::endl;
        }
    }
}

// **Test kopiowania i przypisania Interna (nieistotne, ale dla formalności)**
void testCopyAndAssign() {
    std::cout << "========Test: Intern Copy and Assignment========" << std::endl;

    Intern original;
    Intern copy(original);
    Intern assigned;
    assigned = original;

    std::cout << std::endl;
    try {
        AForm *form = assigned.makeForm("shrubbery creation", "Park");
        std::cout << *form << std::endl;
        delete form;
    } catch (std::exception &e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
}
