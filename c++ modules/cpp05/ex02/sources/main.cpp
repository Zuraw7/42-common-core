#include <iostream>
#include "../includes/Bureaucrat.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"

void testFormCreation();
void testSignFormSuccess();
void testSignFormFail();
void testExecuteFormSuccess();
void testExecuteFormFail();
void testExecuteUnsignedForm();

int main() {
    testFormCreation();
    std::cout << std::endl;

    testSignFormSuccess();
    std::cout << std::endl;

    testSignFormFail();
    std::cout << std::endl;

    testExecuteFormSuccess();
    std::cout << std::endl;

    testExecuteFormFail();
    std::cout << std::endl;

    testExecuteUnsignedForm();
    std::cout << std::endl;

    return 0;
}

// **Test tworzenia formularzy**
void testFormCreation() {
    std::cout << "========Test: Form Creation========" << std::endl;

    try {
        PresidentialPardonForm ppForm("Alice");
        RobotomyRequestForm rrForm("Bob");
        ShrubberyCreationForm scForm("Charlie");

        std::cout << ppForm << std::endl;
        std::cout << rrForm << std::endl;
        std::cout << scForm << std::endl;
    } catch (std::exception &e) {
        std::cout << "Form creation failed: " << e.what() << std::endl;
    }
}

// **Test podpisywania formularzy**
void testSignFormSuccess() {
    std::cout << "========Test: Sign Form Success========" << std::endl;

    Bureaucrat jeff("Jeff", 1);
    PresidentialPardonForm form("Alice");

    try {
        jeff.signForm(form);
        std::cout << form << std::endl; // Form should be signed
    } catch (std::exception &e) {
        std::cout << "Failed to sign the form: " << e.what() << std::endl;
    }
}

void testSignFormFail() {
    std::cout << "========Test: Sign Form Fail========" << std::endl;

    Bureaucrat bob("Bob", 150);
    RobotomyRequestForm form("Charlie");

    try {
        bob.signForm(form); // Bob can't sign, grade too low
        std::cout << form << std::endl;
    } catch (std::exception &e) {
        std::cout << "Failed to sign the form: " << e.what() << std::endl;
    }
}

// **Test wykonywania formularzy**
void testExecuteFormSuccess() {
    std::cout << "========Test: Execute Form Success========" << std::endl;

    Bureaucrat jeff("Jeff", 1);
    PresidentialPardonForm ppf("Alice");
    RobotomyRequestForm rrf("Garry");
    ShrubberyCreationForm scf("Rick");

    try {
        jeff.signForm(ppf);
        jeff.executeForm(ppf);
    } catch (std::exception &e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    try {
        jeff.signForm(rrf);
        jeff.executeForm(rrf);
    } catch (std::exception &e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    try {
        jeff.signForm(scf);
        jeff.executeForm(scf);
    } catch (std::exception &e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    std::cout << std::endl;
}

void testExecuteFormFail() {
    std::cout << "========Test: Execute Form Fail========" << std::endl;

    Bureaucrat bob("Bob", 150);
    RobotomyRequestForm form("Charlie");

    try {
        bob.executeForm(form); // Bob can't execute, grade too low
    } catch (std::exception &e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
}

// **Test wykonywania formularza, który nie został podpisany**
void testExecuteUnsignedForm() {
    std::cout << "========Test: Execute Unsigned Form========" << std::endl;

    Bureaucrat jeff("Jeff", 1);
    ShrubberyCreationForm form("Garden");

    try {
        jeff.executeForm(form); // Form is not signed
    } catch (std::exception &e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
}
