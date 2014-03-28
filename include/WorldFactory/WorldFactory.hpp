#ifndef WORLD_FACTORY_H
#define WORLD_FACTORY_H
#include <World/World.hpp>
#include <EventQueue/EventQueue.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    class WorldFactory{
        private:
            long int nestId;
            long int battlefieldId;
            std::shared_ptr<EntityFactory> entityFactory;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
        public:
            WorldFactory();
            WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq);
            std::unique_ptr<World> createNest();
            std::unique_ptr<World> createBattlefield();
            void setEntityFactory(std::shared_ptr<EntityFactory> ef);
            inline std::shared_ptr<EntityFactory> getEntityFactory(){ return this->entityFactory; }
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return this->gameEventDispatcher; }
            ~WorldFactory();
    };
}
#endif // WORLD_FACTORY_H
