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

#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <stdexcept>
#include <map>
#include <memory>
#include <fstream>

#include <JsonBox.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>

#include <Utils/Utility.hpp>

namespace ant{
    /**
     * @class AssetManager
     * @brief Clase para tener todos los assets(imagenes,texturas,etc) del juego
     *
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class AssetManager{
        public:
            /**
             * @brief Constructor principal sin argumentos.
             */
            AssetManager();
            /**
             * @brief Carga un fichero json con el siguiente formato:
             * @code
             * {
             *      "textures":[ {"id":"TEXTURE_ID","filepath":"data/entities/Example.png"},
             *                 ],
             *      "images":[ {"id":"IMAGE_ID","filepath":"data/entities/Example.png"},
             *               ],
             *      "fonts":[ {"id":"FONT_ID","filepath":"data/entities/Example.ttf"},
             *               ],
             *      "sounds":[ {"id":"SOUND_ID","filepath":"data/entities/Example.ogg"},
             *               ],
             *      "songs":[ {"id":"SONG_ID","filepath":"data/entities/Example.ogg"},
             *               ],
             * }
             * @endcode
             * @param filename std::string fichero a cargar.
             * @return true si ha cargado los datos correctamente, false si hay algun problema.
             */
            bool loadAssets(const std::string& filename);
            /**
             * @brief Añade una textura con el id proporcionado.
             *
             * @param id std::string Id de la textura cargada.
             * @param filename std::string Textura a cargar.
             */
            void addTexture(const std::string& id,const std::string& filename);
            /**
             * @brief Devuelve una referencia a la textura, si no existe,
             *        tira excepcion de fuera de rango.
             *
             * @param id std::string id de la textura.
             * @return sf::Texture& referencia de la textura.
             */
            sf::Texture& getTexture(const std::string& id);
            /**
             * @brief Comprueba si tiene la textura.
             * @param id const std::string & id de la textura.
             */
            bool hasTexture(const std::string& id) const;
            /**
             * @brief Elimina la textura.
             * @param id std::string id de la textura a eliminar.
             */
            void removeTexture(const std::string& id);
            /**
             * @brief Añade una imagen con el id especificado.
             * @param id std::string id de la imagen.
             * @param filename std::string imagen a cargar.
             */
            void addImage(const std::string& id,const std::string& filename);
            /**
             * @brief Añade una imagen con el id especificado.
             * @param id std::string id de la imagen.
             * @param img std::unique_ptr<sf::Image> image para añadir
             */
            void addImage(const std::string& id, std::unique_ptr<sf::Image>&& img);
            /**
             * @brief Devuelve una referencia a la imagen, si no existe
             *        tira excepcion.
             *
             * @param id std::string id de la imagen.
             * @return sf::Image& referencia a imagen.
             */
            sf::Image& getImage(const std::string& id);
            /**
             * @brief Comprueba si tiene la imagen.
             * @param id std::string & id de la imagen.
             */
            bool hasImage(const std::string& id) const;
            /**
             * @brief Elimina la imagen por el id especificado.
             * @param id std::string id de la imagen a eliminar.
             */
            void removeImage(const std::string& id);
            /**
             * @brief Añade un tipo de letra.
             * @param id std::string
             * @param filename std::string
             */
            void addFont(const std::string& id,const std::string& filename);
            /**
             * @brief Devuelve el tipo de letra.
             * @param id std::string
             */
            sf::Font& getFont(const std::string& id);
            /**
             * @brief Comprueba si tiene la fuente especificada.
             * @param id const std::string & id de la fuente
             */
            bool hasFont(const std::string& id) const;
            /**
             * @brief Elimina un tipo de letra.
             * @param id std::string
             */
            void removeFont(const std::string& id);
            /**
             * @brief Añade un sonido
             * @param id const std::string&
             * @param filename const std::string&
             */
            void addSound(const std::string& id, const std::string& filename);
            /**
             * @brief Añade un sonido
             * @param id const std::string&
             * @param std::unique_ptr<sf::SoundBuffer>&&
             */
            void addSound(const std::string& id, std::unique_ptr<sf::SoundBuffer>&& sound);
            /**
             * @brief Comprueba si tiene un sonido
             * @param id const std::string&
             * @return bool
             */
            bool hasSound(const std::string& id) const;
            /**
             * @brief elimina la canción.
             * @param id const std::string&
             */
            void removeSound(const std::string& id);
            /**
             * @brief Añade una canción.
             * @param id const std::string&
             * @param filename const std::string&
             */
            void addSong(const std::string& id, const std::string& filename);
            /**
             * @brief añade una canción
             * @param id const std::string&
             * @param std::unique_ptr<sf::Music>
             */
            void addSong(const std::string& id, std::unique_ptr<sf::Music>&& song);
            /**
             * @brief comprueba si existe
             * @param id const std::string&
             * @return bool
             */
            bool hasSong(const std::string& id) const;
            /**
             * @brief elimina la canción
             * @param id const std::string&
             */
            void removeSong(const std::string id);
            /**
             * @brief Descarga todos los recursos cargados.
             * @return true si los descargo correctamente, false si no.
             */
            bool clear();
            ~AssetManager() = default;
        private:
            std::map<std::string,std::unique_ptr<sf::Texture>> textures;
            std::map<std::string,std::unique_ptr<sf::Image>> images;
            std::map<std::string,std::unique_ptr<sf::Font>> fonts;
            std::map<std::string,std::unique_ptr<sf::SoundBuffer>> sounds;
            std::map<std::string,std::unique_ptr<sf::Music>> songs;
    };
}
#endif // ASSET_MANAGER_HPP
