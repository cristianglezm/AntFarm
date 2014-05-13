#ifndef GAME_H
#define GAME_H
#include <Level/Level.hpp>
#include <Config.hpp>
#include <EventQueue/EventQueue.hpp>
#include <Systems/constructorSystem/Constructions.hpp>
#include <Utils/Utility.hpp>
#include <GUI/Button/Button.hpp>

namespace ant{
    /**
     * @brief Clase Principal del juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Game : public Observer{
        public:
            /**
             * @brief Constructor por defecto.
             */
            Game();
            /**
             * @brief Inicia el juego.
             */
            void run();
            /**
             * @brief Recibe el Evento de Level_COMPLETE y cambia el nivel.
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            /**
             * @brief Carga la interfaz grafica.
             * @param filename std::string
             */
             void loadGUIConf(const std::string& filename);
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
            std::vector<std::unique_ptr<GUI::Button>> buttons;
            sf::RenderWindow win;
            bool running;
            int currentLevel;
            int totalLevels;
            bool isPause;
            // fps
            sf::Clock clock;
            sf::Time elapsedTime;
            sf::Time lastFrame;
            sf::Text fps;
            sf::Text version;
            int GameSpeed;
            std::shared_ptr<Game> self;
    };
}
#endif // GAME_H
