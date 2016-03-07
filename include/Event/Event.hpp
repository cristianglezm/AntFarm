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

#ifndef EVENT_H
#define EVENT_H

#include <tuple>
#include <memory>

namespace ant{
    //  Forward declaration
    template<typename...T>
    class Event;
    namespace priv{
        // helper
        template<class T>
        struct EventHelper;
        // specialized template
        template<class... Args>
        struct EventHelper<ant::Event<Args...>>{
           using tuple_type = std::tuple<Args...>;
        };
    }
    /** @brief Clase Base de eventos
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class baseEvent{
        protected:
            /**
             * @brief Constructor protegido del evento base.
             * @param type int Tipo de evento.
             */
            baseEvent(int type):type(type){}
        public:
            virtual ~baseEvent() = default;
            /**
             * @brief Setter para poner el tipo al evento.
             * @param type int tipo de evento.
             */
            void setType(int type){ this->type=type;}
            /**
             * @brief Getter del tipo de evento.
             * @return int tipo del evento.
             */
            inline int getType() const{ return type; }
            /**
             * @brief Getter de los atributos del evento.
             * @code baseEvent::getAttributes<float,int>(); @endcode
             * @tparam ...T tipo de datos que tiene el evento en el orden adecuado.
             * @return std::tuple<T...> & los attributos del evento(solo lectura)
             */
            template<typename T>
            const typename priv::EventHelper<T>::tuple_type& getAttributes() const;
            /**
             * @brief Setter de los atributos del evento.
             * @code baseEvent::setAttributes<float,int>(5.3,5); @endcode
             * @tparam ...T tipo de datos que tiene el evento en el orden adecuado.
             * @param attributes ...T los parametros de los atributos.
             */
            template<typename T>
            void setAttributes(const typename priv::EventHelper<T>::tuple_type& attributes);
        private:
            int type;
    };
    /**
     * @brief Clase Especializada de evento.
     * @tparam ...T tipo de datos que tendra el evento.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    template<typename...T>
    class Event: public baseEvent{
        public:
            /**
             * @brief Constructor del Evento Especializado.
             *
             * @param type int Tipo del evento.
             * @param data T... attributos del evento.
             */
            Event(int type,T...data)
            : baseEvent{type}
            , attributes{std::move(data)...}{}
            /**
             * @brief Getter de los attributos del evento.
             *
             * Los datos del evento no se pueden modificar, son solo lectura.
             *
             * @return std::tuple<T...>& const reference a la tupla.
             */
            inline const std::tuple<T...>& getAttributes() const { return attributes; }
            /**
             * @brief Setter de los attributos del evento.
             *
             * @param attributes std::tuple<T...> attributos del evento.
             */
            void setAttributes(std::tuple<T...> attributes){ this->attributes = std::move(attributes); }
            ~Event() = default;
        private:
            std::tuple<T...> attributes;
    };

    template<typename T>
    void baseEvent::setAttributes(const typename priv::EventHelper<T>::tuple_type& attributes){
        auto& casted = static_cast<T&>(*this);
        casted.setAttributes(attributes);
    }
    template<typename T>
    const typename priv::EventHelper<T>::tuple_type& baseEvent::getAttributes() const {
        auto& casted = static_cast<const T&>(*this);
        return casted.getAttributes();
    }

}
#endif // EVENT_H
