#ifndef _EVENTS_ALIAS_HPP
#define _EVENTS_ALIAS_HPP

#include <Entity/Entity.hpp>
#include <Systems/constructorSystem/constructorSystem.hpp>
#include <SFML/System/Vector2.hpp>

namespace EventsAlias{
    using change_command = ant::Event<ant::constructorSystem::command>;
    using terrain_collision = ant::Event<ant::Entity*,int>;
    using collision = ant::Event<ant::Entity*,ant::Entity*>;
    using out_map = ant::Event<ant::Entity*>;
    using change_overtime = ant::Event<sf::Time>;
    using change_nentities = ant::Event<int>;
    using select_entity = ant::Event<sf::Vector2i>;
    using level_complete = ant::Event<>;
    using level_failed = ant::Event<>;
    using update_score = ant::Event<int>;
}

#endif // _EVENTS_ALIAS_HPP
