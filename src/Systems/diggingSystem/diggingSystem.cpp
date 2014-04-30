#include <Systems/diggingSystem/diggingSystem.hpp>

namespace ant{
    diggingSystem::diggingSystem(sf::VertexArray* map,sf::FloatRect boundsMap){
        name = "diggingSystem";
        this->map = map;
        this->boundsMap = boundsMap;
    }
    void diggingSystem::onNotify(std::shared_ptr<baseEvent> e){

    }
    void diggingSystem::render(sf::RenderWindow& win){

    }
    void diggingSystem::update(sf::Time dt){

    }
    diggingSystem::~diggingSystem(){}
}
