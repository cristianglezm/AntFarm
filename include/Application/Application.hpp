#ifndef ANT_APPLICATION_HPP
#define ANT_APPLICATION_HPP

#include <Config.hpp>
#include <Utils/String.hpp>
#include <AssetManager/AssetManager.hpp>
#include <StateStack/StateStack.hpp>
#include <AppStates/AppState.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ant{
    /**
     * @brief Clase de aplicacion.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Application{
        public:
            /**
             * @brief Constructor Principal.
             */
            Application();
            /**
             * @brief Comienza la aplicacion
             */
            void run();
            ~Application();
        private:
            /**
             * @brief Procesa el input del teclado/raton etc.
             */
            void processInput();
            /**
             * @brief Actualiza el estado de la aplicacion.
             * @param dt sf::Time delta time
             */
            void update(sf::Time dt);
            /**
             * @brief Renderiza la aplicacion.
             */
            void render();
            /**
             * @brief Carga la configuracion
             * @param filename std::string nombre del fichero de configuracion.
             */
            void loadConfig(const std::string& filename);
            /**
             * @brief Actualiza las estadisticas del juego.
             * @param dt sf::Time
             */
            void updateStatistics(sf::Time dt);
            /**
             * @brief Registra los estados que usara la aplicacion.
             */
            void registerStates();
        private:
            static const sf::Time TimePerFrame;
            std::shared_ptr<sf::RenderWindow> mWindow;
            std::shared_ptr<AssetManager> mAssets;
            StateStack mStateStack;
            sf::Text mStatisticsText;
            sf::Time mStatisticsUpdateTime;
            std::size_t	mStatisticsNumFrames;
            sf::Text version;
            std::string font;
    };
}
#endif // ANT_APPLICATION_HPP
