#include <iostream>

int main()
{
    std::cout << "Masking Test" << std::endl;
    const unsigned long COMPONENT_NONE = 0;
    const unsigned long COMPONENT_MOVEMENT = 1 << 0;
    const unsigned long COMPONENT_ATTACK = 1 << 1;
    const unsigned long COMPONENT_DEFENSE = 1 << 2;
    const unsigned long REQ = COMPONENT_ATTACK | COMPONENT_MOVEMENT;
    const unsigned long REQ2 = COMPONENT_NONE | COMPONENT_ATTACK | COMPONENT_DEFENSE;
    std::cout << "COMPONENT NONE MASK: " << COMPONENT_NONE<< std::endl;
    std::cout << "COMPONENT MOVEMENT MASK: " << COMPONENT_MOVEMENT << std::endl;
    std::cout << "COMPONENT ATTACK MASK: " << COMPONENT_ATTACK<< std::endl;
    std::cout << "REQUIRED MASK: " << REQ << std::endl;
    std::cout << "REQUIRED 2 MASK: " << REQ2 << std::endl;
    std::cout << "REQUIRED MASK TEST CONDITION: " << ((REQ & REQ2) == COMPONENT_ATTACK ? "TRUE":"FALSE") << std::endl;

    return 0;
}

