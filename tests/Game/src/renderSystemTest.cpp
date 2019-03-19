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
#include <Systems/collisionSystem/collisionSystem.hpp>
#include <Systems/movementSystem/movementSystem.hpp>
#include <Utils/Math.hpp>
bool renderSystemTest(){
std::cout << "renderSystemTest Test -----------" << std::endl;
    std::shared_ptr<ant::EntityManager> em(new ant::EntityManager());
    std::shared_ptr<ant::EventQueue> eq(new ant::EventQueue());
    std::shared_ptr<ant::AssetManager> assets(new ant::AssetManager());
    std::shared_ptr<ant::GameEventDispatcher> ged(new ant::GameEventDispatcher());
    assets->addTexture("Ant","datatest/image.png");
    assets->addTexture("p","datatest/image1.png");
    assets->addImage("p","datatest/image1.png");
    ant::ComponentFactory cf(assets);
    sf::RenderWindow win(sf::VideoMode(800,600),"TEST RenderSystem");
    ant::WorldManager wm;
    for(int i=0;i<1;++i){
        std::unique_ptr<ant::SystemManager> sm(new ant::SystemManager());
        for(int j=0;j<1;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("red"));
            //e->addComponent(cf.createSprite("p"));
            e->addComponent(cf.createTransform(sf::Vector2f(100,360),sf::Vector2f(1,1),0));
            e->addComponent(cf.createBounds(sf::FloatRect(0,0,50,50)));
            e->addComponent(cf.createDestructable(sf::Vector2f(100,360),"p"));
            em->addEntity(std::move(e));
        }
        for(int j=0;j<6;++j){
            std::unique_ptr<ant::Entity> e(new ant::Entity("black"+ant::Utils::toString(j)));
            e->addComponent(cf.createSprite("Ant"));
            e->addComponent(cf.createTransform(sf::Vector2f(100,50*j),sf::Vector2f(1,1),45));
            e->addComponent(cf.createBounds(sf::FloatRect(0,0,50,50)));
            e->addComponent(cf.createVelocity(0.06,0.1,1));
            em->addEntity(std::move(e));
        }
        {
            std::shared_ptr<ant::renderSystem> ts(new ant::renderSystem());
            ts->setEntityManager(em);
            ts->setEventQueue(eq);
            sm->addSystem(ts);
        }
        {
            auto& gameMap = std::get<1>(em->getEntity("red")->getComponent(ComponentsMask::COMPONENT_DESTRUCTABLE)
                                        ->getProperties<ComponentsAlias::destructable>());
            auto& bounds = std::get<2>(em->getEntity("red")->getComponent(ComponentsMask::COMPONENT_DESTRUCTABLE)
                                        ->getProperties<ComponentsAlias::destructable>());
            std::shared_ptr<ant::collisionSystem> ts(new ant::collisionSystem(bounds,gameMap.get()));
            ts->setEntityManager(em);
            ts->setEventQueue(eq);
            sm->addSystem(ts);
        }
        {
            std::shared_ptr<ant::movementSystem> ts(new ant::movementSystem());
            ts->setEntityManager(em);
            ts->setEventQueue(eq);
            sm->addSystem(ts);
            ged->onCollision.addObserver(ts.get());
        }
        std::unique_ptr<ant::World> w1(new ant::World(i,em,std::move(sm),eq));
        wm.addWorld(std::move(w1));
    }
    bool running=true;
    auto& prop = em->getEntity("black0")->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<ComponentsAlias::bounds>();
    auto& bounds = std::get<0>(prop);
    while(running){
        while(!eq->isEmpty()){
            ged->DispatchEvent(eq->pop());
        }
        sf::Event event;
        while(win.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        auto& properties1 = em->getEntity("black0")->getComponent(ComponentsMask::COMPONENT_VELOCITY)
                                                                    ->getProperties<ComponentsAlias::velocity>();
                        std::get<1>(properties1) +=0.1;
                    }
                    break;
            }
        }
        for(auto& e : em->getEntities()){
            auto& properties = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                    ->getProperties<ComponentsAlias::transform>();
            auto& pos = std::get<0>(properties);
            auto& rotation = std::get<2>(properties);
            auto mousePos = sf::Mouse::getPosition(win);
            rotation = ant::Utils::toDegrees(ant::Utils::getDirection(pos,(sf::Vector2f)mousePos));
        }
        sf::Time time;
        wm.update(0,time);
        win.clear(sf::Color::White);
        wm.render(0,win);
        win.display();
    }
    auto tmpWorld = wm.getWorld(0);
    assert(tmpWorld->getId()==0);
    //tmpWorld->update(sf::Time());
    win.close();
    return true;
}
