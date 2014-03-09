#include <EntityTest.hpp>
#include <Components/ComponentMask.hpp>
#include <cassert>
bool EntityTest(){
    std::cout << "Entity Test:-------------------------------- " << std::endl;
    ant::Entity e("Test");
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    assert(e.getMask()==0);
    std::cout << "Entity name: " << e.getName() << std::endl;
    assert(e.getName()=="Test");
    std::cout << "Adding Movement,Transform Components..." << std::endl;
    std::unique_ptr<ant::Component> c1(new ant::Component(ComponentsMask::COMPONENT_MOVEMENT));
    e.addComponent(std::move(c1));
    std::unique_ptr<ant::Component> c2(new ant::Component(ComponentsMask::COMPONENT_TRANSFORM));
    e.addComponent(std::move(c2));
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    assert(e.getMask()==(ComponentsMask::COMPONENT_MOVEMENT | ComponentsMask::COMPONENT_TRANSFORM));
    std::cout << "Getting Component Movement mask: " << e.getComponent(ComponentsMask::COMPONENT_MOVEMENT)->getId() << std::endl;
    assert(e.getComponent(ComponentsMask::COMPONENT_MOVEMENT)->getId()==ComponentsMask::COMPONENT_MOVEMENT);
    std::cout << "Removing Component Movement..." << std::endl;
    e.removeComponent(ComponentsMask::COMPONENT_MOVEMENT);
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    assert(e.getMask()==(e.getMask() & ~ComponentsMask::COMPONENT_MOVEMENT));
    return true;
}
