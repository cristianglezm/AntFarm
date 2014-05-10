#include <Systems/spawnSystem/spawnSystem.hpp>

namespace ant{
    spawnSystem::spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state){
        name = "spawnSystem";
        RequiredComponents = ComponentsMask::COMPONENT_IN | ComponentsMask::COMPONENT_TRANSFORM;
        this->nEntities = nEntities;
        entityFactory = ef;
        if(ot.asSeconds()==0){
            overTime = sf::seconds(1);
        }else{
            overTime = ot;
        }
        calcOverTime = sf::seconds(nEntities / ot.asSeconds());
        elapsedTime = sf::seconds(0);
        this->spawnPoint = spawnPoint;
        createdEntities = 0;
        states = state;
    }
    void spawnSystem::setStates(long int state){
        states = state;
    }
    void spawnSystem::update(sf::Time dt){
        if(elapsedTime > calcOverTime && createdEntities < nEntities){
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
                auto& ot = e->getAttributes<sf::Time>();
                if(std::get<0>(ot).asSeconds() == 0){
                    calcOverTime = sf::seconds(nEntities / overTime.asSeconds());
                }else{
                    calcOverTime = sf::seconds(nEntities / std::get<0>(ot).asSeconds());
                }
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
