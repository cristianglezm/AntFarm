#ifndef STATES_H
#define STATES_H

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
        static const long int ONFIRE = 1 << 2;
};

#endif // STATES_H
