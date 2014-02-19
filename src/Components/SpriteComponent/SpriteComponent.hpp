#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H
#include "../Component.hpp"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component{
    private:
        sf::Sprite sprite;
    public:
        SpriteComponent(long int id);
        void setSprite(sf::Sprite& sprite);
        SpriteComponent& operator=(const Component& c);
        inline const sf::Sprite& getSprite();
};
#endif // SPRITE_COMPONENT_H
