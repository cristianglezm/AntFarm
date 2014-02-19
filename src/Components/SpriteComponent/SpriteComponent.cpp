#include "SpriteComponent.hpp"

        SpriteComponent::SpriteComponent(long int id):Component(id){

        }
        void SpriteComponent::setSprite(sf::Sprite& sprite){
            this->sprite = sprite;
        }
        SpriteComponent& SpriteComponent::operator=(const Component& c){
            return *this;
        }
        inline const sf::Sprite& SpriteComponent::getSprite(){
            return sprite;
        }

