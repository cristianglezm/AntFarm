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

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <algorithm>
#include <memory>
#include <Observer.hpp>

namespace ant{
    /**
     * @brief Tema al cual se suscriben los observadores Observer.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Subject final{
        public:
            /**
             * @brief Añade un observador.
             * @param o Observer*
             */
            void addObserver(Observer* o);
            /**
             * @brief Elimina el primer observador que coincida.
             * @param o Observer* observador a eliminar.
             */
            void removeObserver(Observer* o);
            /**
             * @brief Notifica a los Observadores que esten en suscritos a este tema.
             * @param e std::shared_ptr<baseEvent> evento que se envia.
             */
            void notifyObservers(std::shared_ptr<baseEvent> e);
        private:
            std::vector<Observer*> Observers;
    };
}
#endif // SUBJECT_H
