#ifndef LEVEL_H
#define LEVEL_H
#include <memory>
#include <SFML/System/Time.hpp>
#include <Utils/String.hpp>
#include <JsonBox.h>
#include <WorldManager/WorldManager.hpp>
#include <WorldFactory/WorldFactory.hpp>
#include <EventQueue/EventQueue.hpp>
#include <EntityFactory/EntityFactory.hpp>

namespace ant{
    /**
     * @brief Clase que tiene el nivel del juego
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Level{
        public:
            /**
             * @brief Constructor principal
             *
             * @param assetsFilename std::string fichero json a cargar.
             *        formato: AssetManager::loadAssets()
             * @param bounds sf::FloatRect rectangulo con los limites del nivel.
             * @param ged std::shared_ptr<GameEventDispatcher> para que se suscriban a los eventos.
             */
            Level(const std::string& assetsFilename,sf::FloatRect bounds,std::shared_ptr<GameEventDispatcher> ged);
            /**
             * @brief Inicializa el nivel.
             *
             * Añade los mundos iniciales al nivel.
             * @param bounds sf::FloatRect rectangulo con los limites del nivel.
             */
            void init(const sf::FloatRect& bounds);
            /**
             * @brief Carga el nivel de un fichero json.
             * @return bool
             */
            bool loadLevel(const sf::FloatRect& bounds,const std::string& filename);
            /**
             * @brief Setter para la cola de eventos.
             * @param eq std::shared_ptr<EventQueue> Cola para que los sistemas añadan los eventos que sucenden en el juego.
             */
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            /**
             * @brief Getter para la cola de eventos
             * @return std::shared_ptr<EventQueue> Devuelve la cola de eventos.
             */
            inline std::shared_ptr<EventQueue> getEventQueue(){ return this->eventQueue; }
            /**
             * @brief Setter para la fabrica de mundos.
             * @param wf std::shared_ptr<WorldFactory>
             */
            void setWorldFactory(std::shared_ptr<WorldFactory> wf);
            /**
             * @brief Getter de la fabrica de mundos.
             * @return std::shared_ptr<WorldFactory>
             */
            inline std::shared_ptr<WorldFactory> getWorldFactory(){ return worldFactory; }
            /**
             * @brief Setter para el AssetManager
             * @param assets std::shared_ptr<AssetManager>
             */
             void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Getter para el AssetManager
             * @return std::shared_ptr<AssetManager>
             */
             inline std::shared_ptr<AssetManager> getAssetManager(){ return worldFactory->getAssetManager(); }
            /**
             * @brief Actualiza el mundo especificado.
             *
             * Actualiza el mundo especificado, si se pone un -1 se actualizaran todos.
             * @param id long int Mundo a actualizar
             * @param dt sf::Time delta time.
             */
            void update(long int id,sf::Time dt);
            /**
             * @brief Renderiza el mundo especificado.
             *
             * @param id long int Mundo a actualizar
             * @param win sf::RenderWindow & ventana a la cual dibujar.
             */
            void render(long int id,sf::RenderWindow& win);
            ~Level();
        private:
            std::shared_ptr<WorldManager> levels;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<GameEventDispatcher> gameEventDispatcher;
            std::shared_ptr<WorldFactory> worldFactory;
    };
}

#endif // LEVEL_H
