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
