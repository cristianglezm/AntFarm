#include <../include/QuadtreeTest.hpp>
#include <Utils/Quadtree.hpp>
#include <Utils/String.hpp>
#include <Entity/Entity.hpp>
#include <Components/Component.hpp>
#include <Components/ComponentMask.hpp>
#include <EntityManager/EntityManager.hpp>
#include <cassert>
#include <list>
#include <iostream>
bool QuadtreeTest(){
    std::cout << "QuadtreeTest -----------------"<<std::endl;
    ant::Utils::Quadtree qtree(sf::FloatRect(0,0,500,500));
    ant::EntityManager em;
    std::cout << "Insertando Entidades..." << std::endl;
    for(int i=0;i<10;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity("Test" + ant::Utils::toString(i)));
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_BOUNDS,sf::FloatRect(-i,i,20,20)));
        e1->addComponent(std::move(c1));
        em.addEntity(std::move(e1));
    }
    std::cout << "Agregadas al Entity Manager" << std::endl;
    int i=0;
    for(auto& entity:em.getEntities()){
        qtree.insert(entity.get());
    }
    std::cout << "Agregadas al Quadtree" << std::endl;
    std::list<ant::Entity*> entities;
    for(auto& entity:em.getEntities()){
            entities.clear();
        qtree.retrieve(entities,entity.get());
        for(auto entity1:entities){
            auto& properties = entity->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
            sf::FloatRect eBounds = std::get<0>(properties);
            auto& properties1 = entity1->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
            sf::FloatRect eBounds1 = std::get<0>(properties1);
            if(eBounds.intersects(eBounds1)){
                std::cout << "Entity 1 and Entity 2 Collide" << std::endl;
            }else{
                std::cout << "Entity 1 and Entity 2 do not Collide" << std::endl;
            }
        }
    }
}
