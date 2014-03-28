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
    assets->addTexture("p","datatest/image1.png");
    ant::ComponentFactory cf(assets);
    sf::RenderWindow win(sf::VideoMode(800,600),"TEST RenderSystem");
    ant::WorldManager wm;
    for(int i=0;i<1;++i){
        std::unique_ptr<ant::SystemManager> sm(new ant::SystemManager());
        for(int j=0;j<1;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("red"));
            e->addComponent(cf.createSprite("p"));
            e->addComponent(cf.createTransform(sf::Vector2f(400,20),sf::Vector2f(1,50),0));
            em->addEntity(std::move(e));
        }
        for(int j=0;j<1;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("black"));
            e->addComponent(cf.createSprite("Ant"));
            e->addComponent(cf.createTransform(sf::Vector2f(400,20),sf::Vector2f(1,1),0));
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
                case sf::Event::MouseButtonPressed:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        auto& properties = em->getEntity("black")->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f,sf::Vector2f,float>();
                        auto& pos = std::get<0>(properties);
                        auto mousePos = sf::Mouse::getPosition(win);
                        pos = (sf::Vector2f)mousePos;
                    }
                    break;
            }
        }
        wm.update(-1,sf::Time());
        win.clear();
        wm.render(0,win);
        win.display();
    }
    auto tmpWorld = wm.getWorld(0);
    assert(tmpWorld->getId()==0);
    tmpWorld->update(sf::Time());
    win.close();
    return true;
}
