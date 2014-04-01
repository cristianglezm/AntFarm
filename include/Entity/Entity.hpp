#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <memory>
#include <map>
#include <Components/Component.hpp>
#include <iostream>
namespace ant{
    class Entity{
        private:
            std::string name;
            long int mask;
            std::map<long int,std::unique_ptr<baseComponent> > Components;
        public:
            Entity();
            Entity(std::string name);
            Entity(std::string name,std::map<long int,std::unique_ptr<baseComponent> > Components);
            void addComponent(std::unique_ptr<baseComponent> component);
            inline std::unique_ptr<baseComponent>& getComponent(long int mask){
                 try{
                        return Components.at(mask);
                    }catch(std::exception& out){
                        std::cout << out.what() << " COMPONENTE NO ENCONTRADO " << mask << std::endl;
                    }
                 }
            void removeComponent(long int mask);
            inline std::string getName() const { return name; }
            void setName(std::string name);
            void setComponents(std::map<long int,std::unique_ptr<baseComponent>> Components);
            inline std::map<long int,std::unique_ptr<baseComponent> >& getComponents(){ return Components; }
            inline long int getMask() const { return mask; }
            bool operator==(const Entity& e) const;
            bool operator==(const std::string& name) const;
            ~Entity();
    };
};
#endif // ENTITY_H
