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

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <list>
#include <algorithm>
#include <memory>
#include <Entity/Entity.hpp>
namespace ant{
    /**
     * @brief Clase Para manejar las entidades.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class EntityManager{
        public:
            /**
             * @brief Contenedor utilizado por el EntityManager.
             */
            typedef std::list<std::unique_ptr<Entity>> container;
            /**
             * @brief Iterador del EntityManager
             */
            typedef container::iterator iterator;
            /**
             * @brief Constructor por defecto.
             */
            EntityManager();
            /**
             * @brief Añade una entidad al manager.
             * @param e std::unique_ptr<Entity>
             */
            void addEntity(std::unique_ptr<Entity> e);
            /**
             * @brief Elimina la primera entidad que coincida el nombre.
             *
             * @param name std::string nombre de la entidad.
             * @return iterator la posicion siguiente de la entidad eliminada.
             */
            iterator removeEntity(const std::string& name);
            /**
             * @brief Elimina la primera entidad que coincida.
             *
             * @param it iterator
             * @return iterator la posicion siguiente de la entidad eliminada.
             */
            iterator removeEntity(iterator it);
            /**
             * @brief Obtiene la primera entidad que tenga el nombre proporcionado.
             *
             * Si no encuentra la entidad devuelve un puntero nulo(nullptr).
             *
             * @param name std::string nombre de la entidad.
             * @return Entity * naked pointer hacia la entidad o nullptr si no la encuentra.
             */
            Entity* getEntity(const std::string& name);
            /**
             * @brief Añade todas las entidades a la vez.
             * @param e container lista de entidades.
             */
            void addEntities(container&& e);
            /**
             * @brief devuelve la lista de las entidades.
             * @return container &
             */
            inline container& getEntities(){ return entities; }
            /**
             * @brief Devuelve el principio de la lista.
             */
            inline iterator begin(){ return entities.begin(); }
            /**
             * @brief Devuelve el final de la lista.
             */
            inline iterator end(){ return entities.end(); }
            /**
             * @brief Transfiere la primera entidad que coincida con el nombre.
             *
             * Transfiere la posesion(ownership) de la entidad y la elimina del contenedor.
             *
             * @param name std::string nombre de la entidad a transferir.
             * @return std::unique_ptr<Entity> entidad transferida o nullptr si no es encontrada.
             */
            std::unique_ptr<Entity> Transfer(const std::string& name);
            /**
             * @brief Transfiere la primera entidad que coincida con el puntero de entidad.
             *
             * Transfiere la posesion(ownership) de la entidad y la elimina del contenedor.
             *
             * @param e Entity * Puntero a la entidad
             * @return std::unique_ptr<Entity> entidad transferida o nullptr si no es encontrada.
             */
            std::unique_ptr<Entity> Transfer(const Entity* e);
        private:
            container entities;
    };
}
#endif // ENTITY_MANAGER_H
