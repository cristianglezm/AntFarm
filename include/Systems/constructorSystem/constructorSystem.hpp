#ifndef CONSTRUCTOR_SYSTEM_H
#define CONSTRUCTOR_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Components/ComponentMask.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <Event/EventType.hpp>
#include <States/States.hpp>

namespace ant{
    /**
     * @brief Sistema encargado de que las hormigas construyan etc.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class constructorSystem : public System, public Observer{
        public:
            /**
             * @brief Comandos que recibe por eventos.
             * @code
             *  Event<command>(EventType::CHANGE_COMMAND,[](Entity* e,sf::VertexArray* map, sf::FloatRect mapBounds){
                               // do something
                               });
             * @endcode
             */
             //typedef std::function<void(Entity*,sf::VertexArray*, sf::FloatRect)> command;
            typedef void(*command)(Entity*,sf::VertexArray*, sf::FloatRect);
            /**
             * @brief Constructor por defecto.
             * @param map sf::VertexArray * Destructable para construir, etc.
             * @param boundsMap sf::FloatRect bordes del destructable.
             */
            constructorSystem(sf::VertexArray* map,sf::FloatRect boundsMap);
            /**
             * @brief recibe dos eventos
             *
             * # Eventos:
             *    -# EventType::CHANGE_COMMAND Comando que cambiara la construccion que haran las entidades.
             *    -# EventType::SELECT_ENTITY Seleccionara una entidad para aplicarle el comando actual.
             * @param e std::shared_ptr<baseEvent> evento
             */
            virtual void onNotify(std::shared_ptr<baseEvent> e);
            /**
             * @brief No hace nada.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief Gestiona la construccion de los elementos.
             * @param dt sf::Time delta time
             */
            virtual void update(sf::Time dt);
            ~constructorSystem();
        private:
            sf::FloatRect boundsMap;
            sf::VertexArray* map;
            command build;
            bool readyToBuild;
    };
 }

#endif // CONSTRUCTOR_SYSTEM_H
