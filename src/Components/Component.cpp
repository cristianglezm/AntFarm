#include "Component.hpp"

        Component::Component(long int id){
            this->id = id;
        }
       void Component::setId(long int id){
           this->id = id;
       }
       const long Component::getId(){
           return this->id;
       }
