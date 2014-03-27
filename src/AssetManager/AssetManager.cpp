#include <AssetManager/AssetManager.hpp>
namespace ant{
    AssetManager::AssetManager(){

    }
    void AssetManager::loadAssets(std::string& json){

    }
    void AssetManager::addTexture(std::string id,std::string filename){
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        if(!texture->loadFromFile(filename)){
            throw std::runtime_error("Failed to load texture " + filename);
        }
        textures.insert(std::make_pair(id,std::move(texture)));
    }
    sf::Texture& AssetManager::getTexture(std::string id){
        return *textures.at(id);
    }
    void AssetManager::removeTexture(std::string id){
        textures.erase(id);
    }
    void AssetManager::addImage(std::string id,std::string filename){
        std::unique_ptr<sf::Image> image(new sf::Image());
        if(!image->loadFromFile(filename)){
            throw std::runtime_error("Failed to load image " + filename);
        }
        images.insert(std::make_pair(id,std::move(image)));
    }
    sf::Image& AssetManager::getImage(std::string id){
        return *images.at(id);
    }
    void AssetManager::removeImage(std::string id){
        images.erase(id);
    }
    AssetManager::~AssetManager(){

    }
}
