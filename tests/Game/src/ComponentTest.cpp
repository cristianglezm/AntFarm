#include <iostream>
#include <Components/ComponentMask.hpp>
#include <Components/Component.hpp>
#include <ComponentTest.hpp>
bool ComponentTest(){
    //declarations
    std::cout << "Component Test:-------------------------------- " << std::endl;
    ant::Component c(ComponentsMask::COMPONENT_NONE);
    std::cout << "ID: " << c.getId() << std::endl;
    c.setId(ComponentsMask::COMPONENT_EGGS);
    std::cout << "Cambiamos ID\nID: " << c.getId() << std::endl;
    return true;
}
