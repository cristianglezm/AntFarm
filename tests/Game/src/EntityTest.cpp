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
    std::unique_ptr<ant::baseComponent> c1(new ant::Component<int>(ComponentsMask::COMPONENT_VELOCITY,2));
    e.addComponent(std::move(c1));
    std::unique_ptr<ant::baseComponent> c2(new ant::Component<int>(ComponentsMask::COMPONENT_TRANSFORM,2));
    e.addComponent(std::move(c2));
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    assert(e.getMask()==(ComponentsMask::COMPONENT_VELOCITY | ComponentsMask::COMPONENT_TRANSFORM));
    std::cout << "Getting Component Movement mask: " << e.getComponent(ComponentsMask::COMPONENT_VELOCITY)->getId() << std::endl;
    assert(e.getComponent(ComponentsMask::COMPONENT_VELOCITY)->getId()==ComponentsMask::COMPONENT_VELOCITY);
    std::cout << "Removing Component Movement..." << std::endl;
    e.removeComponent(ComponentsMask::COMPONENT_VELOCITY);
    std::cout << "Entity mask: " << e.getMask() << std::endl;
    assert(e.getMask()==(e.getMask() & ~ComponentsMask::COMPONENT_VELOCITY));
    return true;
}
