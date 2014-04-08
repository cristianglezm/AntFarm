
#include <JsonBox.h>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream input("menu.json");
    JsonBox::Value v(input);

    int size = v["textures"].getArray().size();
    for(int i=0;i<size;++i){
        std::cout << "ID: "<< v["Textures"][size_t(i)]["id"] << std::endl;
        std::cout <<"Filename: "<< v["Textures"][size_t(i)]["filename"] << std::endl;
    }
    return 0;
}
