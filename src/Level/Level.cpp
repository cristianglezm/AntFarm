#include <Level/Level.hpp>

namespace ant{
    Level::Level(const std::string& assetsFilename,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged)
    : levels(std::make_shared<WorldManager>())
    , eventQueues()
    , gameEventDispatchers(){
        auto eventQueue(std::make_shared<EventQueue>());
        eventQueues.emplace_back(eventQueue);
        gameEventDispatchers.emplace_back(ged);
        worldFactory = std::make_shared<WorldFactory>(ged,eventQueue);
        worldFactory->loadAssets(assetsFilename);
        init(bounds);
    }
    Level::Level(std::shared_ptr<AssetManager> am,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged)
    : levels(std::make_shared<WorldManager>())
    , eventQueues()
    , gameEventDispatchers(){
        auto eventQueue(std::make_shared<EventQueue>());
        eventQueues.emplace_back(eventQueue);
        gameEventDispatchers.emplace_back(ged);
        worldFactory = std::make_shared<WorldFactory>(ged,eventQueue);
        worldFactory->setAssetManager(am);
        init(bounds);
    }
    void Level::init(const sf::FloatRect& bounds){
        levels->clear();
        loadLevel(bounds,Config::LEVELS_FILE);
    }
    bool Level::loadLevel(const sf::FloatRect& bounds,const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        int size = v["levels"].getArray().size();
        for(int i=0;i<size;++i){
            sf::Image img;
            if(!img.loadFromFile(v["levels"][size_t(i)]["image"].getString())){
                throw std::runtime_error("Error loading image from level "
                                         + v["levels"][size_t(i)]["image"].getString()
                                         + " \nindex: " + Utils::toString<int>(i));
            }
            int nEntities = v["levels"][size_t(i)]["nEntities"].getInteger();
            sf::Time overTime = sf::seconds(v["levels"][size_t(i)]["overtime"].getInteger());
            setEventQueue(i,eventQueues[i]);
            setGameEventDispatcher(i,gameEventDispatchers[i]);
            levels->addWorld(worldFactory->create(v["levels"][size_t(i)]["name"].getString(),
                                v["levels"][size_t(i)]["background"].getString(),
                                img,nEntities,overTime,bounds));
            addEventQueue(std::make_shared<EventQueue>());
            addGameEventDispatcher(std::make_shared<GameEventDispatcher>());
        }
        return true;
    }
    void Level::setEventQueue(int id,std::shared_ptr<EventQueue> eq){
        eventQueues[id] = eq;
        worldFactory->setEventQueue(eventQueues[id]);
    }
    void Level::addEventQueue(std::shared_ptr<EventQueue> eq){
        eventQueues.emplace_back(eq);
    }
    void Level::addGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged){
        gameEventDispatchers.emplace_back(ged);
    }
    void Level::setGameEventDispatcher(int id,std::shared_ptr<GameEventDispatcher> ged){
        gameEventDispatchers[id] = ged;
        worldFactory->setGameEventDispatcher(gameEventDispatchers[id]);
    }
    void Level::setWorldFactory(std::shared_ptr<WorldFactory> wf){
        worldFactory = wf;
    }
    void Level::setAssetManager(std::shared_ptr<AssetManager> assets){
        worldFactory->setAssetManager(assets);
    }
    void Level::update(long int id,sf::Time dt){
        levels->update(id,dt);
    }
    void Level::render(long int id,sf::RenderWindow& win){
        levels->render(id,win);
    }
}
