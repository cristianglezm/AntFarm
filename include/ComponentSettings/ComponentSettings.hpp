////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

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
            int count;
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
             ~ComponentSettings() = default;
        private:
            float Speed;
    };
}
#endif // COMPONENT_SETTINGS_H
