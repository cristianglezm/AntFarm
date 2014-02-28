#include <EntityTest.hpp>
#include <Components/ComponentMask.hpp>
bool EntityTest(){
    std::cout << "Entity Test:-------------------------------- " << std::endl;
    ant::Entity e("Test",std::map<long,ant::Component>());
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    std::cout << "Entity name: " << e.getName() << std::endl;
    std::cout << "Adding Movement,Transform Components..." << std::endl;
    e.addComponent(ant::Component(ComponentsMask::COMPONENT_MOVEMENT));
    e.addComponent(ant::Component(ComponentsMask::COMPONENT_TRANSFORM));
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    std::cout << "Getting Component Movement mask: " << e.getComponent(ComponentsMask::COMPONENT_MOVEMENT).getId() << std::endl;
    std::cout << "Removing Component Movement..." << std::endl;
    e.removeComponent(ComponentsMask::COMPONENT_MOVEMENT);
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    return true;
}
