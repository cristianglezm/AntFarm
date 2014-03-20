#include <Event/Event.hpp>
#include <iostream>
#include <../include/EventTest.hpp>
bool EventTest(){
    std::cout << "Event Test:---------------------------" << std::endl;
    ant::Event<int,std::string> e(4,5,"Test de evento con templates");
    std::cout << "Creamos Evento:\n\tTipo: " << e.getType() << std::endl;
    e.setType(49);
    auto& attributes = e.getAttributes();
    std::cout << std::get<1>(attributes) << std::endl;
    std::cout << "Cambiamos Tipo: " << e.getType() << std::endl;
    return true;
}
