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

#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <stdexcept>
#include <memory>
#include <map>
#include <Components/Component.hpp>
#include <iostream>
namespace ant{
    /**
     * @class Entity
     * @brief Clase para tener los componentes, solo puede tener un componente de cada tipo.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Entity{
        public:
            /**
             * Contenedor que utiliza la entidad para los componentes.
             */
            typedef std::map<long int,std::unique_ptr<baseComponent>> map;
            /**
             * @brief Constructor por defecto.
             */
            Entity();
            /**
             * @brief Constructor con nombre.
             * @param name std::string nombre que tendra la entidad.
             */
            Entity(std::string name);
            /**
             * @brief Constructor con nombre y componentes.
             * @param name std::string nombre que tendra la entidad.
             * @param Components Entity::map mapa de los componentes.
             */
            Entity(std::string name,map Components);
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
             * @param id long int id del componente.
             * @return baseComponent * puntero al componente.
             */
            inline baseComponent* getComponent(long int id){
                if(hasComponent(id)){
                    return Components.at(id).get();
                }else{
                    return nullptr;
                }
            }
            /**
             * @brief Elimina el componente de la entidad.
             * @param id long int
             */
            void removeComponent(long int id);
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
            void setComponents(map Components);
            /**
             * @brief Getter de los componentes.
             * @return Entity::map referencia a los componentes.
             */
            inline map& getComponents(){ return Components; }
            /**
             * @brief Getter de la mascara de la entidad.
             *
             * Con este metodo comprobaras si una entidad tiene los componentes
             * que necesitas antes de utilizar el getComponent(Component::ID);
             * @code if((e.getMask() & Component:ID) == Component::ID) @endcode
             *
             * @return long int
             */
            inline long int getMask() const { return mask; }
            /**
             * @brief Devuelve si esta entidad tiene el componente.
             * @param id long int Id del componente.
             * @return bool
             */
            inline bool hasComponent(long int id){ return ((mask & id) == id); }
            /**
             * @brief Comprueba si la entidad tiene el estado especificado.
             * @param statesID long int id de los estados.
             * @code
             *  e->is(States::FALLING | States::OnFIRE);
             * @endcode
             * @return bool
             */
            inline bool is(long int statesID){ return ((states & statesID) == statesID ); }
            /**
             * @brief Añade un estado a la entidad.
             * @param state long int estado a añadir.
             */
            void addState(long int state);
            /**
             * @brief Elimina un estado de la entidad.
             * @param state long int estado a eliminar.
             */
            void removeState(long int state);
            /**
             * @brief devuelve los estados de la entidad.
             * @return long int Estados de la entidad.
             */
             inline long int getStates(){ return states; }
             /**
              * @brief Limpia los componentes de la entidad
              */
             void clear();
            /**
             * @brief Operator overload para comparar la entidad contra otra entidad.
             * @param e Entity entidad a la cual compararse.
             * @return bool
             */
            bool operator==(const Entity& e) const;
            /**
             * @brief Operator overload para comparar la entidad contra otra entidad
             * @param e Entity entidad a la cual se compara.
             * @return bool
             */
            bool operator!=(const Entity& e) const;
            /**
             * @brief Operator overload para comparar la entidad por nombre.
             * @param name std::string nombre con el cual comparar.
             * @return bool
             */
            bool operator==(const std::string& name) const;
            ~Entity();
        private:
            std::string name;
            long int mask;
            long int states;
            map Components;
    };
}
#endif // ENTITY_H
