#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H
#include "../Component.hpp"
#include <SFML/Graphics.hpp>
/**
 *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
 *  @version 0.1
 */
class SpriteComponent : public Component{
    private:
        sf::Sprite sprite;
    public:
        SpriteComponent(long int id);
        void setSprite(sf::Sprite& sprite);
        SpriteComponent& operator=(const Component& c);
        inline sf::Sprite& getSprite(){ return this->sprite;}
};
#endif // SPRITE_COMPONENT_H
