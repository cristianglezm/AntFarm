#include <../include/SystemManagerTest.hpp>
#include <iostream>
#include <SystemManager/SystemManager.hpp>
#include <../include/SystemTest.hpp>
#include <Components/ComponentMask.hpp>
bool SystemManagerTest(){
    std::cout << "System Manager Test---------------" << std::endl;
    ant::SystemManager sm;
    std::shared_ptr<ant::System> s(new testSystem(ComponentsMask::COMPONENT_MOVEMENT));
    s->setName("testSystem");
    for(int i=0;i<3;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity());
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<int>(ComponentsMask::COMPONENT_MOVEMENT,2));
        std::unique_ptr<ant::baseComponent> c2(new ant::Component<int>(ComponentsMask::COMPONENT_HORNS,2));
        e1->addComponent(std::move(c1));
        e1->addComponent(std::move(c2));
        s->getEntityManager()->addEntity(std::move(e1));
    }
    sm.addSystem(s);
    auto tmp = sm.getSystem("testSystem");
    std::cout << "System Name: " << tmp->getName() << std::endl;
    tmp->update(sf::Time());
    return true;
}
