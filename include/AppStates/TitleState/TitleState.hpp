////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

#ifndef ANT_TITLESTATE_HPP
#define ANT_TITLESTATE_HPP

#include <string>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <AppStates/AppState.hpp>
#include <Config.hpp>

namespace ant{
    /**
     * @brief Muestra el titulo de la aplicacion
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1a
     */
    class TitleState : public AppState{
        public:
            /**
             * @brief Constructor por defecto.
             */
            TitleState(StateStack& stack, Context context);
            /**
             * @brief Renderiza el estado en pantalla.
             */
            virtual void render();
            /**
             * @brief Actualiza
             */
            virtual bool update(sf::Time dt);
            /**
             * @brief Maneja el input de teclado/raton.
             */
            virtual bool handleEvent(const sf::Event& event);
        private:
            /**
             * @brief Carga la configuracion de este estado.
             */
            void loadConfig(const std::string& filename);
        private:
            sf::Sprite mBackground;
            sf::Text mTitle;
            sf::Text mText;
            std::string font;
            std::string background;
            bool mShowText;
            sf::Time mTextEffectTime;
    };
}

#endif // ANT_TITLESTATE_HPP
