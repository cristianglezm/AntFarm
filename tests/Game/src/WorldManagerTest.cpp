#include <../include/WorldManagerTest.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <random>
#include <functional>
#include <WorldManager/WorldManager.hpp>
#include <Utils/String.hpp>
#include <../include/SystemTest.hpp>
#include <Components/ComponentMask.hpp>

bool WorldManagerTest(){
    std::cout << "WorldManager Test -----------" << std::endl;
    std::shared_ptr<ant::EntityManager> em(new ant::EntityManager());
    std::shared_ptr<ant::EventQueue> eq(new ant::EventQueue());
    ant::WorldManager wm;
    for(int i=0;i<5;++i){
        std::unique_ptr<ant::SystemManager> sm(new ant::SystemManager());
        for(int j=0;j<10;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("Test-" + ant::Utils::toString(i)));
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(j,6);
            auto dice = std::bind(distribution, generator);
            switch(dice()){
                case 1:{
                    std::unique_ptr<ant::baseComponent> c1( new ant::Component<int>(ComponentsMask::COMPONENT_ANIMATION,2));
                    e->addComponent(std::move(c1));
                    }
                    break;
                case 2:{
                    std::unique_ptr<ant::baseComponent> c2( new ant::Component<int>(ComponentsMask::COMPONENT_PASSAGE,2));
                    e->addComponent(std::move(c2));
                    }
                    break;
                case 3:{
                    std::unique_ptr<ant::baseComponent> c3( new ant::Component<int>(ComponentsMask::COMPONENT_DESTRUCTABLE,2));
                    e->addComponent(std::move(c3));
                    }
                    break;
                case 4:{
                    std::unique_ptr<ant::baseComponent> c4( new ant::Component<int>(ComponentsMask::COMPONENT_VELOCITY,2));
                    e->addComponent(std::move(c4));
                    }
                    break;
                case 5:{
                    std::unique_ptr<ant::baseComponent> c5( new ant::Component<int>(ComponentsMask::COMPONENT_SPRITE,2));
                    e->addComponent(std::move(c5));
                    }
                    break;
                case 6:{
                    std::unique_ptr<ant::baseComponent> c6( new ant::Component<int>(ComponentsMask::COMPONENT_TRANSFORM,2));
                    e->addComponent(std::move(c6));
                    }
                    break;
            }
        em->addEntity(std::move(e));
        }
        auto masks = ComponentsMask::COMPONENT_ANIMATION | ComponentsMask::COMPONENT_VELOCITY;
        for(int k=0;k<1;++k){
            std::shared_ptr<testSystem> ts(new testSystem(masks));
            ts->setName("test-" + ant::Utils::toString(k));
            ts->setEntityManager(em);
            ts->setEventQueue(eq);
            sm->addSystem(ts);
        }
        std::unique_ptr<ant::World> w1(new ant::World(i,em,std::move(sm),eq));
        wm.addWorld(std::move(w1));
    }
    wm.update(-1,sf::Time());
    std::cout << "Obtenemos mundo especifico para actualizarlo"<< std::endl;
    auto tmpWorld = wm.getWorld(1);
    assert(tmpWorld->getId()==1);
    tmpWorld->update(sf::Time());
    return true;
}
