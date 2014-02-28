#include <../include/EntityManagerTest.hpp>
#include <EntityManager/EntityManager.hpp>
#include <Utils/Utils.hpp>
#include <Components/ComponentMask.hpp>
#include <iostream>
bool EntityManagerTest(){
    std::cout << "Entity Manager Test:-------------------------------- "  << std::endl;
    ant::EntityManager em;
    ant::Entity e0("Test0",std::map<long,ant::Component>());
    ant::Entity e1("Test1",std::map<long,ant::Component>());
    em.addEntity(e0);
    em.addEntity(e1);
    std::cout << "Added Succesfully.." << std::endl;
    em.removeEntity(e0);
    ant::Entity tmp = em.getEntity("Test0");
    if(tmp.getName()!=""){
        std::cout << tmp.getName() << std::endl;
    }else{
        std::cout << "Item Not Found " << std::endl;
        std::cout << "Removed Succesfully.." << std::endl;
    }
    std::cout << "Testing Modifiying Entity.." << std::endl;
    ant::Entity t1 = em.getEntity("Test1");
    if(t1.getName()!=""){
        std::cout << "Found t1 " << t1.getName() << " Mask = " << t1.getMask() << std::endl;
        t1.addComponent(ant::Component(ComponentsMask::COMPONENT_DESTRUCTABLE));
        std::cout << "Found t1 " << t1.getName() << " Mask = " << t1.getMask() << std::endl;
    }
    ant::Entity t2 = em.getEntity("Test1");
    if(t2.getName()!=""){
        std::cout << "Found t2 " << t1.getName() << " Mask = " << t1.getMask() << std::endl;
        t2.addComponent(ant::Component(ComponentsMask::COMPONENT_EGGS));
        std::cout << "Found t2 " << t1.getName() << " Mask = " << t1.getMask() << std::endl;
    }
    for(int i=0;i<10;++i){
        ant::Entity e = ant::Entity("Test-" + ant::Utils::toString(i),std::map<long,ant::Component>());
        switch(rand()%1+i){
            case 1:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_EGGS));
                break;
            case 2:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_HORNS));
                break;
            case 3:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_DESTRUCTABLE));
                break;
            case 4:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_MOVEMENT));
                break;
            case 5:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_SPRITE));
                break;
            case 6:
                e.addComponent(ant::Component(ComponentsMask::COMPONENT_TRANSFORM));
                break;
        }
        em.addEntity(e);
    }
    for(auto& entity: em.getEntities()){
        std::cout << "\tEntity: \n\t\tMask: " << entity.getMask() << "\n\t\tName: " << entity.getName() << std::endl;
    }
}
