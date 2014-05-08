#include <Systems/spawnSystem/spawnSystem.hpp>
#include <iostream>
namespace ant{
    spawnSystem::spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot){
        name = "spawnSystem";
        RequiredComponents = ComponentsMask::COMPONENT_IN | ComponentsMask::COMPONENT_TRANSFORM;
        this->nEntities = nEntities;
        entityFactory = ef;
        overTime = ot;
        calcOverTime = sf::seconds(nEntities / ot.asSeconds());
        elapsedTime = sf::seconds(0);
        createdEntities = 0;
    }
    void spawnSystem::update(sf::Time dt){
        sf::Vector2f spawnPoint;
        sf::Clock clock;
        for(auto& e:em->getEntities()){
            if(e->hasComponent(RequiredComponents)){
                auto& properties = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)
                                                ->getProperties<sf::Vector2f,sf::Vector2f,float>();
                spawnPoint = std::get<0>(properties);
            }
            if(elapsedTime >= calcOverTime && createdEntities < nEntities){
                    /// @todo arreglar creacion
                std::cout << "Elapsed dentro ent = " << elapsedTime.asSeconds() << std::endl;
                std::cout << "Creada Entidad" << std::endl;
                elapsedTime = sf::seconds(0);
                createdEntities +=1;
                ComponentSettings cs;
                cs.loadSettings(Config::ANT_FILE);
                cs.position = spawnPoint;
                entityFactory->createEntity(EntityFactory::Ant,cs);
            }
            elapsedTime += clock.restart();
        }
    }
    void spawnSystem::render(sf::RenderWindow& win){
        return;
    }
    void spawnSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::CHANGE_OVERTIME:{
                auto& ot = e->getAttributes<sf::Time>();
                calcOverTime = sf::seconds(nEntities / std::get<0>(ot).asSeconds());
                break;
            }
            case EventType::CHANGE_NENTITIES:{
                auto& numberOfEntitites = e->getAttributes<int>();
                calcOverTime = sf::seconds(std::get<0>(numberOfEntitites) / overTime.asSeconds());
                break;
            }
        }
    }
    spawnSystem::~spawnSystem(){

    }
}
