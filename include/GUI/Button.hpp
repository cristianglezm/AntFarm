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
         * @brief Simple Button Class
         * @author Cristian Glez <cristian.glez.m@gmail.com>
         * @version 0.1
         */
        class Button : public sf::Drawable{
            public:
                /**
                 * @brief default Constructor
                 */
                Button();
                /**
                 * @brief Constructor with text
                 * @param position sf::Vector2f
                 * @param text sf::Text
                 */
                Button(sf::Vector2f position, sf::Text text);
                /**
                 * @brief Constructor with text and action
                 * @param position sf::Vector2f
                 * @param text sf::Text
                 * @param action constructorSystem::command lambda to send
                 */
                Button(sf::Vector2f position, sf::Text text, constructorSystem::command action);
                /**
                 * @brief Constructor with an image.
                 * @param position sf::Vector2f
                 * @param image sf::Sprite
                 */
                Button(sf::Vector2f position, sf::Sprite image);
                /**
                 * @brief Constructor with an image and action
                 * @param position sf::Vector2f
                 * @param image sf::Sprite
                 * @param action constructorSystem::command lambda to send
                 */
                Button(sf::Vector2f position, sf::Sprite image, constructorSystem::command action);
                /**
                 * @brief Constructor with and image, text and action
                 * @param position sf::Vector2f
                 * @param image sf:Sprite
                 * @param text sf::Text
                 * @param action constructorSystem::command lambda to send
                 */
                Button(sf::Vector2f position, sf::Sprite image, sf::Text text, constructorSystem::command action);
                /**
                 * @brief setter for action
                 * @param action
                 */
                void setAction(constructorSystem::command action);
                /**
                 * @brief getter for action
                 * You need to call this and execute to execute the command
                 * @return constructorSystem::command
                 */
                inline constructorSystem::command getAction() const{ return action; }
                /**
                 * @brief setter for position
                 * @param pos
                 */
                void setPosition(sf::Vector2f pos);
                /**
                 * @brief getter for position
                 * @return sf::Vector2f
                 */
                inline sf::Vector2f getPosition() const{ return position; }
                /**
                 * @brief setter for the scale
                 * @param scale sf::Vector2f
                 */
                void setScale(sf::Vector2f scale);
                /**
                 * @brief getter for the image Size
                 * @return sf::Vector2f
                 */
                inline sf::Vector2f getImageSize() const{ return sf::Vector2f(image.getGlobalBounds().width,image.getGlobalBounds().height); }
                /**
                 * @brief setter for image
                 * @param sprite sf::Sprite
                 */
                void setImage(sf::Sprite sprite);
                /**
                 * @brief getter for the image
                 * @return sf::Sprite
                 */
                inline const sf::Sprite& getImage() const{ return image; }
                /**
                 * @brief setter for text size
                 * @param size int
                 */
                void setTextSize(int size);
                /**
                 * @brief setter for text
                 * @param text sf::Text
                 */
                void setText(sf::Text text);
                /**
                 * @brief getter for text
                 * @return const sf::Text&
                 */
                inline const sf::Text& getText() const{ return text; }
                /**
                 * @brief checks if the point is inside
                 * @param point
                 * @return bool
                 */
                bool contains(sf::Vector2f point) const;
                /**
                 * @brief checks if the point is inside
                 * @param x float
                 * @param y float
                 * @return bool
                 */
                bool contains(float x, float y) const;
                /**
                 * @brief draws the image and text of the button
                 * @param target
                 * @param states
                 */
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
                virtual ~Button() = default;
            private:
                constructorSystem::command action;
                sf::Vector2f position;
                sf::Vector2f scale;
                sf::Sprite image;
                sf::Text text;
        };
    }
}
#endif // ANT_BUTTON_H
