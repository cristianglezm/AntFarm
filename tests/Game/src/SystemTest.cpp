#include <../include/SystemTest.hpp>
#include <Components/ComponentMask.hpp>
#include <iostream>
#include <utility>
#include <Utils/Utility.hpp>
    testSystem::testSystem(ComponentsMask::Mask& req):ant::System(req){
        name = "testSystem";
    }
    void testSystem::update(const sf::Time& dt){
        std::cout << "Update" << std::endl;
        for(auto& entity : em->getEntities()){
            if((entity->getMask() & RequiredComponents) == RequiredComponents){
                std::cout << "Entity has the requirements." << std::endl;
                eventQueue->push(std::make_shared<ant::Event<int,std::string>>(3,3,"Test de evento con templates"));
            }else{
                std::cout << "Entity hasn't the requirements." << std::endl;
            }
        }
    }
    void testSystem::render(sf::RenderWindow& win){
        std::cout << "render" << std::endl;
    }
bool SystemTest(){
    std::shared_ptr<ant::EventQueue> eq(new ant::EventQueue());
    std::cout << "System Test------------------------"<< std::endl;
    auto masks = ComponentsMask::COMPONENT_ANIMATION | ComponentsMask::COMPONENT_VELOCITY;
    testSystem s(masks);
    s.setEventQueue(eq);
    std::cout << "Required Components: " << s.getRequiredComponts() << std::endl;
    std::cout << "Creamos entityManager y agregamos al sistema. " << std::endl;
    std::shared_ptr<ant::EntityManager> em1(new ant::EntityManager());
    s.setEntityManager(em1);
    std::cout << "Creamos y agregamos entidades: " << std::endl;
    for(int i=0;i<3;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity());
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<int>(ComponentsMask::COMPONENT_VELOCITY,2));
        std::unique_ptr<ant::baseComponent> c2(new ant::Component<int>(ComponentsMask::COMPONENT_ANIMATION,2));
        e1->addComponent(std::move(c1));
        e1->addComponent(std::move(c2));
        s.getEntityManager()->addEntity(std::move(e1));
    }
    std::cout << "Creamos y agregamos una entidad sin los requisitos: " << std::endl;
    std::unique_ptr<ant::Entity> e1(new ant::Entity());
    s.getEntityManager()->addEntity(std::move(e1));
    std::cout << "S Update: " << std::endl;
    s.update(sf::Time());
    std::cout << "Creamos otro sistema, agregamos el em y eventqueue" << std::endl;
    auto n=ComponentsMask::COMPONENT_NONE;
    testSystem s1(n);
    for(int i=0;i<2;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity());
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<int>(ComponentsMask::COMPONENT_PASSAGE,3));
        std::unique_ptr<ant::baseComponent> c2(new ant::Component<int>(ComponentsMask::COMPONENT_NONE,2));
        e1->addComponent(std::move(c1));
        e1->addComponent(std::move(c2));
        s1.getEntityManager()->addEntity(std::move(e1));
    }
    s1.setEventQueue(eq);
    s1.setEntityManager(em1);
    s1.update(sf::Time());
    std::cout << "Processing Event Queue " << std::endl;
    while(!s1.getEventQueue()->isEmpty()){
        std::cout << "Type event: " << eq->pop()->getType() << std::endl;
    }
    return true;
}
