#ifndef STATES_HPP
#define STATES_HPP

/**
 * @brief Estados de las entidades
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 0.1
 */
class States{
     public:
        static const long int NONE = 0;
        static const long int GROUND = 1 << 0;
        static const long int FALLING = 1 << 1;
        static const long int CLIMBING = 1 << 2;
        static const long int BUILDING = 1 << 3;
        static const long int ONFIRE = 1 << 4;
        static const long int SAVED = 1 << 5;
        static const long int UNSAVED = 1 << 6;
};

#endif // STATES_HPP
