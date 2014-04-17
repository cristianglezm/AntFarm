#ifndef COMPONENT_H
#define COMPONENT_H
#include <tuple>
#include <memory>

namespace ant{
    /**
     * @brief Clase base de componente.
     *
     * @author Cristian Gonzalez Moreno <cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class baseComponent{
        protected:
            /**
             * @brief Contructor para la clase derivada.
             *
             * TODO posible cambio en el id de long int a bitset<NBits>
             *
             * @param id long int id del componente.
             */
            baseComponent(long int id):id(id){}
        public:
            virtual ~baseComponent() = default;
            /**
             * @brief Setter para el id.
             * @param id long int id para el componente.
             */
            void setId(long int id){ this->id=id;}
            /**
             * @brief Getter para el id.
             * @return long int id del componente.
             */
            inline const long int& getId() const{ return id; }
            /**
             * @brief Getter de las propiedades del componente,
             *
             * Es necesario especificar los datos que tiene
             * el componente en el orden adecuado.
             *
             * @param ...T Tipo de datos, ej: getProperties<float,int,std::string>();
             * @return std::tuple<T...> la tupla con los datos.
             */
            template<typename...T>
            std::tuple<T...>& getProperties();
            /**
             * @brief Setter de las propiedades del componente.
             *
             * @param ...T tipo de datos, ej: setProperties<float,int,int>(std::tuple<float,int,int>(2.4,5,6));
             */
            template<typename...T>
            void setProperties(std::tuple<T...> properties);
        private:
            long int id;
    };
    /**
     * @brief Clase especializada de baseComponent.
     *
     * Puede tener todas las propiedades que se definan
     * despues se tendran que acceder por el orden correcto.
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    template<typename...T>
    class Component: public baseComponent{
        public:
            /**
             * @brief Constructor del componente especializado.
             *
             * @param id long int id del componente.
             * @param data T... propiedades del componente.
             */
            Component(long int id,T...data)
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
             * @param std::tuple<T...> tipo de datos, ej: setProperties(std::tuple<float,int,int>(2.4,5,6));
             */
             void setProperties(std::tuple<T...> properties){ this->properties = std::move(properties); }
        private:
            std::tuple<T...> properties;
    };

    template <typename...T>
    void baseComponent::setProperties(std::tuple<T...> properties){
        auto& casted = dynamic_cast<Component<T...>&>(*this);
        casted.setProperties(properties);
    }

    template<typename...T>
    std::tuple<T...>& baseComponent::getProperties(){
        auto& casted = dynamic_cast<Component<T...>&>(*this);
        return casted.getProperties();
    }
}
#endif // COMPONENT_H
