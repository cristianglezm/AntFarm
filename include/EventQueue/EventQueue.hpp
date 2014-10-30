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

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <queue>
#include <memory>
#include <Event/Event.hpp>
namespace ant{
    /** @brief Clase donde se almacenan los eventos para
     *         ser procesados despues.
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class EventQueue final{
        public:
            /**
             * @brief Añade un evento al final de la cola.
             * @param e std::shared_ptr<baseEvent> Evento a añadir.
             */
            void push(std::shared_ptr<baseEvent>&& e);
            /**
             * @brief Elimina el evento de la cola y lo devuelve.
             * @return std::shared_ptr<baseEvent>
             */
            std::shared_ptr<baseEvent> pop();
            /**
             * @brief Consulta el evento que esta al frente de la cola.
             * @return std::shared_ptr<baseEvent> & referencia al evento.
             */
            std::shared_ptr<baseEvent>& front();
            /**
             * @brief Si la cola esta vacia o no.
             * @return bool
             */
            inline bool isEmpty(){ return eventQueue.empty(); }
            /**
             * @brief Devuelve el numero de eventos en la cola.
             * @return int
             */
            inline int size(){ return eventQueue.size(); }
            /**
             * @brief limpia la cola.
             */
            void clear();
        private:
            std::queue<std::shared_ptr<baseEvent>> eventQueue;
    };
}
#endif // EVENT_QUEUE_H
