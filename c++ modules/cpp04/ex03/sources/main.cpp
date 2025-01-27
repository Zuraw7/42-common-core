#include <iostream>
#include "../includes/AMateria.hpp"
#include "../includes/Character.hpp"
#include "../includes/MateriaSource.hpp"

void testMemoryLeaksBasic();
void testMemoryLeaksOverflowInventory();
void testMemoryLeaksMateriaSource();
void testMemoryLeaksCopy();
void testMemoryLeaksUnequip();
void testMemoryLeaksEquipUnequip();

int main() {
	{
    	std::cout << "=== Test: Main given by subject ===" << std::endl;
		IMateriaSource* src = new MateriaSource();

		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter* me = new Character("me");
		AMateria* tmp;

		tmp = src->createMateria("ice");
		me->equip(tmp);

		tmp = src->createMateria("cure");
		me->equip(tmp);

		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);

		delete bob;
		delete me;
		delete src;
	}

    std::cout << std::endl;
	testMemoryLeaksBasic();
    std::cout << std::endl;
	testMemoryLeaksOverflowInventory();
    std::cout << std::endl;
	testMemoryLeaksMateriaSource();
    std::cout << std::endl;
	testMemoryLeaksCopy();
    std::cout << std::endl;
	testMemoryLeaksUnequip();
    std::cout << std::endl;
    testMemoryLeaksEquipUnequip();
    std::cout << std::endl;
	return 0;
}

void testMemoryLeaksBasic() {
    std::cout << "=== Test: Basic Memory Management ===" << std::endl;
    IMateriaSource* src = new MateriaSource();

    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");
    AMateria* tmp;

    tmp = src->createMateria("ice");
    me->equip(tmp);

    tmp = src->createMateria("cure");
    me->equip(tmp);

    delete me;
    delete src;

    std::cout << "=== Test: Finished ===" << std::endl;
}

void testMemoryLeaksOverflowInventory() {
    std::cout << "=== Test: Inventory Overflow ===" << std::endl;
    ICharacter* me = new Character("me");

    AMateria* m1 = new Ice();
    AMateria* m2 = new Cure();
    AMateria* m3 = new Ice();
    AMateria* m4 = new Cure();
    AMateria* m5 = new Ice();

    me->equip(m1);
    me->equip(m2);
    me->equip(m3);
    me->equip(m4);

    // Przekroczenie limitu ekwipunku
    me->equip(m5);

    // Unequip i upewnienie się, że pamięć jest zarządzana
    me->unequip(0);
    me->unequip(1);

    delete me;

    // m5 jest nadmiarowy i należy go usunąć ręcznie
    delete m5;

    std::cout << "=== Test: Finished ===" << std::endl;
}

void testMemoryLeaksMateriaSource() {
    std::cout << "=== Test: MateriaSource Management ===" << std::endl;
    IMateriaSource* src = new MateriaSource();

    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    src->learnMateria(new Ice()); // Overflow

    delete src;

    std::cout << "=== Test: Finished ===" << std::endl;
}

void testMemoryLeaksCopy() {
    std::cout << "=== Test: Copy Constructor and Assignment ===" << std::endl;

    Character* original = new Character("original");
    original->equip(new Ice());
    original->equip(new Cure());

    Character* copy = new Character(*original); // Konstruktor kopiujący
    Character* assigned = new Character("assigned");
    *assigned = *original; // Operator przypisania

    copy->use(0, *copy);
    assigned->use(1, *assigned);

    delete original;
    delete copy;
    delete assigned;

    std::cout << "=== Test: Finished ===" << std::endl;
}

void testMemoryLeaksUnequip() {
    std::cout << "=== Test: Unequip Memory Management ===" << std::endl;

    ICharacter* me = new Character("me");

    AMateria* m1 = new Ice();
    AMateria* m2 = new Cure();

	std::cout << std::endl;
    me->equip(m1);
    me->equip(m2);

	std::cout << std::endl;

    me->unequip(0);
    me->unequip(1);
    me->unequip(1);
	std::cout << std::endl;

    delete me;

    std::cout << "=== Test: Finished ===" << std::endl;
}

void testMemoryLeaksEquipUnequip() {
    std::cout << "=== Test: Equip and Unequip ===" << std::endl;
    ICharacter* me = new Character("me");

    AMateria* m1 = new Ice();
    AMateria* m2 = new Cure();
    AMateria* m3 = new Ice();
    AMateria* m4 = new Cure();
    AMateria* m5 = new Ice();

    std::cout << std::endl;
    me->equip(m1);
    me->equip(m2);
    me->equip(m3);
    me->unequip(1);
    me->equip(m4);

    me->equip(m5);
    // me->unequip(0);
    std::cout << std::endl;

    delete me;
    std::cout << "=== Test: Finished ===" << std::endl;
}
