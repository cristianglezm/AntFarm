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

#ifndef GAME_EVENT_DISPATCHER_H
#define GAME_EVENT_DISPATCHER_H

#include <Event/Event.hpp>
#include <Event/EventType.hpp>
#include <Subject/Subject.hpp>

namespace ant{
    /**
     * @brief Clase encargada de processar eventos.
     *
     * Esta clase contiene a los eventos a los cuales
     * se pueden suscribir los observadores.
     *
     * @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class GameEventDispatcher{
        public:
            /**
             * @brief lista de observadores del evento onCollision.
             */
            Subject onCollision;
            /**
             * @brief Eventos para el sistema de creacion de entidades.
             */
            Subject spawnEvents;
            /**
             * @brief Eventos de click dan evento con un punto.
             */
            Subject ClickEvents;
            /**
             * @brief Envia un Comando al sistema de construccion.
             */
            Subject ChangeCommand;
            /**
             * @brief Envia una entidad que ha salido del mapa.
             */
            Subject outMap;
            /**
             * @brief El sistema de out envia este evento.
             */
            Subject LevelComplete;
            /**
             * @brief El sistema de out envia este evento.
             */
            Subject LevelFailed;
            /**
             * @brief El sistema de out envia este evento.
             */
            Subject UpdateScore;
            /**
             * @brief Procesa el evento y lo envia a los observadores que esten subscritos.
             * @param e std::shared_ptr<baseEvent>
             * @return bool
             */
            bool DispatchEvent(std::shared_ptr<baseEvent> e);
    };
}
#endif // GAME_EVENT_DISPATCHER_H
