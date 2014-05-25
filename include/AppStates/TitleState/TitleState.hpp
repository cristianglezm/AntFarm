#ifndef ANT_TITLESTATE_HPP
#define ANT_TITLESTATE_HPP
#include <AppStates/AppState.hpp>
#include <string>
#include <Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
namespace ant{
    /**
     * @brief Muestra el titulo de la aplicacion
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1a
     */
    class TitleState : public AppState{
        public:
            TitleState(StateStack& stack, Context context);
            virtual void render();
            virtual bool update(sf::Time dt);
            virtual bool handleEvent(const sf::Event& event);
        private:
            /**
             * @brief Carga la configuracion de este estado.
             */
            void loadConfig(const std::string& filename);
        private:
            sf::Sprite mBackgroundSprite;
            sf::Text mText;
            std::string font;
            std::string background;
            bool mShowText;
            sf::Time mTextEffectTime;
    };
}

#endif // ANT_TITLESTATE_HPP
