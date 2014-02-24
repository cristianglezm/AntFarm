#include <iostream>
#include <Components/ComponentMask.hpp>
#include <Components/Component.hpp>
#include <ComponentTest.hpp>
bool ComponentTest(){
    //declarations
    std::cout << "Component Test: " << std::endl;
    Component c(ComponentsMask::COMPONENT_NONE);
    std::cout << "ID: " << c.getId() << std::endl;
    c.setId(ComponentsMask::COMPONENT_EGGS);
    std::cout << "\nCambiamos ID\nID: " << c.getId() << std::endl;
    return true;
}
