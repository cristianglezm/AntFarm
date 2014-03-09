#ifndef EVENT_H
#define EVENT_H
namespace ant{
    /** @brief Clase Base de eventos
     *  @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class Event{
        private:
            int type;
        public:
            Event(int type);
            void setType(int type);
            inline int getType(){ return type; }
    };
}
#endif // EVENT_H
