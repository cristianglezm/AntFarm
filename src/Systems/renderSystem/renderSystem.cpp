#include <Systems/renderSystem/renderSystem.hpp>
namespace ant{
    renderSystem::renderSystem(){
        name = "renderSystem";
        RequiredComponents = ComponentsMask::COMPONENT_SPRITE | ComponentsMask::COMPONENT_TRANSFORM;
    }
    void renderSystem::render(sf::RenderWindow& win){
        for(auto& entity: this->em->getEntities()){
            if(entity->hasComponent(RequiredComponents)){
                // obtenemos las propiedades del componente
                auto& sprite = entity->getComponent(ComponentsMask::COMPONENT_SPRITE)->getProperties<std::string,std::unique_ptr<sf::Sprite>>();
                auto& transform = entity->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::Vector2f,sf::Vector2f,float>();
                // obtenemos la sprite
                auto& spr = std::get<1>(sprite);
                sf::Vector2f& position = std::get<0>(transform);
                sf::Vector2f& scale = std::get<1>(transform);
               // float& rotation = std::get<2>(transform);
                // si esta dentro de la pantalla actual se muestra.
                if(win.getViewport(win.getView()).contains(position.x,position.y)){
                    spr->setPosition(position);
                    spr->setScale(scale);
                    //spr->setRotation(rotation);
                    win.draw(*spr);
                }
            }
            // si tiene el destructable se renderiza tambien.
            if(entity->hasComponent(ComponentsMask::COMPONENT_DESTRUCTABLE)){
                auto& destructable = entity->getComponent(ComponentsMask::COMPONENT_DESTRUCTABLE)
                                            ->getProperties<std::string,std::unique_ptr<sf::VertexArray>,sf::FloatRect>();
                win.draw(*std::get<1>(destructable));
            }
        }
    }
    void renderSystem::update(const sf::Time& dt){
        return;
    }
}
