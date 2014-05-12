#include <Config.hpp>

namespace ant{
    const std::string Config::VERSION = "0.5 Milestone";
    const std::string Config::ASSETS_GAME_JSON = "data/config/assets.json";
    const std::string Config::ANT_FILE = "data/config/entities/Ant.json";
    const std::string Config::INDOOR_FILE = "data/config/entities/InDoor.json";
    const std::string Config::OUTDOOR_FILE = "data/config/entities/OutDoor.json";
    const sf::FloatRect Config::screenSize = sf::FloatRect(0,0,800,600);
}
