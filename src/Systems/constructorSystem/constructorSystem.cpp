#include <Systems/constructorSystem/constructorSystem.hpp>

namespace ant{
    constructionSystem::constructionSystem(sf::VertexArray* map,sf::FloatRect boundsMap){
        name = "constructionSystem";
        this->map = map;
        this->boundsMap = boundsMap;
    }
    void constructionSystem::onNotify(std::shared_ptr<baseEvent> e){

    }
    void constructionSystem::render(sf::RenderWindow& win){

    }
    void constructionSystem::update(sf::Time dt){

    }
    constructionSystem::~constructionSystem(){}
}
