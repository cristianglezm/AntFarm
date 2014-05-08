#ifndef WORLD_FACTORY_H
#define WORLD_FACTORY_H
#include <World/World.hpp>
#include <Config.hpp>
#include <EventQueue/EventQueue.hpp>
#include <GameEventDispatcher/GameEventDispatcher.hpp>
#include <EntityFactory/EntityFactory.hpp>
#include <SystemFactory/SystemFactory.hpp>
namespace ant{
    /**
     * @brief Clase para crear mundos.
     *
     * Utilizara el GameEventDispatcher, EventQueue que tenga para los mundos generados.
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class WorldFactory{
        public:
            /**
             * @brief Constructor por defecto.
             */
            WorldFactory();
            /**
             * @brief Constructor con GameEventDispatcher y EventQueue.
             * @param ged std::shared_ptr<GameEventDispatcher>
             * @param eq std::shared_ptr<EventQueue>
             */
            WorldFactory(std::shared_ptr<GameEventDispatcher> ged,std::shared_ptr<EventQueue> eq);
            /**
             * @brief Carga los assets necesarios para crear los mundos.
             * @param json const std::string & fichero json con los datos de configuracion.
             * @return bool
             */
            bool loadAssets(const std::string& json);
            /**
             * @brief Descarga los assets que tenga.
             * @return bool
             */
            bool unloadAssets();
            /**
             * @brief Establece el AssetManager que usara.
             * @param assets std::shared_ptr<AssetManager>
             */
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Obtiene el AssetManager que usa.
             * @return std::shared_ptr<AssetManager>
             */
            inline std::shared_ptr<AssetManager> getAssetManager(){ return entityFactory->getAssetManager(); }
            /**
             * @brief Crea un nivel segun la imagen especificada.
             *
             * La imagen especificada tiene que tener algo asi:
             * @todo Descripcion etc.
             * @param name std::string nombre del nivel.
             * @param lvl sf::Image imagen a cargar con la informacion del nivel.
             * @param nEntities int numero de entidades que tendra el nivel.
             * @param overTime sf::Time tiempo maximo para pasarse el nivel.
             * @param bounds sf::FloatRect rectangulo con los limites del
             *        mundo(Tienen que ser iguales a la imagenes de fondo.)
             * @return std::unique_ptr<World> World creado
             */
            std::unique_ptr<World> create(const std::string& name,const std::string& background,const sf::Image& lvl,int nEntities,sf::Time overTime,sf::FloatRect bounds);
            /**
             * @brief Establece el EntityFactory que usara.
             * @param ef std::shared_ptr<EntityFactory>
             */
            void setEntityFactory(std::shared_ptr<EntityFactory> ef);
            /**
             * @brief Obtiene el EntityFactory que usa.
             * @return std::shared_ptr<EntityFactory>
             */
            inline std::shared_ptr<EntityFactory> getEntityFactory(){ return this->entityFactory; }
            /**
             * @brief Establece la EventQueue que usaran los sistemas.
             * @param eq std::shared_ptr<EventQueue>
             */
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             * @brief Obtiene la EventQueue que usa.
             * @return std::shared_ptr<EventQueue>
             */
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            /**
             * @brief Establece el GameEventDispatcher que usara.
             * @param ged std::shared_ptr<GameEventDispatcher>
             */
            void setGameEventDispatcher(std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Obtiene el GameEventDispatcher que usa.
             * @return std::shared_ptr<GameEventDispatcher>
             */
            inline std::shared_ptr<GameEventDispatcher> getGameEventDispatcher(){ return this->gameEventDispatcher; }
            ~WorldFactory();
        private:
            std::shared_ptr<EntityFactory> entityFactory;
            std::shared_ptr<SystemFactory> systemFactory;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            int lvlID;
    };
}
#endif // WORLD_FACTORY_H
