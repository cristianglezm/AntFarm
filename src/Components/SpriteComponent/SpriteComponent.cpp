#include "../Component.cpp"
#ifndef _SFML_
#include <SFML/Graphics.hpp>
#endif // _SFML_
class SpriteComponent : public Component{
    private:
        sf::Sprite sprite;
    public:
        SpriteComponent(long int id):Component(id){

        }
        void setSprite(sf::Sprite sprite){
            this->sprite = sprite;
        }
        SpriteComponent& operator=(const Component& c){
            return *this;
        }
        inline const sf::Sprite getSprite(){
            return sprite;
        }
};

