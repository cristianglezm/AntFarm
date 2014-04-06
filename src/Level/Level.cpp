#include <Level/Level.hpp>
namespace ant{
    Level::Level(const std::string& assetsFilename,std::shared_ptr<GameEventDispatcher> ged){
        battlefields.reset(new WorldManager());
        nests.reset(new WorldManager());
        eventQueue.reset(new EventQueue());
        gameEventDispatcher = ged;
        worldFactory.reset(new WorldFactory(ged,eventQueue));
        /// TODO cargar assets
        init();
    }
    void Level::init(){
        /// TODO crear mundos iniciales, etc.
        nests->addWorld(worldFactory->createNest());
    }
    bool Level::loadLevel(const std::string& filename){
        return false;
    }
    void Level::setEventQueue(std::shared_ptr<EventQueue> eq){
        eventQueue = eq;
        worldFactory->setEventQueue(eventQueue);
        worldFactory->setGameEventDispatcher(gameEventDispatcher);
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
