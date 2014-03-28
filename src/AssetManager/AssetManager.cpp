#include <AssetManager/AssetManager.hpp>
namespace ant{
    AssetManager::AssetManager(){

    }
    void AssetManager::addTexture(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        if(texture->loadFromFile(filename)){

        }
        textures.insert(std::make_pair(id,std::move(texture)));
    }
    sf::Texture* AssetManager::getTexture(const std::string& id){
        return textures.at(id).get();
    }
    void AssetManager::removeTexture(const std::string& id){
        textures.erase(id);
    }
    void AssetManager::addImage(const std::string&id,const std::string& filename){

    }
    sf::Image* AssetManager::getImage(const std::string& id){

    }
    void AssetManager::removeImage(const std::string& id){

    }
    AssetManager::~AssetManager(){

    }
}
