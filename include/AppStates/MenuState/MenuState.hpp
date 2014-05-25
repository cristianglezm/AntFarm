#ifndef ANT_MENUSTATE_HPP
#define ANT_MENUSTATE_HPP
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <Utils/Utility.hpp>
#include <Config.hpp>
#include <SFML/Graphics/Text.hpp>
namespace ant{
    /**
     * @brief Clase de estado del menu
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class MenuState : public AppState{
        public:
            /**
             * @brief Constructor principal.
             * @param stack StateStack stack para cambiar el estado internamente.
             * @param context Context contexto del estado.
             */
            MenuState(StateStack& stack, Context context);
            /**
             * @brief Renderiza el estado.
             */
            virtual void render();
            /**
             * @brief Actualiza el estado.
             * @param dt sf::Time
             */
            virtual bool update(sf::Time dt);
            /**
             * @brief Maneja la input
             * @param event sf::Event
             */
            virtual bool handleEvent(const sf::Event& event);
        private:
            /**
             * @brief Carga la configuracion de este estado.
             * @param filename std::string & fichero a cargar.
             */
            void loadConfig(const std::string& filename);
        	void updateOptionText();
        private:
            enum OptionNames{
                Play,
                Exit,
            };
        private:
            sf::Sprite mBackground;
            std::string strBackground;
            std::string font;
            std::vector<sf::Text> mOptions;
            std::size_t	mOptionIndex;
    };
}
#endif // ANT_MENUSTATE_HPP
