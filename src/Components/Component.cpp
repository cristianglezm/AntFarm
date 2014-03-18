#include <Components/Component.hpp>
namespace ant{
        Component::Component():id(0){
        }
        Component::Component(long int id){
            this->id = id;
        }
        void Component::setId(long int id){
            this->id = id;
        }
        bool Component::operator==(const Component& c)const{
            return (c.id == this->id);
        }
        Component::~Component(){

        }
}
