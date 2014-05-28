#ifndef CONSTRUCTIONS_H
#define CONSTRUCTIONS_H
#include <Systems/constructorSystem/constructorSystem.hpp>
#include <Config.hpp>
#include <Utils/Math.hpp>
namespace ant{
    /**
     * @brief Clase estatica con los comandos para las hormigas.
     * @author Cristian Glez <cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Constructions{
        public:
            // commands
            /**
             * @brief Construye un tunnel.
             */
            static constructorSystem::command tunnel;
            /**
             * @brief Construye un puente.
             */
            static constructorSystem::command bridge;
            /**
             * @brief Construye un muro para escalar o bloquar el paso.
             */
            static constructorSystem::command wall;
            /**
             * @brief Construye unas escaleras.
             */
            static constructorSystem::command stairs;
            /**
             * @brief Crea un agujero en el suelo
             */
            static constructorSystem::command hole;
            /**
             * @brief la Hormiga empieza a escalar.
             */
            static constructorSystem::command climb;
            /**
             * @brief para la construccion / accion que este haciendo.
             */
            static constructorSystem::command stop;
            /**
             * @brief Crea un tunel para abajo.
             */
            static constructorSystem::command downhill;
            /**
             * @brief Crea un tunel para arriba.
             */
            static constructorSystem::command uphill;
            /**
             * @brief Crea una explosion.
             */
            static constructorSystem::command explosion;
            // colors
            static sf::Color Grey;
            static sf::Color lightGrey;
            static sf::Color Brown;
            static sf::Color lightBrown;
    };
}
#endif // CONSTRUCTIONS_H
