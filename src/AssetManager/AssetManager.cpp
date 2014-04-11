#include <AssetManager/AssetManager.hpp>
namespace ant{
    AssetManager::AssetManager(){

    }
    bool AssetManager::loadAssets(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(!v["textures"].isNull()){
            int size = v["textures"].getArray().size();
            for(int i=0;i<size;++i){
                addTexture(v["textures"][size_t(i)]["id"].getString(),
                           v["textures"][size_t(i)]["filepath"].getString());
            }
        }
        if(!v["images"].isNull()){
            int size = v["images"].getArray().size();
            for(int i=0;i<size;++i){
                addImage(v["images"][size_t(i)]["id"].getString(),
                           v["images"][size_t(i)]["filepath"].getString());
            }
        }
        if(!v["fonts"].isNull()){
            int size = v["fonts"].getArray().size();
            for(int i=0;i<size;++i){
                addFont(v["fonts"][size_t(i)]["id"].getString(),
                           v["fonts"][size_t(i)]["filepath"].getString());
            }
        }
        return true;
    }
    void AssetManager::addTexture(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Texture> texture(new sf::Texture());
        if(!texture->loadFromFile(filename)){
            throw std::runtime_error("Failed to load texture " + filename);
        }
        textures.insert(std::make_pair(id,std::move(texture)));
    }
    sf::Texture& AssetManager::getTexture(const std::string& id){
        return *textures.at(id).get();
    }
    void AssetManager::removeTexture(const std::string& id){
        textures.erase(id);
    }
    void AssetManager::addImage(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Image> image(new sf::Image());
        if(!image->loadFromFile(filename)){
            throw std::runtime_error("Failed to load image " + filename);
        }
        images.insert(std::make_pair(id,std::move(image)));
    }
    sf::Image& AssetManager::getImage(const std::string& id){
        return *images.at(id);
    }
    void AssetManager::removeImage(const std::string& id){
        images.erase(id);
    }
    void AssetManager::addFont(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Font> font(new sf::Font());
        if(!font->loadFromFile(filename)){
            throw std::runtime_error("Failed to load Font " + filename);
        }
        fonts.insert(std::make_pair(id,std::move(font)));
    }
    sf::Font& AssetManager::getFont(const std::string& id){
        return *fonts.at(id);
    }
    void AssetManager::removeFont(const std::string& id){
        fonts.erase(id);
    }
    bool AssetManager::clear(){
        images.clear();
        textures.clear();
        fonts.clear();
        return true;
    }
    AssetManager::~AssetManager(){

    }
}
