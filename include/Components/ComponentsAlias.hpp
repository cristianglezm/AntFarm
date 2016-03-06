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
     * @param
     */
    using velocity = ant::Component<sf::Vector2f,float,float,float>;
    using sprite = ant::Component<std::string,std::unique_ptr<sf::Sprite>>;
    using destructable = ant::Component<std::string,std::unique_ptr<sf::VertexArray>,sf::FloatRect>;
    using animation = ant::Component<std::vector<std::string>>;
    using passage = ant::Component<sf::Vector2f>;
    using in = ant::Component<>;
    using out = ant::Component<>;
}
#endif // COMPONENT_ALIAS_HPP
