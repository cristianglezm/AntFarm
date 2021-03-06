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

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <tuple>
#include <memory>

#include <Components/ComponentMask.hpp>

namespace ant{
    //  Forward declaration
    template<typename...T>
    class Component;
    namespace priv{
        // helper
        template<class T>
        struct ComponentHelper;
        // specialized template
        template<class... Args>
        struct ComponentHelper<ant::Component<Args...>>{
           using tuple_type = std::tuple<Args...>;
        };
    }
    /**
     * @class baseComponent
     * @brief Clase base de componente.
     *
     * @author Cristian Gonzalez Moreno <cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class baseComponent{
        protected:
            /**
             * @brief Contructor para la clase derivada.
             * @param id ComponentsMask::Mask id del componente.
             */
            baseComponent(ComponentsMask::Mask id):id(id){}
        public:
            virtual ~baseComponent() = default;
            /**
             * @brief Setter para el id.
             * @param id ComponentsMask::Mask id para el componente.
             */
            void setId(ComponentsMask::Mask id){ this->id=id;}
            /**
             * @brief Getter para el id.
             * @return ComponentsMask::Mask id del componente.
             */
            inline const ComponentsMask::Mask& getId() const{ return id; }
            /**
             * @brief Getter de las propiedades del componente,
             *
             * Es necesario especificar los datos que tiene
             * el componente en el orden adecuado.
             * @tparam ...T tipo de datos que contiene el componente en su orden adecuado.
             * @code
             * getProperties<float,int,std::string>();
             * @endcode
             * @return std::tuple<T...> la tupla con los datos.
             */
            template<typename T>
            typename priv::ComponentHelper<T>::tuple_type& getProperties();
            /**
             * @brief Setter de las propiedades del componente.
             * @tparam ...T tipo de datos que contiene el componente en su orden adecuado.
             * @param properties ...T tipo de datos
             * @code
             * setProperties<float,int,int>(std::tuple<float,int,int>(2.4,5,6));
             * @endcode
             */
            template<typename T>
            void setProperties(typename priv::ComponentHelper<T>::tuple_type properties);
        private:
            ComponentsMask::Mask id;
    };
    /**
     * @class Component
     * @brief Clase especializada de baseComponent.
     *
     * Puede tener todas las propiedades que se definan
     * despues se tendran que acceder por el orden correcto.
     * @tparam ...T tipo de datos que tendra este componente.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    template<typename...T>
    class Component: public baseComponent{
        public:
            using type = std::tuple<T...>;
            /**
             * @brief Constructor del componente especializado.
             *
             * @param id ComponentsMask::Mask id del componente.
             * @param data T... propiedades del componente.
             */
            Component(ComponentsMask::Mask id,T...data)
            : baseComponent{id}
            , properties{std::move(data)...}{}
            /**
             * @brief Getter de las propiedades del componente,
             *
             * Cuando el Componente que tienes es una especializacion
             * no hace falta especificar los componentes ya que estan
             * definidos al crear el objecto.
             *
             * @return std::tuple<T...> la tupla con los datos.
             */
            inline std::tuple<T...>& getProperties(){ return properties; }
            /**
             * @brief Setter de las propiedades del componente.
             *
             * @param properties std::tuple<T...> tipo de datos
             * @code
             * Component<float,int,int> c;
             * c.setProperties(std::tuple<float,int,int>(2.4,5,6));
             * @endcode
             */
             void setProperties(std::tuple<T...> properties){ this->properties = std::move(properties); }
             ~Component() = default;
        private:
            std::tuple<T...> properties;
    };

    template<typename T>
    void baseComponent::setProperties(typename priv::ComponentHelper<T>::tuple_type properties){
        auto& casted = static_cast<T&>(*this);
        casted.setProperties(properties);
    }

    template<typename T>
    typename priv::ComponentHelper<T>::tuple_type& baseComponent::getProperties(){
        auto& casted = static_cast<T&>(*this);
        return casted.getProperties();
    }
}
#endif // COMPONENT_HPP
