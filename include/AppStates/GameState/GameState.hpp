#ifndef ANT_GAME_STATE_HPP
#define ANT_GAME_STATE_HPP
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <Level/Level.hpp>
#include <Config.hpp>
#include <EventQueue/EventQueue.hpp>
#include <Systems/constructorSystem/Constructions.hpp>
#include <Utils/Utility.hpp>
#include <GUI/Button/Button.hpp>

namespace ant{
    /**
     * @brief Estado de juego, Inicia el juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class GameState : public AppState,public Observer{
        public:
            /**
             * @brief Constructor principal
             * @param stack StateStack stack para pedir otros estados etc.
             * @param context Context contexto de la applicacion.
             */
            GameState(StateStack& stack, Context context);
            /**
             * @brief Renderiza el juego.
             */
            virtual void render();
            /**
             * @brief Actualiza el juego.
             * @param dt sf::Time delta time
             */
            virtual bool update(sf::Time dt);
            /**
             * @brief Maneja el input del juego.
             * @param event sf::Event & eventos de teclado/Raton etc
             */
            virtual bool handleEvent(const sf::Event& event);
            /**
             * @brief Recibe los eventos.
             * -# LEVEL_COMPLETE cambia de nivel.
             * -# LEVEL_FAILED vuelve al menu.
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            virtual ~GameState();
        private:
            /**
             * @brief Carga la configuracion de este estado.
             */
            void loadConfig(const std::string& filename);
            /**
             * @brief Carga la interfaz grafica.
             * @param filename std::string
             */
             void loadGUIConf(const std::string& filename);
        private:
            sf::RenderWindow& win;
            std::shared_ptr<AssetManager> assets;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<Level> level;
            std::shared_ptr<EventQueue> eventQueue;
            std::vector<std::unique_ptr<GUI::Button>> buttons;
            int currentLevel;
            int totalLevels;
            float GameSpeed;
            std::string font;
    };
}
#endif // ANT_GAME_STATE_HPP
