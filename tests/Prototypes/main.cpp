#include <iostream>
#include <tuple>
template<typename... Ts>
class Component{
    private:
        long int id;
        std::tuple<Ts...> properties;
    public:
        Component(long int id):id(id){}
        void setId(long int id){
            this->id = id;
        }
        long int getId(){
            return id;
        }
        ~Component(){}
};
int main(int nargs,char** args){
    return 0;
}
