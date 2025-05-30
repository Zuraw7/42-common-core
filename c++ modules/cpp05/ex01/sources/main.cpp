#include <iostream>
#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"

void testFormCreation();
void testFormGradeTooHigh();
void testFormGradeTooLow();
void testFormBeSignedSuccess();
void testFormBeSignedFail();
void testBureaucratSignFormSuccess();
void testBureaucratSignFormFail();

int main() {
    testFormCreation();
    std::cout << std::endl;

    testFormGradeTooHigh();
    std::cout << std::endl;

    testFormGradeTooLow();
    std::cout << std::endl;

    testFormBeSignedSuccess();
    std::cout << std::endl;

    testFormBeSignedFail();
    std::cout << std::endl;

    testBureaucratSignFormSuccess();
    std::cout << std::endl;

    testBureaucratSignFormFail();
    std::cout << std::endl;

    return 0;
}

// Test: Form creation with valid parameters
void testFormCreation() {
    std::cout << "========Test: Form Creation========" << std::endl;

    try {
        Form form("Tax Form", 50, 30);
        std::cout << form << std::endl; // Should print the form details
    } catch (std::exception &e) {
        std::cout << "Form creation failed: " << e.what() << std::endl;
    }
}

// Test: Form creation with grade too high
void testFormGradeTooHigh() {
    std::cout << "========Test: Form Grade Too High========" << std::endl;

    try {
        Form form("Top Secret Form", 0, 30); // Grade to sign is too high
    } catch (std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Test: Form creation with grade too low
void testFormGradeTooLow() {
    std::cout << "========Test: Form Grade Too Low========" << std::endl;

    try {
        Form form("Simple Form", 151, 150); // Grade to sign is too low
    } catch (std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Test: Signing a form successfully
void testFormBeSignedSuccess() {
    std::cout << "========Test: Form BeSigned Success========" << std::endl;

    Bureaucrat jeff("Jeff", 20);
    Form form("Important Form", 30, 25);

    try {
        form.beSigned(jeff);
        std::cout << form << std::endl; // Should show that the form is signed
    } catch (std::exception &e) {
        std::cout << "Failed to sign the form: " << e.what() << std::endl;
    }
}

// Test: Failing to sign a form due to low grade
void testFormBeSignedFail() {
    std::cout << "========Test: Form BeSigned Fail========" << std::endl;

    Bureaucrat jeff("Jeff", 50);
    Form form("Restricted Form", 30, 25);

    try {
        form.beSigned(jeff); // Jeff's grade is too low to sign the form
    } catch (std::exception &e) {
        std::cout << "Failed to sign the form: " << e.what() << std::endl;
    }
}

// Test: Bureaucrat successfully signing a form
void testBureaucratSignFormSuccess() {
    std::cout << "========Test: Bureaucrat SignForm Success========" << std::endl;

    Bureaucrat jeff("Jeff", 20);
    Form form("Legal Form", 30, 25);

    jeff.signForm(form); // Should print that Jeff signed the form
    std::cout << form << std::endl; // Should show that the form is signed
}

// Test: Bureaucrat failing to sign a form
void testBureaucratSignFormFail() {
    std::cout << "========Test: Bureaucrat SignForm Fail========" << std::endl;

    Bureaucrat jeff("Jeff", 50);
    Form form("Classified Form", 30, 25);

    jeff.signForm(form); // Should print that Jeff couldn't sign the form
    std::cout << form << std::endl; // Should show that the form is still not signed
}
