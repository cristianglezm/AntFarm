#include <Application/Application.hpp>

int main(){
    try{
        ant::Application app;
        app.run();
    }catch(std::exception& e){
    #if defined ANDROID
        __android_log_write(ANDROID_LOG_INFO,"AntFarm",e.what()); // REMOMVE TODO
    #else
        std::cout << e.what() << std::end;
    #endif
    }
    return EXIT_SUCCESS;
}
