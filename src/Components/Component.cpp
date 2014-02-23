#include <Components/Component.hpp>
        Component::Component():id(0){
        }
        Component::Component(long int id){
            this->id = id;
        }
        void Component::setId(long int id){
            this->id = id;
       }
