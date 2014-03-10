#include <../include/EntityManagerTest.hpp>
#include <EntityManager/EntityManager.hpp>
#include <Utils/Utils.hpp>
#include <Components/ComponentMask.hpp>
#include <iostream>
#include <cassert>
#include <random>
bool EntityManagerTest(){
    std::cout << "Entity Manager Test:-------------------------------- "  << std::endl;
    ant::EntityManager em;
    std::unique_ptr<ant::Entity> e0(new ant::Entity("Test0"));
    std::unique_ptr<ant::Entity> e1(new ant::Entity("Test1"));
    em.addEntity(std::move(e0));
    em.addEntity(std::move(e1));
    std::cout << "Added Succesfully.." << std::endl;
    em.removeEntity("Test0");
    auto tmp = em.getEntity("Test0");
    if(tmp!=nullptr){
        std::cout << tmp->getName() << std::endl;
    }else{
        std::cout << "Item Not Found " << std::endl;
        std::cout << "Removed Succesfully.." << std::endl;
    }
    std::cout << "Testing Modifiying Entity.." << std::endl;
    auto t1 = em.getEntity("Test1");
    if(t1->getName()=="Test1"){
        std::cout << "Found t1 " << t1->getName() << " Mask = " << t1->getMask() << std::endl;
        std::unique_ptr<ant::Component> c1( new ant::Component(ComponentsMask::COMPONENT_DESTRUCTABLE));
        std::cout << "Adding Component..." << std::endl;
        t1->addComponent(std::move(c1));
        std::cout << "Found t1 " << t1->getName() << " Mask = " << t1->getMask() << std::endl;
    }
    auto t2 = em.getEntity("Test1");
    if(t2->getName()!=""){
        std::cout << "Found t2 " << t2->getName() << " Mask = " << t2->getMask() << std::endl;
        std::cout << "Removing Component..." << std::endl;
        t2->removeComponent(ComponentsMask::COMPONENT_DESTRUCTABLE);
        std::cout << "Found t2 " << t2->getName() << " Mask = " << t2->getMask() << std::endl;
        std::unique_ptr<ant::Component> c2( new ant::Component(ComponentsMask::COMPONENT_EGGS));
        std::cout << "Adding Component..." << std::endl;
        t2->addComponent(std::move(c2));
        std::cout << "Found t2 " << t2->getName() << " Mask = " << t2->getMask() << std::endl;
        std::cout << "Getting Component EGGS" << std::endl;
        std::cout << "EGGS ID = " << t2->getComponent(ComponentsMask::COMPONENT_EGGS)->getId() << std::endl;
    }
    for(int i=0;i<10;++i){
        std::unique_ptr<ant::Entity> e(new ant::Entity("Test-" + ant::Utils::toString(i)));
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(i,6);
        //std::poisson_distribution<int> distribution(i);
        auto dice = std::bind(distribution, generator);
        switch(dice()){
            case 1:{
                std::unique_ptr<ant::Component> c1( new ant::Component(ComponentsMask::COMPONENT_EGGS));
                e->addComponent(std::move(c1));
                }
                break;
            case 2:{
                std::unique_ptr<ant::Component> c2( new ant::Component(ComponentsMask::COMPONENT_HORNS));
                e->addComponent(std::move(c2));
                }
                break;
            case 3:{
                std::unique_ptr<ant::Component> c3( new ant::Component(ComponentsMask::COMPONENT_DESTRUCTABLE));
                e->addComponent(std::move(c3));
                }
                break;
            case 4:{
                std::unique_ptr<ant::Component> c4( new ant::Component(ComponentsMask::COMPONENT_MOVEMENT));
                e->addComponent(std::move(c4));
                }
                break;
            case 5:{
                std::unique_ptr<ant::Component> c5( new ant::Component(ComponentsMask::COMPONENT_SPRITE));
                e->addComponent(std::move(c5));
                }
                break;
            case 6:{
                std::unique_ptr<ant::Component> c6( new ant::Component(ComponentsMask::COMPONENT_TRANSFORM));
                e->addComponent(std::move(c6));
                }
                break;
        }
        em.addEntity(std::move(e));
    }
    for(auto& entity: em.getEntities()){
        std::cout << "\tEntity: \n\t\tMask: " << entity->getMask() << "\n\t\tName: " << entity->getName() << std::endl;
    }
    std::cout << "Testing Tranfer" << std::endl;
    auto newOwner = em.Transfer("Test0");
    auto newOwner2 = em.Transfer("Test1");
    auto t3 = em.getEntity("Test0");
    if(newOwner){
        std::cout << "NewOwner: " << newOwner->getName() << " Points: " << newOwner.get() << std::endl;
        std::cout << "Entity " << newOwner->getName() << " has been Transfered..." << std::endl;
    }else{
        std::cout << "Transfer failed" << std::endl;
    }
    if(newOwner2){
        std::cout << "NewOwner: " << newOwner2->getName() << " Points: " << newOwner2.get() << std::endl;
        std::cout << "Entity " << newOwner2->getName() << " has been Transfered..." << std::endl;
    }else{
        std::cout << "Transfer failed" << std::endl;
    }
    if(t3){
        std::cout << "t3 found: " << t3->getName() << std::endl;
    }else{
        std::cout << "t3 not found" << std::endl;
    }
    return true;
}
