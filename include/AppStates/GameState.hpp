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

#ifndef ANT_GAME_STATE_HPP
#define ANT_GAME_STATE_HPP

#include <AppStates/AppState.hpp>
#include <AppStates/AppStates.hpp>
#include <Level.hpp>
#include <Config.hpp>
#include <EventQueue.hpp>
#include <Systems/constructorSystem/Constructions.hpp>
#include <Utils/Utility.hpp>
#include <GUI/Button.hpp>
#include <utility>

namespace ant{
    /**
     * @brief Estado de juego, Inicia el juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class GameState final: public AppState,public Observer{
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
            ~GameState() = default;
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
            sf::Text textScore;
            int score;
            std::string font;
    };
}
#endif // ANT_GAME_STATE_HPP
