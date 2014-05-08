#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H
/**
 * @brief Tipos de eventos.
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 0.1
 */
class EventType{
    public:
        static const long int COLLISION_EVENT = 0;
        static const long int CHANGE_OVERTIME = 1;
        static const long int CHANGE_NENTITIES = 2;
};
#endif // EVENT_TYPE_H
