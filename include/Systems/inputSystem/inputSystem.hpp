#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include <Systems/System.hpp>

namespace ant{
    /**
     * @class inputSystem
     * @brief Sistema encargado de efectuar los inputs.
     *
     * Se encarga de recibir los metodos de seleccion de hormigas para efectuar las ordenes a esas hormigas
     * las que esten seleccionadas se les aplicara los inputs para hacerlos.
     * - Ordenes | inputs
     *      -# Buscar comida
     *      -# Atacar
     *      -# huir
     *      -# etc
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class inputSystem : public System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            inputSystem();
            /**
             * @brief no hace nada.
             */
            virtual void render(sf::RenderWindow& win);
            /**
             * @brief metodo encargado de efectuar las acciones sobre las entidades.
             */
            virtual void update(sf::Time dt);
            ~inputSystem();
    };
}

#endif // INPUT_SYSTEM_H
