#ifndef LEVEL_H
#define LEVEL_H
#include <list>
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
            static const long int BATTLEFIELD = 0;
            static const long int NEST = 1;
            Level();
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            void setWorldFactory(std::shared_ptr<WorldFactory> wf);
            inline std::shared_ptr<WorldFactory> getWorldFactory(){ return worldFactory; }
            void update(long int id,long int type,sf::Time dt);
            void render(long int id,long int type,sf::RenderWindow& win);
            ~Level();
    };
}

#endif // LEVEL_H
