#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <stdexcept>
#include <map>
#include <memory>
#include <fstream>
#include <JsonBox.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

namespace ant{
    class AssetManager{
        private:
            std::map<std::string,std::unique_ptr<sf::Texture>> textures;
            std::map<std::string,std::unique_ptr<sf::Image>> images;
        public:
            AssetManager();
            void loadAssets(const std::string& filename);
            void addTexture(const std::string& id,const std::string& filename);
            sf::Texture& getTexture(const std::string& id);
            void removeTexture(const std::string& id);
            void addImage(const std::string& id,const std::string& filename);
            sf::Image& getImage(const std::string& id);
            void removeImage(const std::string& id);
            ~AssetManager();
    };
}
#endif // ASSET_MANAGER_H
