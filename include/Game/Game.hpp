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
            /**
             * @brief Obtiene los fps.
             * @param time sf::Time
             * @return float
             */
            float getFPS(const sf::Time& time);
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<Level> level;
            std::shared_ptr<AssetManager> assets;
            sf::RenderWindow win;
            bool running;
            int currentLevel;
            bool isPause;
            // fps
            sf::Clock clock;
            sf::Time elapsedTime;
            sf::Time lastFrame;
            sf::Text fps;
    };
}
#endif // GAME_H
