#ifndef ANT_PAUSE_STATE_HPP
#define ANT_PAUSE_STATE_HPP
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <Utils/Utility.hpp>
#include <Config.hpp>
namespace ant{
    /**
     * @brief Estado de pausa.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class PauseState : public AppState{
        public:
            /**
             * @brief Constructor por defecto.
             */
            PauseState(StateStack& stack, Context context);
            /**
             * @brief Renderiza el estado.
             */
            virtual void render();
            /**
             * @brief Actualiza
             * @param dt sf::Time delta time
             */
            virtual bool update(sf::Time dt);
            /**
             * @brief Maneja el input del teclado/raton
             * @param event sf::Event evento.
             */
            virtual bool handleEvent(const sf::Event& event);
        private:
            /**
             * @brief Carga la configuracion de este estado.
             */
            void loadConfig(const std::string& filename);
        private:
            sf::Text mText;
            std::string font;
            bool mShowText;
            sf::Time mTextEffectTime;
    };
}
#endif // ANT_PAUSE_STATE_HPP
