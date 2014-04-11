#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include <SFML/System/Time.hpp>
#include <WorldManager/WorldManager.hpp>
#include <WorldFactory/WorldFactory.hpp>
#include <EventQueue/EventQueue.hpp>
#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    /**
     * Clase que tiene el nivel del juego
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Level{
        private:
            std::shared_ptr<WorldManager> battlefields;
            std::shared_ptr<WorldManager> nests;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<WorldFactory> worldFactory;
        public:
            static const long int BATTLEFIELD = 0;
            static const long int NEST = 1;
            /**
             *
             *
             */
            Level(const std::string& assetsFilename,std::shared_ptr<GameEventDispatcher> ged);
            /**
             *
             *
             */
            void init();
            /**
             *
             *
             */
            bool loadLevel(const std::string& filename);
            /**
             *
             *
             */
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             *
             *
             */
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            /**
             *
             *
             */
            void setWorldFactory(std::shared_ptr<WorldFactory> wf);
            /**
             *
             *
             */
            inline std::shared_ptr<WorldFactory> getWorldFactory(){ return worldFactory; }
            /**
             *
             *
             */
             void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             *
             *
             */
             inline std::shared_ptr<AssetManager> getAssetManager(){ return worldFactory->getAssetManager(); }
            /**
             *
             *
             */
            void update(long int id,long int type,sf::Time dt);
            /**
             *
             *
             */
            void render(long int id,long int type,sf::RenderWindow& win);
            ~Level();
    };
}

#endif // LEVEL_H
