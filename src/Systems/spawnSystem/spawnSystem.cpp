#include <Systems/spawnSystem/spawnSystem.hpp>

namespace ant{
    spawnSystem::spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state){
        name = "spawnSystem";
        RequiredComponents = ComponentsMask::COMPONENT_IN | ComponentsMask::COMPONENT_TRANSFORM;
        this->nEntities = nEntities;
        entityFactory = ef;
        if(ot.asSeconds()<=0.0){
            overTime = sf::seconds(1);
        }else{
            overTime = ot;
        }
        elapsedTime = sf::seconds(0);
        this->spawnPoint = spawnPoint;
        createdEntities = 0;
        states = state;
    }
    void spawnSystem::setStates(long int state){
        states = state;
    }
    void spawnSystem::update(sf::Time dt){
        if(elapsedTime > overTime && createdEntities < nEntities){
            elapsedTime = sf::seconds(0);
            createdEntities +=1;
            ComponentSettings cs;
            cs.loadSettings(Config::ANT_FILE);
            cs.position = spawnPoint + sf::Vector2f(5,5);
            auto ant = entityFactory->createEntity(EntityFactory::Ant,cs);
            ant->addState(states);
            em->addEntity(std::move(ant));
        }
        elapsedTime += clock.restart();
    }
    void spawnSystem::render(sf::RenderWindow& win){
        return;
    }
    void spawnSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::CHANGE_OVERTIME:{
                auto& ot = std::get<0>(e->getAttributes<sf::Time>());
                if(ot.asSeconds() <= 0.0){
                    overTime = sf::seconds(1);
                }else{
                    overTime = ot;
                }
                break;
            }
            case EventType::CHANGE_NENTITIES:{
                auto& numberOfEntitites = std::get<0>(e->getAttributes<int>());
                nEntities = numberOfEntitites;
                break;
            }
        }
    }
    spawnSystem::~spawnSystem(){

    }
}
