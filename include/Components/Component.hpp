#ifndef COMPONENT_H
#define COMPONENT_H
namespace ant{
    /** @brief Clase basica de componente.
     *  @author Cristian Gonzalez Moreno <cristian.glez.m@gmail.com>
     *  @version 0.1
     */
    class Component{
        private:
            long int id;
        public:
            Component();
            Component(long int id);
            void setId(long int id);
            inline const long getId(){ return this->id; }
            virtual bool operator==(const Component& c) const;
            virtual ~Component();
    };
}
#endif // COMPONENT_H
