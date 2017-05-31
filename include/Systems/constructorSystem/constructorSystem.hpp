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

#ifndef CONSTRUCTOR_SYSTEM_H
#define CONSTRUCTOR_SYSTEM_H
#include <functional>
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Components/ComponentMask.hpp>
#include <Components/ComponentsAlias.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Event/EventType.hpp>
#include <Entity/States.hpp>

namespace ant{
    /**
     * @brief Sistema encargado de que las hormigas construyan etc.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class constructorSystem final : public System, public Observer{
        public:
            /**
             * @brief Comandos que recibe por eventos.
             * @code
             *  Event<command>(EventType::CHANGE_COMMAND,[](Entity* e,sf::VertexArray* map, sf::FloatRect mapBounds){
                               // do something
                               });
             * @endcode
             */
            using command = std::function<void(Entity*,sf::VertexArray*, sf::FloatRect)>;
            /**
             * @brief Constructor por defecto.
             * @param map sf::VertexArray * Destructable para construir, etc.
             * @param boundsMap sf::FloatRect bordes del destructable.
             */
            constructorSystem(sf::VertexArray* map,sf::FloatRect boundsMap);
            /**
             * @brief recibe dos eventos
             *
             * # Eventos:
             *    -# EventType::CHANGE_COMMAND Comando que cambiara la construccion que haran las entidades.
             *    -# EventType::SELECT_ENTITY Seleccionara una entidad para aplicarle el comando actual.
             * @param e std::shared_ptr<baseEvent> evento
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e) override;
            /**
             * @brief No hace nada.
             */
            virtual void render(sf::RenderWindow& win) override;
            /**
             * @brief Gestiona la construccion de los elementos.
             * @param dt sf::Time delta time
             */
            virtual void update(const sf::Time& dt) override;
            ~constructorSystem() = default;
        private:
            sf::FloatRect boundsMap;
            sf::VertexArray* map;
            command build;
            bool readyToBuild;
    };
 }

#endif // CONSTRUCTOR_SYSTEM_H
