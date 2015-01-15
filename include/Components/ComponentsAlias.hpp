#ifndef _COMPONENT_ALIAS_HPP
#define _COMPONENT_ALIAS_HPP

#include <vector>
#include <memory>
#include <string>
#include <Components/Component.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace ComponentsAlias{
    /**
     *
     */
    using transform = ant::Component<sf::Vector2f,sf::Vector2f,float>;
    /**
     * @brief Component
     * @param sf::FloatRect bounds
     */
    using bounds = ant::Component<sf::FloatRect>;
    /**
     *
     */
    using count = ant::Component<int>;
    using velocity = ant::Component<sf::Vector2f,float,float,float>;
    using sprite = ant::Component<std::string,std::unique_ptr<sf::Sprite>>;
    using destructable = ant::Component<std::string,std::unique_ptr<sf::VertexArray>,sf::FloatRect>;
    using animation = ant::Component<std::vector<std::string>>;
    using passage = ant::Component<sf::Vector2f>;
    using in = ant::Component<>;
    using out = ant::Component<>;
}
#endif // _COMPONENT_ALIAS_HPP
