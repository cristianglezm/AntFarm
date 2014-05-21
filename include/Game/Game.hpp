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
             /**
              * @brief Carga la configuracion del tipo de fuente.
              * @param filename std::string
              */
             void loadConfig(const std::string& filename);
            ~Game();
        private:
            /**
             * @brief Obtiene los fps.
             * @param time sf::Time
             * @return float
             */
            float getFPS(const sf::Time& time);
        private:
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<Level> level;
            std::shared_ptr<AssetManager> assets;
            std::vector<std::unique_ptr<GUI::Button>> buttons;
            sf::RenderWindow win;
            bool running;
            int currentLevel;
            int totalLevels;
            sf::Text version;
            int GameSpeed;
            bool isPause;
            bool gameCompleted;
            bool gameFailed;
            std::string font;
            // fps
            sf::Clock clock;
            sf::Time elapsedTime;
            sf::Time timePoint1;
            sf::Time timePoint2;
            sf::Time lastFrame;
            sf::Text fps;
            std::shared_ptr<Game> self;
    };
}
#endif // GAME_H
