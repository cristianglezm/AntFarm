#ifndef COMPONENT_ALIAS_HPP
#define COMPONENT_ALIAS_HPP

#include <vector>
#include <memory>
#include <string>
#include <Components/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ComponentsAlias{
    /**
     * @brief component transform
     */
    using transform = ant::Component<sf::Vector2f,sf::Vector2f,float>;
    /**
     * @brief Component bounds
     * @param sf::FloatRect bounds
     */
    using bounds = ant::Component<sf::FloatRect>;
    /**
     * @brief Component count
     * @param int counter
     */
    using count = ant::Component<int>;
    /**
     * @brief component velocity
     * @param sf::Vector2f velocity
     * @param float speed
     * @param float minSpeed
     * @param float maxSpeed
     */
    using velocity = ant::Component<sf::Vector2f,float,float,float>;
    /**
     * @brief component Sprite
     * @param std::string id of the sprite
     * @param std::unique_ptr<sf::Sprite>
     */
    using sprite = ant::Component<std::string,std::unique_ptr<sf::Sprite>>;
    /**
     * @brief component Destructable
     * @param std::string destructable id
     * @param std::unique_ptr<sf::VertexArray> array of vertices
     * @param sf::FloatRect bounds of destructable
     */
    using destructable = ant::Component<std::string,std::unique_ptr<sf::VertexArray>,sf::FloatRect>;
    /**
     * @brief component animation
     * @param std::vector<std::string> vector for the id of sprites.
     */
    using animation = ant::Component<std::vector<std::string>>;
    using passage = ant::Component<sf::Vector2f>;
    using in = ant::Component<>;
    using out = ant::Component<>;
}
#endif // COMPONENT_ALIAS_HPP
