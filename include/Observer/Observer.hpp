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

#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>
#include <Event/Event.hpp>
namespace ant{
    /**
     * @brief Interfaz para los observadores.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Observer{
        public:
            /**
             * @brief Constructor principal.
             */
            Observer(){};
            /**
             * @brief Metodo para notificar al observador del evento.
             * @param e std::shared_ptr<baseEvent> evento.
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e) = 0;
            virtual ~Observer() = default;
    };
}
#endif // OBSERVER_H
