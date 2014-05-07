#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H
#include <Systems/System.hpp>
#include <Observer/Observer.hpp>
#include <EntityFactory/EntityFactory.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de crear las entidades sobre el tiempo.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class spawnSystem : public System, Observer{
        public:
            /**
             * @brief Constructor por defecto.
             */
            spawnSystem();
            /**
             * @brief Overload de constructor con parametros.
             * @param nEntities int numero de entidades a crear.
             * @param ot sf::Time El tiempo en el que tiene que crear esas entidades.
             * @param ef EntityFactory * Para crear las entidades.
             */
            spawnSystem(int nEntities, EntityFactory* ef,sf::Time ot);
            /**
             *
             */
            void update(sf::Time dt);
            /**
             *
             */
            void render(sf::RenderWindow& win);
            /**
             * @brief Recibe eventos para cambiar el tiempo
             * o el numero de entidades que tiene que crear.
             */
            void onNotify(std::shared_ptr<baseEvent> e);
            ~spawnSystem();
        private:
            EntityFactory* entityFactory;
            int nEntities;
            sf::Time overTime;
    };
}
#endif // SPAWN_SYSTEM_H
