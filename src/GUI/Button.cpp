#include <GUI/Button.hpp>

namespace ant{
    namespace GUI{
        Button::Button()
        : position(0.f,0.f)
        , scale(1.f,1.f)
        , image()
        , text(){
            action = [](Entity* e,sf::VertexArray* map, sf::FloatRect bounds){};
        }
        Button::Button(sf::Vector2f position, sf::Text text)
        : position(position)
        , scale(1.f,1.f)
        , image()
        , text(text){
            this->text.setPosition(position);
            this->action = [](Entity* e,sf::VertexArray* map, sf::FloatRect bounds){};
        }
        Button::Button(sf::Vector2f position, sf::Text text, constructorSystem::command action)
        : position(position)
        , scale(1.f,1.f)
        , image()
        , text(text){
            this->text.setPosition(position);
            this->action = action;
        }
        Button::Button(sf::Vector2f position, sf::Sprite image)
        : position(position)
        , scale(1.f,1.f)
        , image(image)
        , text(){
            this->image.setPosition(position);
            this->image.setScale(scale);
            this->action = [](Entity* e,sf::VertexArray* map, sf::FloatRect bounds){};
        }
        Button::Button(sf::Vector2f position, sf::Sprite image, constructorSystem::command action)
        : position(position)
        , scale(1.f,1.f)
        , image(image)
        , text(){
            this->image.setPosition(position);
            this->image.setScale(scale);
            this->action = action;
        }
        Button::Button(sf::Vector2f position, sf::Sprite image, sf::Text text, constructorSystem::command action)
        : position(position)
        , scale(1.f,1.f)
        , image(image)
        , text(text){
            this->image.setPosition(position);
            this->text.setPosition(position);
            this->image.setScale(scale);
            this->text.setScale(scale);
            this->action = action;
        }
        void Button::setAction(constructorSystem::command action){
            this->action = action;
        }
        void Button::setPosition(sf::Vector2f pos){
            position = pos;
            image.setPosition(position);
            text.setPosition(position);
        }
        void Button::setImage(sf::Sprite sprite){
            image = sprite;
            image.setPosition(position);
            image.setScale(scale);
        }
        void Button::setText(sf::Text text){
            this->text = text;
            this->text.setPosition(position);
            text.setScale(scale);
        }
        void Button::setScale(sf::Vector2f scale){
            image.setScale(scale);
            text.setScale(scale);
            this->scale = scale;
        }
        void Button::setTextSize(int size){
            text.setCharacterSize(size);
            text.setScale(scale);
        }
        bool Button::contains(float x, float y) const{
            return image.getGlobalBounds().contains(x,y);
        }
        bool Button::contains(sf::Vector2f point) const{
            return image.getGlobalBounds().contains(point);
        }
        void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
            target.draw(image);
            target.draw(text);
        }
    }
}
