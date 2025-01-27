#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    // Test 1: Konstrukcja i destrukcja ClapTrap
    {
        std::cout << "\n=== TEST 1: Konstrukcja i destrukcja ClapTrap ===" << std::endl;
        ClapTrap clap("Clappy");
    }

    // Test 2: Konstrukcja i destrukcja FragTrap
    {
        std::cout << "\n=== TEST 2: Konstrukcja i destrukcja FragTrap ===" << std::endl;
        FragTrap frag("Fraggy");
    }

    // Test 3: Atakowanie FragTrap
    {
        std::cout << "\n=== TEST 3: Atakowanie FragTrap ===" << std::endl;
        FragTrap frag("Fraggy");
        frag.attack("Enemy");
    }

    // Test 4: otrzymywanie obrażeń i leczenie FragTrap
    {
        std::cout << "\n=== TEST 4: otrzymywanie obrażeń i leczenie FragTrap ===" << std::endl;
        FragTrap frag("Fraggy");
        frag.takeDamage(50);
        frag.beRepaired(30);
        frag.takeDamage(100);  // FragTrap powinien umrzeć
        frag.beRepaired(20);   // Próba leczenia martwego FragTrap
    }

    // Test 5: Zużycie energii przez FragTrap
    {
        std::cout << "\n=== TEST 5: Zużycie energii przez FragTrap ===" << std::endl;
        FragTrap frag("EnergyDrainer");
        for (int i = 0; i < 101; ++i) {
            frag.attack("Enemy");
        }
    }

    // Test 6: Funkcja highFivesGuys
    {
        std::cout << "\n=== TEST 6: Funkcja highFivesGuys ===" << std::endl;
        FragTrap frag("Friendly");
        frag.highFivesGuys();
    }

    // Test 7: Kopiowanie FragTrap
    {
        std::cout << "\n=== TEST 7: Kopiowanie FragTrap ===" << std::endl;
        FragTrap original("Original");
        FragTrap copy(original); // Wywołanie konstruktora kopiującego
        copy.highFivesGuys();
    }

    // Test 8: Operator przypisania FragTrap
    {
        std::cout << "\n=== TEST 8: Operator przypisania FragTrap ===" << std::endl;
        FragTrap frag1("First");
        FragTrap frag2("Second");
        frag2 = frag1; // Wywołanie operatora przypisania
        frag2.highFivesGuys();
    }

    return 0;
}
