#include <iostream>
#include <Components/ComponentMask.hpp>
#include <Components/Component.hpp>
#include <ComponentTest.hpp>
#include <cassert>
bool ComponentTest(){
    std::cout << "Component Test:-------------------------------- " << std::endl;
    /// Al declararlo ya de esta forma el getProperties no requiere los <int,etc>
    /// si fuese declarado como baseComponent tendriamos que indicarle las propiedades al metodo
    /// getProperties<int,etc>();
    ant::Component<int,ant::Component<float>> c(ComponentsMask::COMPONENT_NONE,2,
                            ant::Component<float>(
                                ComponentsMask::COMPONENT_DESTRUCTABLE,4.5));
    assert(c.getId()==ComponentsMask::COMPONENT_NONE);
    std::cout << "ID: " << c.getId() << std::endl;
    c.setId(ComponentsMask::COMPONENT_EGGS);
    auto& properties = c.getProperties();
    std::cout << "Propiedad 1(int): " << std::get<0>(properties) << std::endl;
    std::cout << "Propiedad 2(Component)->propiedad 1(float): " << std::get<0>(std::get<1>(properties).getProperties()) << std::endl;
    assert(c.getId()==ComponentsMask::COMPONENT_EGGS);
    std::cout << "Cambiamos ID\nID: " << c.getId() << std::endl;
    return true;
}
