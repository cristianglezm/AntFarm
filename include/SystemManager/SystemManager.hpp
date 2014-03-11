#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include <map>
#include <memory>
#include <Systems/System.hpp>
namespace ant{
    class SystemManager{
        private:
            std::map<std::string,std::shared_ptr<System> > systems;
        public:
            SystemManager();
            bool addSystem(std::shared_ptr<System> s);
            std::shared_ptr<System> getSystem(std::string name);
            void setSystems(std::map<std::string,std::shared_ptr<System>> systems);
            std::map<std::string,std::shared_ptr<System>> getSystems();
            void removeSystem(std::string name);
            ~SystemManager();
    };
}
#endif // SYSTEM_MANAGER_H
