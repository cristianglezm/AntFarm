#ifndef GAME_H
#define GAME_H
#include <Level/Level.hpp>
#include <Config.hpp>
#include <EventQueue/EventQueue.hpp>
namespace ant{
    /**
     * @brief Clase Principal del juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Game{
        public:
            /**
             * @brief Constructor por defecto.
             */
            Game();
            /**
             * @brief Inicia el juego.
             */
            void run();
            ~Game();
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
    };
}
#endif // GAME_H
