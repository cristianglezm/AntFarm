#ifndef COMPONENT_MASK_H
#define COMPONENT_MASK_H

/**
 * Clase estatica para enumeracion de componentes.
 * @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
 * @version 0.1
 */
class ComponentsMask{
     public:
         static const long int COMPONENT_NONE = 0;
         static const long int COMPONENT_SPRITE = 1 << 0;
         static const long int COMPONENT_MOVEMENT = 1 << 1;
         static const long int COMPONENT_TRANSFORM = 1 << 2;
         static const long int COMPONENT_EGGS = 1 << 3;
         static const long int COMPONENT_HORNS = 1 << 4;
         static const long int COMPONENT_DESTRUCTABLE = 1 << 5;
         static const long int COMPONENT_BOUNDS = 1 << 6;
};
#endif // COMPONENT_MASK_H
