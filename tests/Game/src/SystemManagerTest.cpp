#include <../include/SystemManagerTest.hpp>
#include <iostream>
#include <SystemManager/SystemManager.hpp>
#include <../include/SystemTest.hpp>
#include <Components/ComponentMask.hpp>
bool SystemManagerTest(){
    std::cout << "System Manager Test---------------" << std::endl;
    ant::SystemManager sm;
    sm.addSystem(std::shared_ptr<ant::System>(new testSystem(ComponentsMask::COMPONENT_MOVEMENT)));
}
