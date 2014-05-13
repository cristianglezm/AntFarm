#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <States/States.hpp>
#include <Config.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de crear las entidades sobre el tiempo establecido.
     *
     * Crea las entidades en la posicion de las entidades con ComponentsMask::COMPONENT_IN.
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class spawnSystem : public System, public Observer{
        public:
            /**
             * @brief constructor por defecto.
             * @param nEntities int numero de entidades a crear.
             * @param ot sf::Time cantidad para la cual usara para crear las entidades.
             * @param ef EntityFactory * Para crear las entidades.
             * @param spawnPoint sf::Vector2f sitio donde saldran las entidades.
             * @param long int states initial states when entities are created.
             */
            spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state);
            /**
             * @brief
             * @param
             */
            void setStates(long int state);
            /**
             * @brief
             * @return
             */
            inline const long int getStates() const { return states; }
            /**
             * @brief Cada x segundos crea un entidad en el sitio establecido.
             * @param dt sf::Time delta time
             */
            void update(sf::Time dt);
            /**
             * @brief no hace nada.
             */
            void render(sf::RenderWindow& win);
            /**
             * @brief Recibe eventos para cambiar el tiempo
             * o el numero de entidades que tiene que crear.
             *
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            ~spawnSystem();
        private:
            EntityFactory* entityFactory;
            int nEntities;
            int createdEntities;
            sf::Time overTime;
            sf::Time elapsedTime;
            sf::Vector2f spawnPoint;
            sf::Clock clock;
            long int states;
    };
}
#endif // SPAWN_SYSTEM_H
