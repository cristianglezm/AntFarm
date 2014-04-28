#ifndef COMPONENT_MASK_H
#define COMPONENT_MASK_H

/**
 * @brief tipos de componentes.
 * @author Cristian Glez <Cristian.glez.m@gmail.com>
 * @version 0.1
 */
class ComponentsMask{
     public:
        static const long int COMPONENT_NONE = 0;
        static const long int COMPONENT_SPRITE = 1 << 0;
        static const long int COMPONENT_ANIMATION = 1 << 1;
        static const long int COMPONENT_VELOCITY = 1 << 2;
        static const long int COMPONENT_TRANSFORM = 1 << 3;
        static const long int COMPONENT_EGGS = 1 << 4;
        static const long int COMPONENT_HORNS = 1 << 5;
        static const long int COMPONENT_DESTRUCTABLE = 1 << 6;
        static const long int COMPONENT_BOUNDS = 1 << 7;
        static const long int COMPONENT_DIRT_BAG = 1 << 8;
        static const long int COMPONENT_FOOD_BAG = 1 << 9;
        static const long int COMPONENT_PASSPORT = 1 << 10;
};
#endif // COMPONENT_MASK_H
