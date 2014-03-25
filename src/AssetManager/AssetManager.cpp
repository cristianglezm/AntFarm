#include <AssetManager/AssetManager.hpp>
namespace ant{
    AssetManager::AssetManager(){

    }
    void AssetManager::addTexture(std::string id,std::string filename){
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        if(texture->loadFromFile(filename)){

        }
        textures.insert(std::make_pair(id,std::move(texture)));
    }
    sf::Texture* AssetManager::getTexture(std::string id){
        return textures.at(id).get();
    }
    void AssetManager::removeTexture(std::string id){
        textures.erase(id);
    }
    void AssetManager::addImage(std::string id,std::string filename){

    }
    sf::Image* AssetManager::getImage(std::string id){

    }
    void AssetManager::removeImage(std::string id){

    }
    AssetManager::~AssetManager(){

    }
}
