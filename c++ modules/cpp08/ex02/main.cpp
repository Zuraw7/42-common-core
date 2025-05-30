#include <iostream>
#include <list>
#include "MutantStack.hpp"

void test_basic_operations();
void test_reverse_iteration();
void test_custom_data();
void test_compare_with_list();

int main() {

    test_basic_operations();
	std::cout << std::endl;

    test_reverse_iteration();
	std::cout << std::endl;

    test_custom_data();
	std::cout << std::endl;

    test_compare_with_list();
	std::cout << std::endl;

    return 0;
}

void test_basic_operations() {
    std::cout << "Running test_basic_operations...\n";
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "Top element: " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack);
}

void test_reverse_iteration() {
    std::cout << "Running test_reverse_iteration...\n";
    MutantStack<int> mstack;
    for (int i = 1; i <= 5; ++i) {
        mstack.push(i * 10);
    }

    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();
    while (rit != rite) {
        std::cout << *rit << " ";
        ++rit;
    }
    std::cout << std::endl;
}

class CustomData {
private:
    int _id;
    std::string _name;

public:
    CustomData(int id, const std::string& name) : _id(id), _name(name) {}

    void print() const {
        std::cout << "ID: " << _id << ", Name: " << _name;
    }
};

void test_custom_data() {
    std::cout << "Running test_custom_data...\n";
    MutantStack<CustomData> mstack;
    mstack.push(CustomData(1, "Alice"));
    mstack.push(CustomData(2, "Bob"));
    mstack.push(CustomData(3, "Charlie"));

    for (MutantStack<CustomData>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        it->print();
        std::cout << std::endl;
    }
}

void test_compare_with_list() {
    std::cout << "Running test_compare_with_list...\n";
    MutantStack<int> mstack;
    std::list<int> lst;

    for (int i = 10; i <= 50; i += 10) {
        mstack.push(i);
        lst.push_back(i);
    }

    std::cout << "MutantStack output: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "std::list output: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
