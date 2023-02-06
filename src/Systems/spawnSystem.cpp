#include <Systems/spawnSystem.hpp>
#include <Event/EventsAlias.hpp>

namespace ant{
    spawnSystem::spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,ComponentsMask::Mask& state)
    : entityFactory(ef)
    , nEntities(nEntities)
    , createdEntities(0)
    , overTime(sf::seconds(1))
    , elapsedTime(sf::seconds(0))
    , spawnPoint(spawnPoint)
    , clock()
    , states(state)
    , cs(){
        name = "spawnSystem";
        RequiredComponents = ComponentsMask::COMPONENT_IN | ComponentsMask::COMPONENT_TRANSFORM;
        if(ot.asSeconds()<=0.0){
            overTime = sf::seconds(1);
        }else{
            overTime = ot;
        }
        cs.loadSettings(Config::ANT_FILE);
        cs.position = spawnPoint + sf::Vector2f(5,5);
    }
    void spawnSystem::setStates(ComponentsMask::Mask& state){
        states = state;
    }
    void spawnSystem::update([[maybe_unused]] const sf::Time& dt){
        if(elapsedTime > overTime && createdEntities < nEntities){
            elapsedTime = sf::seconds(0);
            ++createdEntities;
            auto ant = entityFactory->createEntity(EntityFactory::Ant,cs);
            ant->addState(states);
            em->addEntity(std::move(ant));
        }
        elapsedTime += clock.restart();
    }
    void spawnSystem::render([[maybe_unused]] sf::RenderWindow& win){
        return;
    }
    void spawnSystem::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::CHANGE_OVERTIME:{
                auto& ot = std::get<0>(e->getAttributes<EventsAlias::change_overtime>());
                if(ot.asSeconds() <= 0.0){
                    overTime = sf::seconds(1);
                }else{
                    overTime = ot;
                }
                break;
            }
            case EventType::CHANGE_NENTITIES:{
                auto& numberOfEntitites = std::get<0>(e->getAttributes<EventsAlias::change_nentities>());
                nEntities = numberOfEntitites;
                break;
            }
        }
    }
}
