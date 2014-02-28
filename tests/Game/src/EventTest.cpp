#include <Event/Event.hpp>
#include <iostream>
#include <../include/EventTest.hpp>
bool EventTest(){
    std::cout << "Event Test:---------------------------" << std::endl;
    ant::Event e(4);
    std::cout << "Creamos Evento:\n\tTipo: " << e.getType() << std::endl;
    e.setType(49);
    std::cout << "Cambiamos Tipo: " << e.getType() << std::endl;
}
