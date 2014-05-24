#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <Event/EventType.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <Entity/States.hpp>
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
             * @param ot sf::Time Tiempo para crear las entidades cada X tiempo.
             * @param ef EntityFactory * Para crear las entidades.
             * @param spawnPoint sf::Vector2f sitio donde saldran las entidades.
             * @param state long int Estados iniciales para cuando las entidades son creadas.
             */
            spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot,sf::Vector2f spawnPoint,long int state);
            /**
             * @brief Establece el estado por defecto que pondra a las entidades.
             * @param state long int estados de las entidades
             * @code
             *  setStates(States::FALLING | STATES::ONFIRE);
             * @endcode
             */
            void setStates(long int state);
            /**
             * @brief Obtiene los estados que pone por defecto al crear las entidades.
             * @return long int
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
             * @param e std::shared_ptr<baseEvent>
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
