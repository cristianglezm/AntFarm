#ifndef COMPONENT_H
#define COMPONENT_H

class Component{
    private:
        long int id;
    public:
        Component(long int id);
        void setId(long int id);
        const long getId();
};
#endif // COMPONENT_H
