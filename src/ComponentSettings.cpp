#include <ComponentSettings.hpp>

namespace ant{
    ComponentSettings::ComponentSettings()
    : entityName("")
    , minSpeed(0)
    , maxSpeed(0)
    , scale(sf::Vector2f(1,1))
    , position(sf::Vector2f(0,0))
    , rotation(0)
    , spriteID("")
    , animation()
    , dest(sf::Vector2f(0,0))
    , DestructiblePosition(sf::Vector2f(0,0))
    , imageID("")
    , bounds(sf::FloatRect(0,0,0,0))
    , count(10)
    , Speed(0){}
    void ComponentSettings::loadSettings(const std::string& filename){
        JsonBox::Value v;
    #if defined ANDROID
        v.loadFromString(std::string(android::readAssetsFile(filename).data()));
    #else
        v.loadFromFile(filename);
    #endif
        entityName = v["Entity"]["name"].getString();
        if(!v["Entity"]["Components"].isNull()){
            int size = v["Entity"]["Components"].getArray().size();
            if(size>0){
                for(int i=0;i<size;++i){
                    std::string id = v["Entity"]["Components"][size_t(i)]["id"].getString();
                    if(id == "velocity"){
                        minSpeed = v["Entity"]["Components"][size_t(i)]["properties"]["minSpeed"].getDouble();
                        maxSpeed = v["Entity"]["Components"][size_t(i)]["properties"]["maxSpeed"].getDouble();
                        setSpeed(v["Entity"]["Components"][size_t(i)]["properties"]["Speed"].getDouble());
                    }else if(id == "transform"){
                        scale = sf::Vector2f(v["Entity"]["Components"][size_t(i)]["properties"]["scale"]["x"].getDouble(),
                                             v["Entity"]["Components"][size_t(i)]["properties"]["scale"]["y"].getDouble()
                                             );
                        if(scale.x <=0.0 || scale.y <= 0.0){scale = sf::Vector2f(1,1);}
                        position = sf::Vector2f(v["Entity"]["Components"][size_t(i)]["properties"]["position"]["x"].getDouble(),
                                                v["Entity"]["Components"][size_t(i)]["properties"]["position"]["y"].getDouble()
                                                );
                        rotation = v["Entity"]["Components"][size_t(i)]["properties"]["rotation"].getDouble();
                    }else if(id == "sprite"){
                        spriteID = v["Entity"]["Components"][size_t(i)]["properties"]["id"].getString();
                    }else if(id == "bounds"){
                        bounds = sf::FloatRect(v["Entity"]["Components"][size_t(i)]["properties"]["left"].getDouble(),
                                               v["Entity"]["Components"][size_t(i)]["properties"]["top"].getDouble(),
                                               v["Entity"]["Components"][size_t(i)]["properties"]["width"].getDouble(),
                                               v["Entity"]["Components"][size_t(i)]["properties"]["height"].getDouble()
                                               );
                    }else if(id == "destructable"){
                        DestructiblePosition = sf::Vector2f(v["Entity"]["Components"][size_t(i)]["properties"]["position"]["x"].getDouble(),
                                                            v["Entity"]["Components"][size_t(i)]["properties"]["position"]["y"].getDouble()
                                                            );
                        imageID = v["Entity"]["Components"][size_t(i)]["properties"]["imageID"].getString();
                    }else if(id == "buildCounter"){
                        count = v["Entity"]["Components"][size_t(i)]["properties"]["count"].getInteger();
                    }
                }
            }
        }
    }
    void ComponentSettings::setSpeed(float speed){
        Speed = speed;
        if(Speed > maxSpeed){
            Speed = maxSpeed;
        }else if(Speed < minSpeed){
            Speed = minSpeed;
        }
    }
}
