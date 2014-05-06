#ifndef COMPONENT_SETTINGS_H
#define COMPONENT_SETTINGS_H
#include <string>
#include <fstream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <JsonBox.h>
namespace ant{
    /**
     * @brief Clase para la configuracion de los componentes en EntityFactory.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class ComponentSettings{
        public:
            std::string entityName;
            float minSpeed;
            float maxSpeed;
            sf::Vector2f scale;
            sf::Vector2f position;
            float rotation;
            std::string spriteID;
            std::vector<std::string> animation;
            sf::Vector2f dest;
            sf::Vector2f DestructiblePosition;
            std::string imageID;
            sf::FloatRect bounds;
            /**
             *
             */
             ComponentSettings();
            /**
             * @brief Carga la configuracion de la entidad.
             *
             * Carga un fichero json con las propiedades de los componentes
             * las propiedades que no encuentre las pondra por defecto.
             *
             * @param filename std::string nombre del fichero(json) a cargar.
             */
            void loadSettings(const std::string& filename);
            /**
             * @brief Establece la Velocidad.
             * @param speed float velocidad
             */
            void setSpeed(float speed);
            inline float getSpeed(){ return Speed; }
             ~ComponentSettings();
        private:
            float Speed;
    };
}
#endif // COMPONENT_SETTINGS_H
