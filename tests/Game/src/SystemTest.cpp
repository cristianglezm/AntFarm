#include <../include/SystemTest.hpp>
#include <Components/ComponentMask.hpp>
#include <iostream>
    testSystem::testSystem(long int req):ant::System(req){
        name = "testSystem";
        RequiredComponents = (ComponentsMask::COMPONENT_HORNS | ComponentsMask::COMPONENT_MOVEMENT);
    }
    void testSystem::update(sf::Time dt){
        std::cout << "Update" << std::endl;
        for(auto& entity : em->getEntities()){
            if((entity->getMask() & RequiredComponents) == RequiredComponents){
                std::cout << "Entity has the requeriments." << std::endl;
                eventQueue.push(std::shared_ptr<ant::Event>(new ant::Event(4)));
            }else{
                std::cout << "Entity hasnt the requeriments." << std::endl;
            }
        }
    }
    void testSystem::render(){
        std::cout << "render" << std::endl;
    }
bool SystemTest(){
    std::cout << "System Test"<< std::endl;
    testSystem s(ComponentsMask::COMPONENT_HORNS | ComponentsMask::COMPONENT_MOVEMENT);
    std::cout << "Required Components: " << s.getRequiredComponts() << std::endl;
    std::shared_ptr<ant::EntityManager> em1(new ant::EntityManager());
    s.setEntityManager(em1);
    for(int i=0;i<10;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity());
        std::unique_ptr<ant::Component> c1(new ant::Component(ComponentsMask::COMPONENT_MOVEMENT));
        std::unique_ptr<ant::Component> c2(new ant::Component(ComponentsMask::COMPONENT_HORNS));
        e1->addComponent(std::move(c1));
        e1->addComponent(std::move(c2));
        s.getEntityManager()->addEntity(std::move(e1));
    }
    std::unique_ptr<ant::Entity> e1(new ant::Entity());
    s.getEntityManager()->addEntity(std::move(e1));
    s.update(sf::Time());
    s.render();
    std::cout << "Event Process " << std::endl;
    while(!s.getEventQueue().isEmpty()){
     std::cout << "Type event: " << s.getEventQueue().pop()->getType() << std::endl;
    }
    return true;
}
