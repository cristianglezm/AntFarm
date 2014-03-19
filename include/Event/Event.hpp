#ifndef EVENT_H
#define EVENT_H
#include <tuple>
#include <memory>
namespace ant{
    /** @brief Clase Base de eventos
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class baseEvent{
        private:
            int type;
        protected:
            baseEvent(int type):type(type){}
        public:
            virtual ~baseEvent() = default;
            void setType(int type){ this->type=type;}
            inline int getType()const{ return type; }
            template<typename...T>
            const std::tuple<T...>& getAttributes() const;
            template<typename...T>
            void setAttributes(std::tuple<T...> attributes);
    };
    /**
     *
     *
     */
    template<typename...T>
    class Event: public baseEvent{
        private:
            std::tuple<T...> attributes;
        public:
            Event(int type,T...data): baseEvent{type}, attributes{std::move(data)...} {}
        inline const std::tuple<T...>& getAttributes() const { return attributes; }
    };
    template<typename...T>
    const std::tuple<T...>& baseEvent::getAttributes() const {
        auto& casted = dynamic_cast<const Event<T...>&>(*this);
        return casted.getAttributes();
    }
    template<typename T, typename... Args>
    std::shared_ptr<T> makeSharedPtr(Args&&... args) {
        return std::shared_ptr<T>(new T(args...));
    }
}
#endif // EVENT_H
