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

#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H
#include <SFML/Graphics.hpp>
#include <array>
#include <AssetManager/AssetManager.hpp>
#include <Components/Component.hpp>
#include <Components/ComponentMask.hpp>
namespace ant{
    /**
     * @class ComponentFactory
     * @brief Clase para crear los componentes de las entidades.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class ComponentFactory{
        public:
            /**
             * @brief Constructor sin argumentos.
             */
            ComponentFactory();
            /**
             * @brief Constructor que le pasa los assets.
             *
             * @param assets std::shared_ptr<AssetManager>
             */
            ComponentFactory(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Llama a la funcion de AssetsManager::loadAssets()
             *        para cargar los assets desde un fichero,
             *        tiene que tener el formato especificado en la funcion.
             *
             * @param json std::string fichero json a cargar.
             * @return bool
             */
            bool loadAssets(const std::string& json);
            /**
             * @brief Descarga los assets cargados.
             * @return bool
             */
            bool unloadAssets();
            /**
             * @brief Pone el AssetManager especificado para usar,
             *        en la creacion de los componentes que
             *        requieran de assets.
             *
             * @param assets std::shared_ptr<AssetManager> Assets
             */
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Devuelve el asset manager que utiliza.
             * @return std::shared_ptr<AssetManager> AssetManager que utiliza.
             */
            inline std::shared_ptr<AssetManager> getAssetManager(){ return this->assets; }
            /**
             * @brief Crea un componente tipo Transform.
             *
             * Este componente basico es el cual permite a la entidad tener posicion.
             * necesario para poder renderizar, moverse, etc.
             * @code
             * Component<sf::Vector2f,sf::Vector2f,float>
             * @endcode
             * @param position sf::Vector2f posicion de la entidad.
             * @param scale sf::Vector2f escala de la entidad.
             * @param rotation float rotacion de la entidad.
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createTransform(sf::Vector2f position,sf::Vector2f scale,float rotation);
            /**
             * @brief Crea un componente Tipo Velocity
             *
             * Este componente basico es el cual permite a la entidad moverse.
             * necesario para poder moverse.
             * @code
             * Component<sf::Vector2f,float,float,float>
             * @endcode
             * @param speed float Velocidad actual.
             * @param minSpeed float Velocidad minima a la cual puede ir.
             * @param maxSpeed float Velocidad Maxima a la cual puede ir.
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createVelocity(float speed,float minSpeed,float maxSpeed);
            /**
             * @brief Crea un componente Tipo Bounds.
             *
             * Este componente basico es el cual permite a la entidad tener colisiones.
             * @code
             * Component<sf::FloatReact>
             * @endcode
             * @param bounds sf::FloatRect rectangulo de colision.
             * @return std::unique_ptr<baseComponent> componente Creado.
             */
            std::unique_ptr<baseComponent> createBounds(sf::FloatRect bounds);
            /**
             * @brief Crea un componente tipo Destructable.
             *
             * Este componente basico es el cual permite a la entidad ser destruida.
             * Son pixeles individuales las operaciones de mover no se pueden aplicar
             * sin tener un coste elevado, tarda mas segun lo grande que sea la imagen.
             * @code
             * Component<std::string,sf::VertexArray>
             * @endcode
             * @param position sf::Vector2f posicion en la que dibuja el primer pixel.
             * @param imageID std::string& id de la imagen a mapear.
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createDestructable(sf::Vector2f position,const std::string& imageID);
            /**
             * @brief Crea un componente tipo Animation.
             *
             * Este componente basico es el cual permite hacer animaciones.
             * necesita un sistema especifico por cada animacion.
             * @code
             *  Component<std::vector<std::string>>>
             * @endcode
             * @param ids std::vector<std::string> id de las texturas para la animacion.
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createAnimation(std::vector<std::string> ids);
            /**
             * @brief Crea un componente tipo Sprite
             *
             * Este componente basico es el cual permite a una entidad ser renderizada en 2d.
             * @code
             *  Component<std::string,sf::Sprite>
             * @endcode
             * @param id std::string id de la textura.
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createSprite(std::string id);
            /**
             * @brief Crea un componente tipo Passage
             *
             * Este componente permite ir de un sitio a otro.
             * @code
             *  Component<sf::Vector2f>
             * @endcode
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createPassage(sf::Vector2f dest);
            /**
             * @brief Crea un componente que indica la direccion.
             *
             * Este componente permite hacer que una entidad haga
             * aparecer otras entidades.
             *
             * @code
             *  Component<>
             * @endcode
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createIn();
            /**
             * @brief Crea un componente que indica la direccion.
             *
             * Este componente permite hacer que una entidad haga
             * desparecer las entidades que colisiones contra ella.
             *
             * @code
             *  Component<>
             * @endcode
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createOut();
            /**
             * @brief Crea un componente que tiene un numero de veces.
             * @code
             *  Component<int>
             * @endcode
             * @return std::unique_ptr<baseComponent> componente creado.
             */
            std::unique_ptr<baseComponent> createCounter(int count);
            ~ComponentFactory();
        private:
            std::shared_ptr<AssetManager> assets;
            /**
             * @brief Sirve para mapear una imagen a un sf::VertexArray.
             *
             * Se utiliza para mapear una imagen a un sf::VertexArray, si
             * la posicion es diferente a 0 la array se recorrera otra vez
             * para poner las posiciones de los pixels segun la posicion puesta.
             *
             * @param position sf::Vector2f Donde empezara a poner la posicion de cada pixel.
             * @param img sf::Image& referencia de la imagen a mapear.
             * @param bounds * sf::FloatRect la posicion y tamaño del destuctible
             */
            std::unique_ptr<sf::VertexArray> mapImage(const sf::Vector2f& position,sf::Image& img,sf::FloatRect* bounds);
    };
}

#endif // COMPONENT_FACTORY_H
