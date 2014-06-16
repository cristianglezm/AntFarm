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

#ifndef ANT_CONFIG_H
#define ANT_CONFIG_H
#include <string>
#include <SFML/Graphics/Rect.hpp>
namespace ant{
    /**
     * @brief Clase de configuracion con constantes de ficheros.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class Config{
        private:
        public:
            static const std::string VERSION;
            static const std::string ASSETS_GAME_JSON;
            static const std::string ANT_FILE;
            static const std::string INDOOR_FILE;
            static const std::string OUTDOOR_FILE;
            static const std::string GUI_FILE;
            static const std::string LEVEL_FILE;
            static const std::string LEVELS_FILE;
            static const std::string CONFIG_FILE;
            static const sf::FloatRect screenSize;

    };
}
#endif // CONFIG_H
