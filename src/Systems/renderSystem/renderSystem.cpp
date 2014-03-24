#include <Systems/renderSystem/renderSystem.hpp>
namespace ant{
    renderSystem::renderSystem(){
        RequiredComponents = ComponentsMask::COMPONENT_SPRITE
                             | ComponentsMask::COMPONENT_TRANSFORM;
    }
    renderSystem::renderSystem(std::shared_ptr<sf::RenderWindow> rw){
        renderWindow = rw;
    }
    void renderSystem::setRenderWindow(std::shared_ptr<sf::RenderWindow> rw){
        renderWindow = rw;
    }
    void renderSystem::render(){
        for(auto& entity: this->em->getEntities()){
            if((entity->getMask() & RequiredComponents)==RequiredComponents){
                auto& sprite = entity->getComponent(ComponentsMask::COMPONENT_SPRITE)->getProperties<std::unique_ptr<sf::Sprite>>();
                auto& transform = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f>();

            }
        }
    }
    void renderSystem::update(sf::Time dt){
        return;
    }
    renderSystem::~renderSystem(){

    }
}
