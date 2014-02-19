#include "../Components/Component.cpp"
#ifndef _SFML_
#include <SFML/Graphics.hpp>
#endif // _SFML_
class Entity{
    private:
        std::string name;
        long int id;
        std::map<long,Component> Components;
    public:
        Entity(){

        }
        Entity(std::string name,std::map<long,Component> components){
            this->name = name;
            this->Components = components;
            for(auto &c: Components){

            }
        }
        void addComponent(Component component){
            id << component.getId();
            this->Components.insert(std::pair<long,Component>(component.getId(),component));
        }
        inline const Component getComponent(long id){
            return Components.at(id);
        }

};
