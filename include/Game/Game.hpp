#ifndef GAME_H
#define GAME_H
#include <Level/Level.hpp>
#include <Config.hpp>
#include <EventQueue/EventQueue.hpp>
namespace ant{
    /**
     *
     *  @author Cristian Glez <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class Game{
        private:
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<Level> level;
            std::shared_ptr<AssetManager> assets;
            sf::RenderWindow win;
            bool running;
            int mode;
            int idWorld;
            bool isPause;
        public:
            Game();
            void run();
            ~Game();
    };
}
#endif // GAME_H
