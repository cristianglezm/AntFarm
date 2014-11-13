#include <GUI/Button/Button.hpp>

namespace ant{
    namespace GUI{
        Button::Button()
        :position(0.f,0.f)
        ,size(100.f,100.f){
            action = [](Entity* e,sf::VertexArray* map, sf::FloatRect bounds){};
        }
        Button::Button(sf::Vector2f position,sf::Vector2f size,sf::Text text, constructorSystem::command action){
            this->position = position;
            this->size = size;
            this->action = action;
            this->text = text;
        }
        Button::Button(sf::Vector2f position,sf::Vector2f size,sf::Sprite image,constructorSystem::command action){
            this->position = position;
            this->size = size;
            this->action = action;
            this->image = image;
        }
        Button::Button(sf::Vector2f position,sf::Vector2f size,sf::Sprite image,sf::Text text,constructorSystem::command action){
            this->position = position;
            this->size = size;
            this->action = action;
            this->image = image;
            this->text = text;
        }
        void Button::setAction(constructorSystem::command action){
            this->action = action;
        }
        void Button::setPosition(sf::Vector2f pos){
            position = pos;
        }
        void Button::setSize(sf::Vector2f size){
            this->size = size;
        }
        void Button::setImage(sf::Sprite sprite){
            image = sprite;
        }
        void Button::setText(sf::Text text){
            this->text = text;
        }
        bool Button::contains(sf::Vector2f point){
            sf::FloatRect v(position.x,position.y,size.x,size.y);
            return v.contains(point);
        }
        void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const{
            target.draw(image);
            target.draw(text);
        }
    }
}
