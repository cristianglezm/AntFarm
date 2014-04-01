#include <iostream>
#include <cstdlib>
int main()
{
    std::cout << "Masking Test" << std::endl;
    const unsigned long COMPONENT_NONE = 0;
    const unsigned long COMPONENT_MOVEMENT = 1 << 1;
    const unsigned long COMPONENT_ATTACK = 1 << 2;
    const unsigned long COMPONENT_DEFENSE = 1 << 3;
    unsigned long EntityMask = COMPONENT_ATTACK | COMPONENT_MOVEMENT | COMPONENT_DEFENSE;
    unsigned long ReqSystem = COMPONENT_MOVEMENT | COMPONENT_ATTACK | COMPONENT_DEFENSE;
    std::cout << "COMPONENT NONE MASK: " << COMPONENT_NONE<< std::endl;
    std::cout << "COMPONENT MOVEMENT MASK: " << COMPONENT_MOVEMENT << std::endl;
    std::cout << "COMPONENT ATTACK MASK: " << COMPONENT_ATTACK<< std::endl;
    std::cout << "REQUIRED MASK: " << EntityMask << std::endl;
    std::cout << "REQUIRED 2 MASK: " << ReqSystem << std::endl;
    std::cout << "REQUIRED MASK TEST CONDITION: " << ((EntityMask & ReqSystem) == ReqSystem ? "TRUE":"FALSE") << std::endl;
    std::cout << "Removing Movement Component.." << std::endl;
    EntityMask &= ~COMPONENT_MOVEMENT;
    std::cout << "REQUIRED MASK: " << EntityMask << std::endl;
    std::cout << "REQUIRED 2 MASK: " << ReqSystem << std::endl;
    std::cout << "REQUIRED MASK TEST CONDITION: " << ((EntityMask & ReqSystem) == ReqSystem ? "TRUE":"FALSE") << std::endl;
    std::cout << "Adding movement Component " << std::endl;
    EntityMask |= COMPONENT_MOVEMENT;
    std::cout << "REQUIRED MASK: " << EntityMask << std::endl;
    std::cout << "REQUIRED 2 MASK: " << ReqSystem << std::endl;
    std::cout << "REQUIRED MASK TEST CONDITION: " << ((EntityMask & ReqSystem) == ReqSystem ? "TRUE":"FALSE") << std::endl;
    system("PAUSE");
    return 0;
}

