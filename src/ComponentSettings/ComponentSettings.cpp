#include <ComponentSettings/ComponentSettings.hpp>

namespace ant{
    ComponentSettings::ComponentSettings(){
        minSpeed = 0;
        maxSpeed = 0;
        scale = sf::Vector2f(0,0);
        position = sf::Vector2f(0,0);
        rotation = 90;
        spriteID = "";
        dest = sf::Vector2f(0,0);
        DestructiblePosition = sf::Vector2f(0,0);
        imageID = "";
        bounds = sf::FloatRect(0,0,0,0);
    }
    ComponentSettings::loadSettings(const std::string& filename){

    }
    void ComponentSettings::setSpeed(){

    }
    ComponentSettings::~ComponentSettings(){

    }
};
