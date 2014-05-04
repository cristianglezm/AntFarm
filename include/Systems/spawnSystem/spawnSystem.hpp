#ifndef SPAWN_SYSTEM_H
#define SPAWN_SYSTEM_H
#include <Systems/System.hpp>
#include <EntityFactory/EntityFactory.hpp>
namespace ant{
    /**
     * @brief Sistema encargado de crear las entidades sobre el tiempo.
     */
    class spawnSystem : public System{
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
             *
             */
            ~spawnSystem();
        private:
            EntityFactory* entityFactory;
            int nEntities;
            sf::Time overTime;
    };
}
#endif // SPAWN_SYSTEM_H
