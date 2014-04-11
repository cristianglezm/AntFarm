#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <stdexcept>
#include <map>
#include <memory>
#include <fstream>
#include <JsonBox.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>

namespace ant{
    /**
     * Clase para tener todos los assets(imagenes,texturas,etc) del juego
     * @author Cristian Glez <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class AssetManager{
        private:
            std::map<std::string,std::unique_ptr<sf::Texture>> textures;
            std::map<std::string,std::unique_ptr<sf::Image>> images;
            std::map<std::string,std::unique_ptr<sf::Font>> fonts;
        public:
            AssetManager();
            bool loadAssets(const std::string& filename);
            void addTexture(const std::string& id,const std::string& filename);
            sf::Texture& getTexture(const std::string& id);
            void removeTexture(const std::string& id);
            void addImage(const std::string& id,const std::string& filename);
            sf::Image& getImage(const std::string& id);
            void removeImage(const std::string& id);
            void addFont(const std::string& id,const std::string& filename);
            sf::Font& getFont(const std::string& id);
            void removeFont(const std::string& id);
            bool clear();
            ~AssetManager();
    };
}
#endif // ASSET_MANAGER_H
