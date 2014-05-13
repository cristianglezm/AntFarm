#ifndef ANT_BUTTON_H
#define ANT_BUTTON_H
#include <SFML/Graphics/Drawable.hpp>
#include <Systems/constructorSystem/constructorSystem.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
namespace ant{
    namespace GUI{
        class Button : public sf::Drawable{
            public:
                Button();
                Button(sf::Vector2f position,sf::Vector2f size,sf::Text text, constructorSystem::command action);
                Button(sf::Vector2f position,sf::Vector2f size,sf::Sprite image,constructorSystem::command action);
                Button(sf::Vector2f position,sf::Vector2f size,sf::Sprite image,sf::Text text,constructorSystem::command action);
                void setAction(constructorSystem::command action);
                inline constructorSystem::command getAction(){ return action; }
                void setPosition(sf::Vector2f pos);
                inline sf::Vector2f getPosition(){ return position; }
                void setSize(sf::Vector2f size);
                inline sf::Vector2f getSize(){ return size; }
                void setImage(sf::Sprite sprite);
                inline sf::Sprite getSprite(){ return image;}
                void setText(sf::Text text);
                inline sf::Text getText(){ return text; }
                bool contains(sf::Vector2f point);
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
                ~Button();
            private:
                constructorSystem::command action;
                sf::Vector2f position;
                sf::Vector2f size;
                sf::Sprite image;
                sf::Text text;
        };
    }
}
#endif // ANT_BUTTON_H
