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

#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

#include <ComponentFactory.hpp>
#include <Components/ComponentMask.hpp>
#include <ComponentSettings.hpp>
#include <Entity/Entity.hpp>
#include <Utils/Utility.hpp>
#include <Config.hpp>

namespace ant{
    /**
     * @brief Clase para crear las entidades del juego.
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class EntityFactory final{
        public:
            static const ComponentsMask::Mask Ant;
            static const ComponentsMask::Mask Door;
            static const ComponentsMask::Mask InDoor;
            static const ComponentsMask::Mask OutDoor;
            static const ComponentsMask::Mask level;
            /**
             * @brief Constructor por defecto.
             */
            EntityFactory();
            /**
             * @brief Constructor que carga los assets del json especificado.
             *
             * @param json std::string fichero json a cargar.
             */
            EntityFactory(const std::string& json);
            /**
             * @brief Carga los assets especificados en el fichero json.
             *
             * Formato del fichero json AssetManager::loadAssets()
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
             * @brief Setter del assetManager.
             * @param assets std::shared_ptr<AssetManager> assets que utilizara para cargar componentes que los utilicen.
             */
            void setAssetManager(std::shared_ptr<AssetManager> assets);
            /**
             * @brief Getter del AssetManager.
             * @return std::shared_ptr<AssetManager>
             */
            inline std::shared_ptr<AssetManager> getAssetManager() noexcept{ return componentFactory->getAssetManager(); }
            /**
             * @brief Crea la entidad especificada.
             *
             * Se puede especificar otros componentes pero tendran los datos por defecto
             *
             * @param mask ComponentsMask::Mask Mascara de la entidad o componentes.
             *        @code EntityFactory::createEntity( EntityFactory::ANT | Component::Wings | Component::Horns); @endcode
             *        Creas una entidad Hormiga con los componentes adicionales especificados los cuales tendran
             *        valores por defecto.
             * @return std::unique_ptr<Entity> entidad creada.
             */
            std::unique_ptr<Entity> createEntity(ComponentsMask::Mask mask);
            /**
             * @brief Crea la entidad especificada con los datos especificados.
             *
             * @param mask ComponentsMask::Mask mascara de la entidad o componentes.
             * @param cs ComponentSettings
             * @return std::unique_ptr<Entity>
             */
            std::unique_ptr<Entity> createEntity(ComponentsMask::Mask mask, ComponentSettings& cs);
            /**
             * @brief Setter de la fabrica de componentes a utilizar.
             * @param cf std::shared_ptr<ComponentFactory>
             */
            void setComponentFactory(std::shared_ptr<ComponentFactory> cf);
            /**
             * @brief Getter de la fabrica de componentes utilizada.
             * @return std::shared_ptr<ComponentFactory>
             */
            inline std::shared_ptr<ComponentFactory> getComponentFactory() noexcept{ return componentFactory; }
            ~EntityFactory() = default;
        private:
            std::shared_ptr<ComponentFactory> componentFactory;
    };
}

#endif // ENTITY_FACTORY_HPP