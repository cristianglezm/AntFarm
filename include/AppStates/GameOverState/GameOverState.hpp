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

#ifndef ANT_GAMEOVER_STATE_HPP
#define ANT_GAMEOVER_STATE_HPP
#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Config.hpp>
namespace ant{
    /**
     * @brief Muestra el mensaje de final de juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1a
     */
    class GameOverState : public AppState{
        public:
            /**
             * @brief Constructor principal.
             * @param stack StateStack stack para cambiar estados internamente.
             * @param context Context contexto de la aplicacion.
             * @param msg std::string mensaje que mostrara.
             */
            GameOverState(StateStack& stack, Context context,std::string msg);
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
             * @brief Maneja la input.
             * @param event sf::Event
             */
            virtual bool handleEvent(const sf::Event& event);
        private:
            /**
             * @brief Carga la configuracion de este estado.
             * @param filename std::string fichero a cargar.
             */
            void loadConfig(const std::string& filename);
        private:
            sf::Text mText;
            std::string font;
    };
}

#endif // ANT_GAMEOVER_STATE_HPP
