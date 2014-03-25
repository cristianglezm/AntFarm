#ifndef COMPONENT_H
#define COMPONENT_H
#include <tuple>
#include <memory>
namespace ant{
    /** @brief Clase base de componente.
     *  @author Cristian Gonzalez Moreno <cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class baseComponent{
        private:
            int id;
        protected:
            baseComponent(int id):id(id){}
        public:
            virtual ~baseComponent() = default;
            void setId(int id){ this->id=id;}
            inline int getId() const{ return id; }
            template<typename...T>
            std::tuple<T...>& getProperties();
            template<typename...T>
            void setProperties(std::tuple<T...> properties);
    };
    /**
     *
     *
     */
    template<typename...T>
    class Component: public baseComponent{
        private:
            std::tuple<T...> properties;
        public:
            Component(int id,T...data): baseComponent{id}, properties{std::move(data)...} {}
            inline std::tuple<T...>& getProperties(){ return properties; }
    };
    template<typename...T>
    std::tuple<T...>& baseComponent::getProperties(){
        auto& casted = dynamic_cast<Component<T...>&>(*this);
        return casted.getProperties();
    }
    template<typename T, typename... Args>
    std::unique_ptr<T> makeUniquePtr(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif // COMPONENT_H
