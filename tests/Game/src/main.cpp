#include <ComponentTest.hpp>
#include <EntityTest.hpp>
#include <EntityManagerTest.hpp>
#include <EventTest.hpp>
#include <EventQueueTest.hpp>
#include <SystemTest.hpp>
#include <SystemManagerTest.hpp>
#include <QuadtreeTest.hpp>
#include <WorldManagerTest.hpp>
#include <renderSystemTest.hpp>
////////////////////////////
#include <Utils/Quadtree.hpp>
#include <Utils/String.hpp>
#include <Entity/Entity.hpp>
#include <Components/Component.hpp>
#include <Components/ComponentMask.hpp>
#include <Components/ComponentsAlias.hpp>
#include <EntityManager.hpp>
#include <assetManagerTest.hpp>
#include <cassert>
#include <list>
#include <iostream>
#include <cstdlib>
////////////////////////////////////
bool CollisionSpeedTest();

int main(){
    ComponentTest();
    EntityTest();
    EntityManagerTest();
    EventTest();
    EventQueueTest();
    SystemTest();
    SystemManagerTest();
    QuadtreeTest(); // 1000 Entidades -> 0.156
    CollisionSpeedTest(); // 1000 Entidades -> 59 secs
    WorldManagerTest();
    renderSystemTest();
    assetManagerTest();
    system("pause");
    return 0;
}

bool CollisionSpeedTest(){
    ant::EntityManager em;
    std::cout << "Insertando Entidades..." << std::endl;
    for(int i=0;i<10;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity("Test" + ant::Utils::toString(i)));
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_TRANSFORM,sf::FloatRect(-i,i,20,20)));
        e1->addComponent(std::move(c1));
        em.addEntity(std::move(e1));
    }
    for(auto& entity1:em.getEntities()){
        auto& properties1 = entity1->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                    ->getProperties<ComponentsAlias::bounds>();
        sf::FloatRect eBounds1 = std::get<0>(properties1);
        for(auto& entity2:em.getEntities()){
            auto& properties2 = entity2->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                        ->getProperties<ComponentsAlias::bounds>();
            sf::FloatRect eBounds2 = std::get<0>(properties2);
            if(eBounds1.intersects(eBounds2)){
               std::cout << "Entity 1 and Entity 2 Collide" << std::endl;
            }else{
                std::cout << "Entity 1 and Entity 2 do not Collide" << std::endl;
            }
        }
    }
    return true;
}
