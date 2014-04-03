#include <Level/Level.hpp>
namespace ant{
    Level::Level(std::shared_ptr<GameEventDispatcher> ged){
        battlefields.reset(new WorldManager());
        nests.reset(new WorldManager());
        eventQueue.reset(new EventQueue());
        worldFactory.reset(new WorldFactory(ged,eventQueue));
        init();
    }
    void Level::init(){

    }
    bool Level::loadLevel(const std::string& filename){

    }
    void Level::setEventQueue(std::shared_ptr<EventQueue> eq){
        eventQueue = eq;
        worldFactory->setEventQueue(eventQueue);
    }
    void Level::setWorldFactory(std::shared_ptr<WorldFactory> wf){
        worldFactory = wf;
    }
    void Level::update(long int id,long int type,sf::Time dt){
        switch(type){
            case BATTLEFIELD:
                    battlefields->update(id,dt);
                break;
            case NEST:
                    nests->update(id,dt);
                break;
        }
    }
    void Level::render(long int id,long int type,sf::RenderWindow& win){
        switch(type){
                    case BATTLEFIELD:
                            battlefields->render(id,win);
                        break;
                    case NEST:
                            nests->render(id,win);
                        break;
                }
    }
    Level::~Level(){

    }
}
