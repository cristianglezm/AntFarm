#include <Components/SpriteComponent/SpriteComponent.hpp>
namespace ant{
        SpriteComponent::SpriteComponent(long int id):Component(id){

        }
        void SpriteComponent::setSprite(sf::Sprite& sprite){
            this->sprite = sprite;
        }
        SpriteComponent& SpriteComponent::operator=(const Component& c){
            return *this;
        }
}
