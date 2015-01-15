////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

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
        /**
         * @brief Clase de un simple boton.
         * @author Cristian Glez <cristian.glez.m@gmail.com>
         * @version 0.1
         */
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
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                virtual ~Button(){}
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
