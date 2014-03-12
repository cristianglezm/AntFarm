#ifndef LEVEL_H
#define LEVEL_H
#include <list>
#include <memory>
#include <SFML/System/Time.hpp>

#include <World/World.hpp>
#include <WorldFactory/WorldFactory.hpp>
#include <EventQueue/EventQueue.hpp>
#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    class Level{
        private:
            std::list<std::unique_ptr<World>> battlefields;
            std::list<std::unique_ptr<World>> nests;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<WorldFactory> worldFactory;

        public:
            Level();
            void update(sf::Time dt);
            void render();
            ~Level();
    };
}

#endif // LEVEL_H
