#ifndef ANT_MENUSTATE_HPP
#define ANT_MENUSTATE_HPP
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <Utils/Utility.hpp>
#include <Config.hpp>
#include <SFML/Graphics/Text.hpp>
namespace ant{
    class MenuState : public AppState{
        public:
            MenuState(StateStack& stack, Context context);
            virtual void render();
            virtual bool update(sf::Time dt);
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
