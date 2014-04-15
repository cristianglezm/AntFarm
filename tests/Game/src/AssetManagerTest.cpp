#include <../include/AssetManagerTest.hpp>
#include <iostream>
#include <AssetManager/AssetManager.hpp>
bool assetManagerTest(){
    std::cout << "AssetManager Test------------" << std::endl;
    ant::AssetManager am;
    std::cout << "Loading assets..." << std::endl;
    am.loadAssets("../../data/config/assets.json");
    std::cout << "assets loaded" << std::endl;
    std::cout << "removing Ant" << std::endl;
    am.removeTexture("Ant");
}
