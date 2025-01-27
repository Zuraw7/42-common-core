#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    // Test 1: Konstrukcja i destrukcja ClapTrap
    {
        std::cout << "\n=== TEST 1: Konstrukcja i destrukcja ClapTrap ===" << std::endl;
        ClapTrap clap("Clappy");
    }

    // Test 2: Konstrukcja i destrukcja ScavTrap
    {
        std::cout << "\n=== TEST 2: Konstrukcja i destrukcja ScavTrap ===" << std::endl;
        ScavTrap scav("Scavy");
    }

    // Test 3: Atakowanie ClapTrap
    {
        std::cout << "\n=== TEST 3: Atakowanie ClapTrap ===" << std::endl;
        ClapTrap clap("Clappy");
        clap.attack("Enemy");
    }

    // Test 4: Atakowanie ScavTrap
    {
        std::cout << "\n=== TEST 4: Atakowanie ScavTrap ===" << std::endl;
        ScavTrap scav("Scavy");
        scav.attack("Enemy");
    }

    // Test 5: Przyjmowanie obrażeń i leczenie ClapTrap
    {
        std::cout << "\n=== TEST 5: Przyjmowanie obrażeń i leczenie ClapTrap ===" << std::endl;
        ClapTrap clap("Clappy");
        clap.takeDamage(5);
        clap.beRepaired(3);
        clap.takeDamage(10);  // ClapTrap powinien umrzeć
        clap.beRepaired(5);   // Próba leczenia martwego ClapTrap
    }

    // Test 6: Przyjmowanie obrażeń i leczenie ScavTrap
    {
        std::cout << "\n=== TEST 6: Przyjmowanie obrażeń i leczenie ScavTrap ===" << std::endl;
        ScavTrap scav("Scavy");
        scav.takeDamage(20);
        scav.beRepaired(10);
        scav.takeDamage(100); // ScavTrap powinien umrzeć
        scav.beRepaired(10);  // Próba leczenia martwego ScavTrap
    }

    // Test 7: Zużycie energii przez ScavTrap
    {
        std::cout << "\n=== TEST 7: Zużycie energii przez ScavTrap ===" << std::endl;
        ScavTrap scav("EnergyDrainer");
        for (int i = 0; i < 55; ++i) {
            scav.attack("Enemy");
        }
    }

    // Test 8: Tryb strażnika (guardGate)
    {
        std::cout << "\n=== TEST 8: Tryb strażnika (guardGate) ===" << std::endl;
        ScavTrap scav("Guardian");
        scav.guardGate(); // Włączenie trybu strażnika
        scav.guardGate(); // Wyłączenie trybu strażnika
    }

    // Test 9: Kopiowanie ScavTrap
    {
        std::cout << "\n=== TEST 9: Kopiowanie ScavTrap ===" << std::endl;
        ScavTrap original("Original");
        ScavTrap copy = original; // Wywołanie konstruktora kopiującego
        copy.guardGate();
    }

    // Test 10: Operator przypisania ScavTrap
    {
        std::cout << "\n=== TEST 10: Operator przypisania ScavTrap ===" << std::endl;
        ScavTrap scav1("First");
        ScavTrap scav2("Second");
        scav2 = scav1; // Wywołanie operatora przypisania
        scav2.guardGate();
    }

    return 0;
}
