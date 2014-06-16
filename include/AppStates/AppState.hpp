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

#ifndef ANT_APPSTATE_HPP
#define ANT_APPSTATE_HPP
#include <AssetManager/AssetManager.hpp>
#include <AppStates/AppStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <functional>

namespace ant{
    class StateStack;
    /**
     * @brief Clase abstracta de estado de aplicacion.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class AppState{
        public:
            /**
             * @brief Puntero unico de AppState
             */
            typedef std::unique_ptr<AppState> uPtr;
            /**
             * @brief Puntero Compartido de AppState
             */
            typedef std::shared_ptr<AppState> sPtr;
            /**
             * @brief Clase para compartir datos esenciales a los estados.
             * @author Cristian Glez <Cristian.glez.m@gmail.com>
             */
            struct Context{
                /**
                 * @brief Constructor Principal.
                 */
                Context(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<AssetManager> assets);
                std::shared_ptr<sf::RenderWindow> window;
                std::shared_ptr<AssetManager> assets;
            };
        public:
            /**
             * @brief Constructor principal
             * @param stack StateStack referencia a un stack,
             * @param context AppState::Context contexto de ejecucion
             */
            AppState(StateStack& stack,AppState::Context context);
            /**
             * @brief Metodo abstracto para que los estados
             * dibujen a la pantalla.
             */
            virtual void render() = 0;
            /**
             * @brief Metodo abstracto para que los estados actualizen su estado.
             * @return bool retorna true para que los demas tambien actualicen.
             */
            virtual bool update(sf::Time dt) = 0;
            /**
             * @brief Metodo abstracto para que los estados manejen el input.
             * @return bool retorna true para que los demas tambien manejen eventos.
             */
            virtual bool handleEvent(const sf::Event& event) = 0;
            virtual ~AppState();
        protected:
            /**
             * @brief Pide al stack que añada un estado nuevo.
             * @param stateID AppStates::ID id del estado.
             */
            void requestStackPush(AppStates::ID stateID);
            /**
             * @brief Pide al stack que quite el ultimo estado añadido.
             */
            void requestStackPop();
            /**
             * @brief Pide al stack que se limpie.
             */
            void requestStateClear();
            /**
             * @brief Devuelve el contexto.
             * @return AppState::Context
             */
            Context	getContext() const;
        private:
            StateStack* mStack;
            Context	mContext;
    };
}
#include <StateStack/StateStack.hpp>
#endif // ANT_APPSTATE_HPP
