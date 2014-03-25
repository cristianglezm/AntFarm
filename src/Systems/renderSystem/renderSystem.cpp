#include <Systems/renderSystem/renderSystem.hpp>
namespace ant{
    renderSystem::renderSystem(long int req): System(req){}
    void renderSystem::render(sf::RenderWindow& win){
        for(auto& entity: this->em->getEntities()){
            if((entity->getMask() & RequiredComponents)==RequiredComponents){
                auto& sprite = entity->getComponent(ComponentsMask::COMPONENT_SPRITE)->getProperties<std::unique_ptr<sf::Sprite>>();
                auto& transform = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f,sf::Vector2f,float>();
                auto& spr = std::get<0>(sprite);
                sf::Vector2f& position = std::get<0>(transform);
                sf::Vector2f& scale = std::get<1>(transform);
                float& rotation = std::get<2>(transform);
                if(win.getViewport(win.getView()).contains(position.x,position.y)){
                    spr->setPosition(position);
                    spr->setScale(scale);
                    spr->setRotation(rotation);
                    win.draw(*spr);
                }
            }
        }
    }
    void renderSystem::update(sf::Time dt){
        return;
    }
    renderSystem::~renderSystem(){

    }
}
