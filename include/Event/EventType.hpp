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
        static const long int TERRAIN_COLLISION = 1;
        static const long int CHANGE_OVERTIME = 2;
        static const long int CHANGE_NENTITIES = 3;
        static const long int CHANGE_COMMAND = 4;
        static const long int SELECT_ENTITY = 5;
};
#endif // EVENT_TYPE_H
