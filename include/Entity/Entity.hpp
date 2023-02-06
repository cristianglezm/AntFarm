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

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <Components/Component.hpp>
#include <Entity/States.hpp>

namespace ant{
    /**
     * @class Entity
     * @brief Clase para tener los componentes, solo puede tener un componente de cada tipo.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Entity final{
        public:
            /**
             * Contenedor que utiliza la entidad para los componentes.
             */
            typedef std::unordered_map<ComponentsMask::Mask,std::unique_ptr<baseComponent>> map;
            /**
             * @brief Constructor por defecto.
             */
            Entity();
            /**
             * @brief Constructor con nombre.
             * @param name std::string nombre que tendra la entidad.
             */
            Entity(const std::string& name);
            /**
             * @brief Constructor con nombre y componentes.
             * @param name std::string nombre que tendra la entidad.
             * @param Components Entity::map mapa de los componentes.
             */
            Entity(const std::string& name,map&& Components);
            /**
             * @brief Añade un componente a la entidad.
             *
             * @param component std::unique_ptr<baseComponent> componente para añadir.
             */
            void addComponent(std::unique_ptr<baseComponent> component);
            /**
             * @brief Obtiene una referencia al componente.
             *
             * Si el componente no se encuentra devuelve un nullptr.
             *
             * @param id ComponentsMask::Mask id del componente.
             * @return baseComponent * puntero al componente.
             */
            inline baseComponent* getComponent(const ComponentsMask::Mask& id) noexcept{
                if(hasComponent(id)){
                    return Components[id].get();
                }
                return nullptr;
            }
            /**
             * @brief Elimina el componente de la entidad.
             * @param id ComponentsMask::Mask
             */
            void removeComponent(const ComponentsMask::Mask& id);
            /**
             * @brief Getter del nombre de la entidad.
             * @return std::string nombre de la entidad.
             */
            inline std::string getName() const { return name; }
            /**
             * @brief Setter del nombre de la entidad.
             * @param name std::string nombre nuevo de la entidad.
             */
            void setName(std::string name);
            /**
             * @brief Setter de los componentes de la entidad.
             * @param Components Entity::map
             */
            void setComponents(map&& Components);
            /**
             * @brief Getter de los componentes.
             * @return Entity::map referencia a los componentes.
             */
            inline map& getComponents() noexcept{ return Components; }
            /**
             * @brief Getter de la mascara de la entidad.
             *
             * Con este metodo comprobaras si una entidad tiene los componentes
             * que necesitas antes de utilizar el getComponent(Component::ID);
             * @code if((e.getMask() & Component:ID) == Component::ID) @endcode
             *
             * @return ComponentsMask::Mask
             */
            inline const ComponentsMask::Mask& getMask() const noexcept{ return mask; }
            /**
             * @brief Devuelve si esta entidad tiene el componente.
             * @param id ComponentsMask::Mask Id del componente.
             * @return bool
             */
            inline bool hasComponent(const ComponentsMask::Mask& id) const noexcept{ return ((mask & id) == id); }
            /**
             * @brief Comprueba si la entidad tiene el estado especificado.
             * @param statesID ComponentsMask::Mask id de los estados.
             * @code
             *  e->is(States::FALLING | States::OnFIRE);
             * @endcode
             * @return bool
             */
            inline bool is(const States::Mask& statesID) const noexcept{ return ((states & statesID) == statesID ); }
            /**
             * @brief Añade un estado a la entidad.
             * @param state ComponentsMask::Mask estado a añadir.
             */
            void addState(const States::Mask& state);
            /**
             * @brief Elimina un estado de la entidad.
             * @param state ComponentsMask::Mask estado a eliminar.
             */
            void removeState(const States::Mask& state);
            /**
             * @brief devuelve los estados de la entidad.
             * @return ComponentsMask::Mask Estados de la entidad.
             */
             inline const States::Mask& getStates() const noexcept{ return states; }
             /**
              * @brief Limpia los componentes de la entidad
              */
             void clear();
            /**
             * @brief Operator overload para comparar la entidad contra otra entidad.
             * @param e Entity entidad a la cual compararse.
             * @return bool
             */
            bool operator==(const Entity& e) const noexcept;
            /**
             * @brief Operator overload para comparar la entidad contra otra entidad
             * @param e Entity entidad a la cual se compara.
             * @return bool
             */
            bool operator!=(const Entity& e) const noexcept;
            /**
             * @brief Operator overload para comparar la entidad por nombre.
             * @param name std::string nombre con el cual comparar.
             * @return bool
             */
            bool operator==(const std::string& name) const noexcept;
            ~Entity() = default;
        private:
            std::string name;
            ComponentsMask::Mask mask;
            ComponentsMask::Mask states;
            map Components;
    };
}
#endif // ENTITY_HPP
