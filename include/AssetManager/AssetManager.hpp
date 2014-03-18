#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

namespace ant{
    class AssetManager{
        private:
            std::map<std::string,std::unique_ptr<sf::Texture>> textures;
            std::map<std::string,std::unique_ptr<sf::Image>> images;
        public:
            void addTexture(std::string id,std::string filename);
            sf::Texture* getTexture(std::string id);
            void removeTexture(std::string id);
            void addImage(std::string id,std::string filename);
            sf::Image* getImage(std::string id);
            void removeImage(std::string id);
    };
}
#endif // ASSET_MANAGER_H
