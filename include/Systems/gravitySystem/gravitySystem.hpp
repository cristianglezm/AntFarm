#ifndef GRAVITY_SYSTEM_H
#define GRAVITY_SYSTEM_H
#include <Systems/System.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     * @brief Sistema para aplicar la gravedad a las entidades.
     *
     * Aplica por defecto 0.8
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class gravitySystem : public System{
        public:
            /**
             * @brief Constructor por defecto.
             */
            gravitySystem();
            /**
             * @brief Overload de constructor para configurar la gravedad directamente.
             * @param g float gravedad a aplicar.
             */
            gravitySystem(float g);
            /**
             * @brief Establece la gravedad que aplicara el sistema.
             * @param g float gravedad a aplicar.
             */
            void setGravity(float g);
            /**
             * @brief Obtiene la gravedad que aplica a las entidades.
             * @return float Gravedad que aplica.
             */
            inline float getGravity(){ return Gravity; }
            /**
             * @brief Metodo abstracto para actualizar entidades.
             * @param dt sf::Time delta time para los calculos.
             */
            virtual void update(sf::Time dt);
            /**
             * @brief No hace nada.
             */
            virtual void render(sf::RenderWindow& win);
            ~gravitySystem();
        private:
            float Gravity;
    };
}
#endif // GRAVITY_SYSTEM_H
