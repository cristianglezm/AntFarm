#include <Application/Application.hpp>

int main(){
    try{
        ant::Application app;
        app.run();
    }catch(std::exception& e){
    #ifndef ANDROID
        std::cout << e.what() << std::endl;
    #endif
    }
    return EXIT_SUCCESS;
}
