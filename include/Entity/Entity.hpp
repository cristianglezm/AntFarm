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
             * Si el componente no se encuentra tira excepcion,
             * se tiene que comprobar que la entidad tiene el componente,
             * se comprobaria con la mascara de la entidad.
             * ej: (e.getMask() & Component::ID) == Component::ID
             * devolveria true si tiene el componente, false si no tiene.
             *
             * @param id long int id del componente.
             * @return std::unique_ptr<baseComponent>& referencia al componente.
             */
            inline std::unique_ptr<baseComponent>& getComponent(long int id){
                 try{
                        return Components.at(id);
                    }catch(std::exception& out){
                        std::string ex = out.what();
                        throw std::runtime_error("Component not Found: Mask " + ex);
                    }
            }
            /**
             * @brief Elimina el componente de la entidad.
             * @param mask long int
             */
            void removeComponent(long int mask);
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
             * ej: if((e.getMask() & Component:ID) == Component::ID)
             *
             * @return long int
             */
            inline long int getMask() const { return mask; }
            /**
             * @brief Operator overload para comparar la entidad contra otra entidad.
             * @param e Entity entidad a la cual compararse.
             * @return bool
             */
            bool operator==(const Entity& e) const;
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
            map Components;
    };
}
#endif // ENTITY_H
