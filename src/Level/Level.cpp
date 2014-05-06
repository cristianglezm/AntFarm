#include <Level/Level.hpp>
namespace ant{
    Level::Level(const std::string& assetsFilename,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged){
        levels.reset(new WorldManager());
        eventQueue.reset(new EventQueue());
        gameEventDispatcher = ged;
        worldFactory.reset(new WorldFactory(ged,eventQueue));
        worldFactory->loadAssets(assetsFilename);
        init(bounds);
    }
    void Level::init(const sf::FloatRect& bounds){
        /// @todo crear mundos iniciales, etc.
        loadLevel(bounds,"data/config/levels.json");
    }
    bool Level::loadLevel(const sf::FloatRect& bounds,const std::string& filename){
        /// @todo Implement
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
            int nEntities = v["levels"][size_t(i)]["nEntities"].getInt();
            sf::Time overTime;
            overTime = sf::seconds(v["levels"][size_t(i)]["overtime"].getInt());
            levels->addWorld(worldFactory->create(v["levels"][size_t(i)]["name"].getString(),
                                 img,nEntities,overTime,bounds));
        }
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
    void Level::setAssetManager(std::shared_ptr<AssetManager> assets){
        worldFactory->setAssetManager(assets);
    }
    void Level::update(long int id,sf::Time dt){
        levels->update(id,dt);
    }
    void Level::render(long int id,sf::RenderWindow& win){
        levels->render(id,win);
    }
    Level::~Level(){

    }
}
