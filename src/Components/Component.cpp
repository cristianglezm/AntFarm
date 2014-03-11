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
            if(c.id == this->id){
                return true;
            }else{
                return false;
            }
        }
        Component::~Component(){

        }
}
