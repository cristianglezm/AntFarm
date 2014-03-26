#include <../include/renderSystemTest.hpp>
#include <Systems/renderSystem/renderSystem.hpp>
#include <Entity/Entity.hpp>
#include <memory>
#include <ComponentFactory/ComponentFactory.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <WorldManager/WorldManager.hpp>
#include <Utils/String.hpp>
#include <Components/ComponentMask.hpp>
bool renderSystemTest(){
std::cout << "WorldManager Test -----------" << std::endl;
    std::shared_ptr<ant::EntityManager> em(new ant::EntityManager());
    std::shared_ptr<ant::EventQueue> eq(new ant::EventQueue());
    std::shared_ptr<ant::AssetManager> assets(new ant::AssetManager());
    assets->addTexture("Ant","datatest/image.png");
    ant::ComponentFactory cf(assets);
    sf::RenderWindow win(sf::VideoMode(800,600),"TEST RenderSystem");
    ant::WorldManager wm;
    for(int i=0;i<5;++i){
        std::unique_ptr<ant::SystemManager> sm(new ant::SystemManager());
        for(int j=0;j<10;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("Test-" + ant::Utils::toString(i)));
            e->addComponent(cf.createSprite("Ant"));
            e->addComponent(cf.createTransform(sf::Vector2f(j+i,i+j),sf::Vector2f(1,6),0));
            em->addEntity(std::move(e));
        }
        for(int k=0;k<1;++k){
            std::shared_ptr<ant::renderSystem> ts(new ant::renderSystem(ComponentsMask::COMPONENT_SPRITE | ComponentsMask::COMPONENT_TRANSFORM));
            ts->setName("test-" + ant::Utils::toString(k));
            ts->setEntityManager(em);
            ts->setEventQueue(eq);
            sm->addSystem(ts);
        }
        std::unique_ptr<ant::World> w1(new ant::World(i,em,std::move(sm),eq));
        wm.addWorld(std::move(w1));
    }
    bool running=true;
    while(running){
        sf::Event event;
        while(win.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    running = false;
                    break;
            }
        }
        wm.update(-1,sf::Time());
        win.clear();
        wm.render(0,win);
        win.display();
    }
    win.close();
    auto tmpWorld = wm.getWorld(1);
    assert(tmpWorld->getId()==1);
    tmpWorld->update(sf::Time());
}
